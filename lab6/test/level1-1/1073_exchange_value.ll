@n = global i32 0, align 4
define i32 @main() {
B24:
  %t27 = alloca i32, align 4
  %t26 = alloca i32, align 4
  %t25 = alloca i32, align 4
  %t4 = call i32 @getint()
  store i32 %t4, i32* %t25, align 4
  %t6 = call i32 @getint()
  store i32 %t6, i32* %t26, align 4
  %t9 = load i32, i32* %t25, align 4
  store i32 %t9, i32* %t27, align 4
  %t11 = load i32, i32* %t26, align 4
  store i32 %t11, i32* %t25, align 4
  %t13 = load i32, i32* %t27, align 4
  store i32 %t13, i32* %t26, align 4
  %t15 = load i32, i32* %t25, align 4
  call void @putint(i32 %t15)
  store i32 10, i32* %t27, align 4
  %t18 = load i32, i32* %t27, align 4
  call void @putch(i32 %t18)
  %t20 = load i32, i32* %t26, align 4
  call void @putint(i32 %t20)
  store i32 10, i32* %t27, align 4
  %t23 = load i32, i32* %t27, align 4
  call void @putch(i32 %t23)
  ret i32 0
}
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
