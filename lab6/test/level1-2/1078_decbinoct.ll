define i32 @dec2bin(i32 %t0) {
B39:
  %t44 = alloca i32, align 4
  %t43 = alloca i32, align 4
  %t42 = alloca i32, align 4
  %t41 = alloca i32, align 4
  %t40 = alloca i32, align 4
  store i32 %t0, i32* %t40, align 4
  store i32 0, i32* %t41, align 4
  store i32 1, i32* %t42, align 4
  %t9 = load i32, i32* %t40, align 4
  store i32 %t9, i32* %t44, align 4
  br label %B45
B45:                               	; preds = %B39, %B46
  %t10 = load i32, i32* %t44, align 4
  %t11 = icmp ne i32 %t10, 0
  br i1 %t11, label %B46, label %B48
B46:                               	; preds = %B45
  %t13 = load i32, i32* %t44, align 4
  %t14 = srem i32 %t13, 2
  store i32 %t14, i32* %t43, align 4
  %t16 = load i32, i32* %t42, align 4
  %t17 = load i32, i32* %t43, align 4
  %t18 = mul i32 %t16, %t17
  %t19 = load i32, i32* %t41, align 4
  %t20 = add i32 %t18, %t19
  store i32 %t20, i32* %t41, align 4
  %t22 = load i32, i32* %t42, align 4
  %t23 = mul i32 %t22, 10
  store i32 %t23, i32* %t42, align 4
  %t25 = load i32, i32* %t44, align 4
  %t26 = sdiv i32 %t25, 2
  store i32 %t26, i32* %t44, align 4
  br label %B45
B48:                               	; preds = %B45
  br label %B47
B47:                               	; preds = %B48
  %t27 = load i32, i32* %t41, align 4
  ret i32 %t27
}
define i32 @main() {
B51:
  %t53 = alloca i32, align 4
  %t52 = alloca i32, align 4
  store i32 400, i32* %t52, align 4
  %t32 = load i32, i32* %t52, align 4
  %t33 = call i32 @dec2bin(i32 %t32)
  store i32 %t33, i32* %t53, align 4
  %t35 = load i32, i32* %t53, align 4
  call void @putint(i32 %t35)
  store i32 10, i32* %t53, align 4
  %t38 = load i32, i32* %t53, align 4
  call void @putch(i32 %t38)
  ret i32 0
}
declare void @putint(i32)
declare void @putch(i32)
