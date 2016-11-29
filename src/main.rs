#![no_main]

extern crate libc;
#[macro_use]
extern crate lazy_static;

mod read;

use libc::c_char;
use std::ffi::CStr;
use std::collections::HashMap;
use std::sync::Mutex;
use std::fmt::{self, Write};

type RegSize = i64;

#[derive(Debug)]
enum Instruction<'a> {
    ADD,
    SUB,
    MUL,
    DIV,
    LES,
    AND,
    EQU,
    NOT,
    LA(&'a str),
    LC(RegSize),
    LV,
    STR,
    PRI,
    REA,
    JMP(&'a str),
    JIN(&'a str),
    DS(&'a str, usize),
    NOP,
    STP,
    Label(&'a str),
}

struct Code<'a>(Vec<Instruction<'a>>);

impl<'a> fmt::Display for Instruction<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        use self::Instruction::*;

        match *self {
            ADD => write!(f, "ADD"),
            SUB => write!(f, "SUB"),
            MUL => write!(f, "MUL"),
            DIV => write!(f, "DIV"),
            LES => write!(f, "LES"),
            EQU => write!(f, "EQU"),
            AND => write!(f, "AND"),
            NOT => write!(f, "NOT"),
            LA(variable) => write!(f, "LA {}", variable),
            LC(constant) => write!(f, "LC {}", constant),
            LV => write!(f, "LV"),
            STR => write!(f, "STR"),
            PRI => write!(f, "PRI"),
            REA => write!(f, "REA"),
            JMP(label) => write!(f, "JMP {}", label),
            JIN(label) => write!(f, "JIN {}", label),
            DS(variable, count) => write!(f, "DS {} {}", variable, count),
            NOP => write!(f, "NOP"),
            Label(l) => write!(f, "{}", l),
            STP => write!(f, "STP"),
        }
    }
}

impl<'a> fmt::Display for Code<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        for instruction in &self.0 {
            writeln!(f, "{}", instruction)?;
        }
        Ok(())
    }
}

fn parse_asm(src: &str) -> Result<Vec<Instruction>, String> {
    use self::Instruction::*;

    let mut src = src.split_whitespace();
    let mut instructions = Vec::new();

    while let Some(opcode) = src.next() {
        let instruction = match opcode {
            "ADD" => ADD,
            "SUB" => SUB,
            "MUL" => MUL,
            "DIV" => DIV,
            "LES" => LES,
            "AND" => AND,
            "EQU" => EQU,
            "NOT" => NOT,
            "LA" => {
                let variable = src.next().ok_or("Expected LA variable.")?;
                if !variable.starts_with('$') {
                    return Err("LA variable doesn't start with $.".into());
                }
                LA(variable)
            }
            "LC" => {
                LC(src.next()
                    .ok_or("Expected LC argument.")?
                    .parse()
                    .map_err(|_| "Failed to parse LC argument as number.")?)
            }
            "LV" => LV,
            "STR" => STR,
            "PRI" => PRI,
            "REA" => REA,
            "JMP" => {
                let label = src.next().ok_or("Expected JMP label.")?;
                if !label.starts_with('#') {
                    return Err("JMP label doesn't start with #.".into());
                }
                JMP(label)
            }
            "JIN" => {
                let label = src.next().ok_or("Expected JIN label.")?;
                if !label.starts_with('#') {
                    return Err("JIN label doesn't start with #.".into());
                }
                JIN(label)
            }
            "DS" => {
                let variable = src.next().ok_or("Expected DS variable.")?;
                if !variable.starts_with('$') {
                    return Err("DS variable doesn't start with $.".into());
                }
                let count = src.next()
                    .ok_or("Expected DS variable count.")?
                    .parse()
                    .map_err(|_| "Couldn't parse DS variable count.")?;
                DS(variable, count)
            }
            "NOP" => NOP,
            "STP" => STP,
            label if label.starts_with('#') => Label(label),
            o => return Err(format!("Unknown opcode {}.", o)),
        };
        instructions.push(instruction);
    }

    Ok(instructions)
}

