use libc;
use std::ffi::{CString, CStr};
use std::str;

trait Interop {
    fn as_int(self, _: &mut Vec<CString>) -> libc::c_int;
}

impl Interop for i32 {
    fn as_int(self, _: &mut Vec<CString>) -> libc::c_int {
        self
    }
}

impl<'a> Interop for &'a str {
    fn as_int(self, arena: &mut Vec<CString>) -> libc::c_int {
        let c = CString::new(self).unwrap();
        let ret = c.as_ptr() as libc::c_int;
        arena.push(c);
        ret
    }
}

impl<'a> Interop for *const libc::c_void {
    fn as_int(self, _: &mut Vec<CString>) -> libc::c_int {
        self as libc::c_int
    }
}

#[macro_export]
macro_rules! js {
    ( ($( $x:expr ),*) $y:expr ) => {
        {
            let mut arena:Vec<CString> = Vec::new();
            const LOCAL: &'static [u8] = $y;
            unsafe { ::read::emscripten_asm_const_int(&LOCAL[0] as *const _ as *const libc::c_char, $(Interop::as_int($x, &mut arena)),*) }
        }
    };
    ( $y:expr ) => {
        {
            const LOCAL: &'static [u8] = $y;
            unsafe { ::read::emscripten_asm_const_int(&LOCAL[0] as *const _ as *const libc::c_char) }
        }
    };
}

pub fn prompt(message: &str, value: &str) -> String {
    let a = js! { (message, value) b"\
            var message = UTF8ToString($0); \
            var value = UTF8ToString($1); \
            var text = prompt(message, value); \
            if (text === null) { \
                text = ''; \
            } \
            return allocate(intArrayFromString(text), 'i8', ALLOC_STACK); \
        \0" };
    unsafe {
        str::from_utf8(CStr::from_ptr(a as *const libc::c_char).to_bytes()).unwrap().to_owned()
    }
}

extern "C" {
    pub fn emscripten_asm_const_int(s: *const libc::c_char, ...) -> libc::c_int;
}
