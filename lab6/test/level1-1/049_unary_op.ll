define i32 @main() {
B14:
  %t15 = alloca i32, align 4
  store i32 10, i32* %t15, align 4
  %t2 = load i32, i32* %t15, align 4
  %t20 = icmp ne i32 %t2, 0
  %t3 = xor i1 %t20, true
  %t4 = xor i1 %t3, true
  %t5 = xor i1 %t4, true
  %t21 = zext i1 %t5 to i32
  %t6 = sub i32 0, %t21
  %t12 = icmp ne i32 %t6, 0
  br i1 %t12, label %B16, label %B19
B16:                               	; preds = %B14
  %t8 = sub i32 0, 1
  %t9 = sub i32 0, %t8
  %t10 = sub i32 0, %t9
  store i32 %t10, i32* %t15, align 4
  br label %B18
B19:                               	; preds = %B14
  br label %B17
B18:                               	; preds = %B16, %B17
  %t13 = load i32, i32* %t15, align 4
  ret i32 %t13
B17:                               	; preds = %B19
  store i32 0, i32* %t15, align 4
  br label %B18
}