fn find_label_positions<'a>(code: &'a [Instruction<'a>]) -> HashMap<&'a str, usize> {
    code.iter()
        .enumerate()
        .filter_map(|(pos, instruction)| if let Instruction::Label(label) = *instruction {
            Some((label, pos))
        } else {
            None
        })
        .collect()
}

fn execute(code: &[Instruction], output: &mut String, debug: bool) -> Result<(), String> {
    use Instruction::*;

    let label_positions = find_label_positions(code);
    let mut variable_pointers = HashMap::new();
    let mut stack = Vec::<RegSize>::new();
    let mut instruction_ptr = code.iter().peekable();

    while let Some(instruction) = instruction_ptr.next() {
        match *instruction {
            ADD => {
                let a = stack.pop().ok_or("Stack is empty.")?;
                let b = stack.pop().ok_or("Stack is empty.")?;
                stack.push(b.wrapping_add(a));
            }
            SUB => {
                let a = stack.pop().ok_or("Stack is empty.")?;
                let b = stack.pop().ok_or("Stack is empty.")?;
                stack.push(b.wrapping_sub(a));
            }
            MUL => {
                let a = stack.pop().ok_or("Stack is empty.")?;
                let b = stack.pop().ok_or("Stack is empty.")?;
                stack.push(b.wrapping_mul(a));
            }
            DIV => {
                let a = stack.pop().ok_or("Stack is empty.")?;
                let b = stack.pop().ok_or("Stack is empty.")?;
                stack.push(b.wrapping_div(a));
            }
            LES => {
                let a = stack.pop().ok_or("Stack is empty.")?;
                let b = stack.pop().ok_or("Stack is empty.")?;
                stack.push(if b < a { 1 } else { 0 });
            }
            EQU => {
                let a = stack.pop().ok_or("Stack is empty.")?;
                let b = stack.pop().ok_or("Stack is empty.")?;
                stack.push(if b == a { 1 } else { 0 });
            }
            AND => {
                let a = stack.pop().ok_or("Stack is empty.")?;
                let b = stack.pop().ok_or("Stack is empty.")?;
                stack.push(if b != 0 && a != 0 { 1 } else { 0 });
            }
            NOT => {
                let a = stack.pop().ok_or("Stack is empty.")?;
                stack.push(if a == 0 { 1 } else { 0 });
            }
            LA(variable) => {
                let ptr = *variable_pointers.get(variable).ok_or("Couldn't find variable.")?;
                stack.push(ptr as RegSize);
            }
            LC(constant) => {
                stack.push(constant);
            }
            LV => {
                let ptr = stack.pop().ok_or("Stack is empty.")?;
                let value = *stack.get(ptr as usize).ok_or("LV pointer out of bounds.")?;
                stack.push(value);
            }
            STR => {
                let ptr = stack.pop().ok_or("Stack is empty.")?;
                let value = stack.pop().ok_or("Stack is empty.")?;
                let reference = stack.get_mut(ptr as usize).ok_or("STR pointer out of bounds.")?;
                *reference = value;
            }
            PRI => {
                let a = stack.pop().ok_or("Stack is empty.")?;
                writeln!(output, "{}", a).unwrap();
            }
            REA => {
                let buf;
                let text = if let Some(&&LA(variable)) = instruction_ptr.peek() {
                    buf = format!("Choose {}:", &variable[1..]);
                    &buf
                } else {
                    "Choose Number:"
                };
                let buffer = read::prompt(text, "");
                let value = buffer.trim()
                    .parse()
                    .map_err(|e| format!("Couldn't parse user input as number: {}.", e))?;
                stack.push(value);
            }
            JMP(label) => {
                let pos = *label_positions.get(label).ok_or("Couldn't find label to jump to.")?;
                instruction_ptr = code[pos..].iter().peekable();
            }
            JIN(label) => {
                let expression = stack.pop().ok_or("Stack is empty.")?;
                if expression == 0 {
                    let pos = *label_positions.get(label).ok_or("Couldn't find label to jump to.")?;
                    instruction_ptr = code[pos..].iter().peekable();
                }
            }
            DS(variable, count) => {
                variable_pointers.insert(variable, stack.len());
                for _ in 0..count {
                    stack.push(0);
                }
            }
            NOP | Label(_) => {}
            STP => break,
        }
        if debug {
            writeln!(output, "{} {:?}", instruction, stack).unwrap();
        } else {
            println!("{} {:?}", instruction, stack);
        }
    }

    Ok(())
}

lazy_static! {
    static ref OUTPUT: Mutex<String> = Mutex::new(String::new());
}

#[no_mangle]
pub unsafe extern "C" fn format_asm(asm: *const c_char) -> *const c_char {
    let mut output = OUTPUT.lock().unwrap();

    output.clear();

    let asm = CStr::from_ptr(asm);
    let asm = asm.to_string_lossy();

    let instructions = parse_asm(&asm);
    match instructions {
        Ok(instructions) => write!(&mut output, "{}", Code(instructions)).unwrap(),
        Err(e) => *output = e,
    }

    output.push('\0');
    output.as_ptr() as *const c_char
}

#[no_mangle]
pub unsafe extern "C" fn interpret(asm: *const c_char, debug: bool) -> *const c_char {
    let mut output = OUTPUT.lock().unwrap();

    output.clear();

    let asm = CStr::from_ptr(asm);
    let asm = asm.to_string_lossy();

    let instructions = parse_asm(&asm);
    match instructions {
        Ok(instructions) => {
            if let Err(e) = execute(&instructions, &mut output, debug) {
                *output = e;
            }
        }
        Err(e) => *output = e,
    }

    output.push('\0');
    output.as_ptr() as *const c_char
}
