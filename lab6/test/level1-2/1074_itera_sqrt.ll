define i32 @fsqrt(i32 %t0) {
B34:
  %t37 = alloca i32, align 4
  %t36 = alloca i32, align 4
  %t35 = alloca i32, align 4
  store i32 %t0, i32* %t35, align 4
  store i32 0, i32* %t36, align 4
  %t5 = load i32, i32* %t35, align 4
  %t6 = sdiv i32 %t5, 2
  store i32 %t6, i32* %t37, align 4
  br label %B38
B38:                               	; preds = %B34, %B39
  %t7 = load i32, i32* %t36, align 4
  %t8 = load i32, i32* %t37, align 4
  %t9 = sub i32 %t7, %t8
  %t10 = icmp ne i32 %t9, 0
  br i1 %t10, label %B39, label %B41
B39:                               	; preds = %B38
  %t12 = load i32, i32* %t37, align 4
  store i32 %t12, i32* %t36, align 4
  %t14 = load i32, i32* %t36, align 4
  %t15 = load i32, i32* %t35, align 4
  %t16 = load i32, i32* %t36, align 4
  %t17 = sdiv i32 %t15, %t16
  %t18 = add i32 %t14, %t17
  store i32 %t18, i32* %t37, align 4
  %t20 = load i32, i32* %t37, align 4
  %t21 = sdiv i32 %t20, 2
  store i32 %t21, i32* %t37, align 4
  br label %B38
B41:                               	; preds = %B38
  br label %B40
B40:                               	; preds = %B41
  %t22 = load i32, i32* %t37, align 4
  ret i32 %t22
}
define i32 @main() {
B44:
  %t46 = alloca i32, align 4
  %t45 = alloca i32, align 4
  store i32 400, i32* %t45, align 4
  %t27 = load i32, i32* %t45, align 4
  %t28 = call i32 @fsqrt(i32 %t27)
  store i32 %t28, i32* %t46, align 4
  %t30 = load i32, i32* %t46, align 4
  call void @putint(i32 %t30)
  store i32 10, i32* %t46, align 4
  %t33 = load i32, i32* %t46, align 4
  call void @putch(i32 %t33)
  ret i32 0
}
declare void @putint(i32)
declare void @putch(i32)
