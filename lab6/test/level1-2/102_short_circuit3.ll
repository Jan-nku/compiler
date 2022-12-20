@a = global i32 0, align 4
@b = global i32 0, align 4
@d = global i32 0, align 4
define i32 @set_a(i32 %t3) {
B147:
  %t148 = alloca i32, align 4
  store i32 %t3, i32* %t148, align 4
  %t6 = load i32, i32* %t148, align 4
  store i32 %t6, i32* @a, align 4
  %t7 = load i32, i32* @a, align 4
  ret i32 %t7
}
define i32 @set_b(i32 %t8) {
B149:
  %t150 = alloca i32, align 4
  store i32 %t8, i32* %t150, align 4
  %t11 = load i32, i32* %t150, align 4
  store i32 %t11, i32* @b, align 4
  %t12 = load i32, i32* @b, align 4
  ret i32 %t12
}
define i32 @set_d(i32 %t13) {
B151:
  %t152 = alloca i32, align 4
  store i32 %t13, i32* %t152, align 4
  %t16 = load i32, i32* %t152, align 4
  store i32 %t16, i32* @d, align 4
  %t17 = load i32, i32* @d, align 4
  ret i32 %t17
}
define i32 @main() {
B153:
  %t239 = alloca i32, align 4
  %t238 = alloca i32, align 4
  %t237 = alloca i32, align 4
  %t236 = alloca i32, align 4
  %t235 = alloca i32, align 4
  %t172 = alloca i32, align 4
  store i32 2, i32* @a, align 4
  store i32 3, i32* @b, align 4
  %t20 = call i32 @set_a(i32 0)
  %t22 = icmp ne i32 %t20, 0
  br i1 %t22, label %B156, label %B157
B156:                               	; preds = %B153
  %t21 = call i32 @set_b(i32 1)
  %t23 = icmp ne i32 %t21, 0
  br i1 %t23, label %B154, label %B160
B157:                               	; preds = %B153
  br label %B155
B154:                               	; preds = %B156
  br label %B155
B160:                               	; preds = %B156
  br label %B155
B155:                               	; preds = %B154, %B157, %B160
  %t26 = load i32, i32* @a, align 4
  call void @putint(i32 %t26)
  call void @putch(i32 32)
  %t29 = load i32, i32* @b, align 4
  call void @putint(i32 %t29)
  call void @putch(i32 32)
  store i32 2, i32* @a, align 4
  store i32 3, i32* @b, align 4
  %t33 = call i32 @set_a(i32 0)
  %t35 = icmp ne i32 %t33, 0
  br i1 %t35, label %B165, label %B166
B165:                               	; preds = %B155
  %t34 = call i32 @set_b(i32 1)
  %t36 = icmp ne i32 %t34, 0
  br i1 %t36, label %B163, label %B169
B166:                               	; preds = %B155
  br label %B164
B163:                               	; preds = %B165
  br label %B164
B169:                               	; preds = %B165
  br label %B164
B164:                               	; preds = %B163, %B166, %B169
  %t39 = load i32, i32* @a, align 4
  call void @putint(i32 %t39)
  call void @putch(i32 32)
  %t42 = load i32, i32* @b, align 4
  call void @putint(i32 %t42)
  call void @putch(i32 10)
  store i32 1, i32* %t172, align 4
  store i32 2, i32* @d, align 4
  %t46 = load i32, i32* %t172, align 4
  %t47 = icmp sge i32 %t46, 1
  br i1 %t47, label %B175, label %B176
B175:                               	; preds = %B164
  %t48 = call i32 @set_d(i32 3)
  %t49 = icmp ne i32 %t48, 0
  br i1 %t49, label %B173, label %B179
B176:                               	; preds = %B164
  br label %B174
B173:                               	; preds = %B175
  br label %B174
B179:                               	; preds = %B175
  br label %B174
B174:                               	; preds = %B173, %B176, %B179
  %t52 = load i32, i32* @d, align 4
  call void @putint(i32 %t52)
  call void @putch(i32 32)
  %t54 = load i32, i32* %t172, align 4
  %t55 = icmp sle i32 %t54, 1
  br i1 %t55, label %B182, label %B185
B182:                               	; preds = %B174, %B184
  br label %B183
B185:                               	; preds = %B174
  br label %B184
B183:                               	; preds = %B182, %B188
  %t60 = load i32, i32* @d, align 4
  call void @putint(i32 %t60)
  call void @putch(i32 10)
  %t62 = add i32 2, 1
  %t63 = sub i32 3, %t62
  %t64 = icmp sge i32 16, %t63
  br i1 %t64, label %B191, label %B193
B184:                               	; preds = %B185
  %t56 = call i32 @set_d(i32 4)
  %t57 = icmp ne i32 %t56, 0
  br i1 %t57, label %B182, label %B188
B191:                               	; preds = %B183
  call void @putch(i32 65)
  br label %B192
B193:                               	; preds = %B183
  br label %B192
B188:                               	; preds = %B184
  br label %B183
B192:                               	; preds = %B191, %B193
  %t66 = sub i32 25, 7
  %t67 = mul i32 6, 3
  %t68 = sub i32 36, %t67
  %t69 = icmp ne i32 %t66, %t68
  br i1 %t69, label %B196, label %B198
B196:                               	; preds = %B192
  call void @putch(i32 66)
  br label %B197
B198:                               	; preds = %B192
  br label %B197
B197:                               	; preds = %B196, %B198
  %t71 = icmp slt i32 1, 8
  %t72 = srem i32 7, 2
  %t207 = zext i1 %t71 to i32
  %t73 = icmp ne i32 %t207, %t72
  br i1 %t73, label %B201, label %B203
B201:                               	; preds = %B197
  call void @putch(i32 67)
  br label %B202
B203:                               	; preds = %B197
  br label %B202
B202:                               	; preds = %B201, %B203
  %t75 = icmp sgt i32 3, 4
  %t216 = zext i1 %t75 to i32
  %t76 = icmp eq i32 %t216, 0
  br i1 %t76, label %B210, label %B212
B210:                               	; preds = %B202
  call void @putch(i32 68)
  br label %B211
B212:                               	; preds = %B202
  br label %B211
B211:                               	; preds = %B210, %B212
  %t78 = icmp sle i32 102, 63
  %t225 = zext i1 %t78 to i32
  %t79 = icmp eq i32 1, %t225
  br i1 %t79, label %B219, label %B221
B219:                               	; preds = %B211
  call void @putch(i32 69)
  br label %B220
B221:                               	; preds = %B211
  br label %B220
B220:                               	; preds = %B219, %B221
  %t81 = sub i32 5, 6
  %t231 = icmp ne i32 0, 0
  %t82 = xor i1 %t231, true
  %t232 = zext i1 %t82 to i32
  %t83 = sub i32 0, %t232
  %t84 = icmp eq i32 %t81, %t83
  br i1 %t84, label %B228, label %B230
B228:                               	; preds = %B220
  call void @putch(i32 70)
  br label %B229
B230:                               	; preds = %B220
  br label %B229
B229:                               	; preds = %B228, %B230
  call void @putch(i32 10)
  store i32 0, i32* %t235, align 4
  store i32 1, i32* %t236, align 4
  store i32 2, i32* %t237, align 4
  store i32 3, i32* %t238, align 4
  store i32 4, i32* %t239, align 4
  br label %B240
B240:                               	; preds = %B229, %B241
  %t92 = load i32, i32* %t235, align 4
  %t94 = icmp ne i32 %t92, 0
  br i1 %t94, label %B243, label %B244
B243:                               	; preds = %B240
  %t93 = load i32, i32* %t236, align 4
  %t95 = icmp ne i32 %t93, 0
  br i1 %t95, label %B241, label %B247
B244:                               	; preds = %B240
  br label %B242
B241:                               	; preds = %B243
  call void @putch(i32 32)
  br label %B240
B247:                               	; preds = %B243
  br label %B242
B242:                               	; preds = %B244, %B247
  %t98 = load i32, i32* %t235, align 4
  %t100 = icmp ne i32 %t98, 0
  br i1 %t100, label %B250, label %B253
B250:                               	; preds = %B242, %B252
  call void @putch(i32 67)
  br label %B251
B253:                               	; preds = %B242
  br label %B252
B251:                               	; preds = %B250, %B256
  %t104 = load i32, i32* %t235, align 4
  %t105 = load i32, i32* %t236, align 4
  %t106 = icmp sge i32 %t104, %t105
  br i1 %t106, label %B259, label %B262
B252:                               	; preds = %B253
  %t99 = load i32, i32* %t236, align 4
  %t101 = icmp ne i32 %t99, 0
  br i1 %t101, label %B250, label %B256
B259:                               	; preds = %B251, %B261
  call void @putch(i32 72)
  br label %B260
B262:                               	; preds = %B251
  br label %B261
B256:                               	; preds = %B252
  br label %B251
B260:                               	; preds = %B259, %B265
  %t112 = load i32, i32* %t237, align 4
  %t113 = load i32, i32* %t236, align 4
  %t114 = icmp sge i32 %t112, %t113
  br i1 %t114, label %B270, label %B271
B261:                               	; preds = %B262
  %t107 = load i32, i32* %t236, align 4
  %t108 = load i32, i32* %t235, align 4
  %t109 = icmp sle i32 %t107, %t108
  br i1 %t109, label %B259, label %B265
B270:                               	; preds = %B260
  %t115 = load i32, i32* %t239, align 4
  %t116 = load i32, i32* %t238, align 4
  %t117 = icmp ne i32 %t115, %t116
  br i1 %t117, label %B268, label %B274
B271:                               	; preds = %B260
  br label %B269
B265:                               	; preds = %B261
  br label %B260
B268:                               	; preds = %B270
  call void @putch(i32 73)
  br label %B269
B274:                               	; preds = %B270
  br label %B269
B269:                               	; preds = %B268, %B271, %B274
  %t120 = load i32, i32* %t235, align 4
  %t121 = load i32, i32* %t236, align 4
  %t282 = icmp ne i32 %t121, 0
  %t122 = xor i1 %t282, true
  %t283 = zext i1 %t122 to i32
  %t123 = icmp eq i32 %t120, %t283
  br i1 %t123, label %B280, label %B281
B280:                               	; preds = %B269
  %t124 = load i32, i32* %t238, align 4
  %t125 = load i32, i32* %t238, align 4
  %t126 = icmp slt i32 %t124, %t125
  br i1 %t126, label %B277, label %B286
B281:                               	; preds = %B269
  br label %B279
B277:                               	; preds = %B279, %B280
  call void @putch(i32 74)
  br label %B278
B286:                               	; preds = %B280
  br label %B279
B279:                               	; preds = %B281, %B286
  %t128 = load i32, i32* %t239, align 4
  %t129 = load i32, i32* %t239, align 4
  %t130 = icmp sge i32 %t128, %t129
  br i1 %t130, label %B277, label %B289
B278:                               	; preds = %B277, %B289
  %t133 = load i32, i32* %t235, align 4
  %t134 = load i32, i32* %t236, align 4
  %t296 = icmp ne i32 %t134, 0
  %t135 = xor i1 %t296, true
  %t297 = zext i1 %t135 to i32
  %t136 = icmp eq i32 %t133, %t297
  br i1 %t136, label %B292, label %B295
B289:                               	; preds = %B279
  br label %B278
B292:                               	; preds = %B278, %B300
  call void @putch(i32 75)
  br label %B293
B295:                               	; preds = %B278
  br label %B294
B293:                               	; preds = %B292, %B301, %B304
  call void @putch(i32 10)
  ret i32 0
B294:                               	; preds = %B295
  %t137 = load i32, i32* %t238, align 4
  %t138 = load i32, i32* %t238, align 4
  %t139 = icmp slt i32 %t137, %t138
  br i1 %t139, label %B300, label %B301
B300:                               	; preds = %B294
  %t140 = load i32, i32* %t239, align 4
  %t141 = load i32, i32* %t239, align 4
  %t142 = icmp sge i32 %t140, %t141
  br i1 %t142, label %B292, label %B304
B301:                               	; preds = %B294
  br label %B293
B304:                               	; preds = %B300
  br label %B293
}
declare void @putint(i32)
declare void @putch(i32)
