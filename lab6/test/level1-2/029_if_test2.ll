define i32 @ifElseIf() {
B31:
  %t33 = alloca i32, align 4
  %t32 = alloca i32, align 4
  store i32 5, i32* %t32, align 4
  store i32 10, i32* %t33, align 4
  %t4 = load i32, i32* %t32, align 4
  %t5 = icmp eq i32 %t4, 6
  br i1 %t5, label %B34, label %B38
B34:                               	; preds = %B31, %B37
  %t9 = load i32, i32* %t32, align 4
  ret i32 %t9
  br label %B36
B38:                               	; preds = %B31
  br label %B37
B36:                               	; preds = %B34, %B46
  %t28 = load i32, i32* %t32, align 4
  ret i32 %t28
B37:                               	; preds = %B38
  %t6 = load i32, i32* %t33, align 4
  %t7 = icmp eq i32 %t6, 11
  br i1 %t7, label %B34, label %B41
B41:                               	; preds = %B37
  br label %B35
B35:                               	; preds = %B41
  %t10 = load i32, i32* %t33, align 4
  %t11 = icmp eq i32 %t10, 10
  br i1 %t11, label %B47, label %B48
B47:                               	; preds = %B35
  %t12 = load i32, i32* %t32, align 4
  %t13 = icmp eq i32 %t12, 1
  br i1 %t13, label %B44, label %B51
B48:                               	; preds = %B35
  br label %B45
B44:                               	; preds = %B47
  store i32 25, i32* %t32, align 4
  br label %B46
B51:                               	; preds = %B47
  br label %B45
B45:                               	; preds = %B48, %B51
  %t16 = load i32, i32* %t33, align 4
  %t17 = icmp eq i32 %t16, 10
  br i1 %t17, label %B57, label %B58
B46:                               	; preds = %B44, %B56
  br label %B36
B57:                               	; preds = %B45
  %t18 = load i32, i32* %t32, align 4
  %t19 = sub i32 0, 5
  %t20 = icmp eq i32 %t18, %t19
  br i1 %t20, label %B54, label %B61
B58:                               	; preds = %B45
  br label %B55
B54:                               	; preds = %B57
  %t23 = load i32, i32* %t32, align 4
  %t24 = add i32 %t23, 15
  store i32 %t24, i32* %t32, align 4
  br label %B56
B61:                               	; preds = %B57
  br label %B55
B55:                               	; preds = %B58, %B61
  %t26 = load i32, i32* %t32, align 4
  %t27 = sub i32 0, %t26
  store i32 %t27, i32* %t32, align 4
  br label %B56
B56:                               	; preds = %B54, %B55
  br label %B46
}
define i32 @main() {
B64:
  %t30 = call i32 @ifElseIf()
  call void @putint(i32 %t30)
  ret i32 0
}
declare void @putint(i32)
