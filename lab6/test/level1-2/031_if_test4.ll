define i32 @if_ifElse_() {
B14:
  %t16 = alloca i32, align 4
  %t15 = alloca i32, align 4
  store i32 5, i32* %t15, align 4
  store i32 10, i32* %t16, align 4
  %t4 = load i32, i32* %t15, align 4
  %t5 = icmp eq i32 %t4, 5
  br i1 %t5, label %B17, label %B19
B17:                               	; preds = %B14
  %t6 = load i32, i32* %t16, align 4
  %t7 = icmp eq i32 %t6, 10
  br i1 %t7, label %B22, label %B25
B19:                               	; preds = %B14
  br label %B18
B22:                               	; preds = %B17
  store i32 25, i32* %t15, align 4
  br label %B24
B25:                               	; preds = %B17
  br label %B23
B18:                               	; preds = %B19, %B24
  %t12 = load i32, i32* %t15, align 4
  ret i32 %t12
B24:                               	; preds = %B22, %B23
  br label %B18
B23:                               	; preds = %B25
  %t10 = load i32, i32* %t15, align 4
  %t11 = add i32 %t10, 15
  store i32 %t11, i32* %t15, align 4
  br label %B24
}
define i32 @main() {
B28:
  %t13 = call i32 @if_ifElse_()
  ret i32 %t13
}
