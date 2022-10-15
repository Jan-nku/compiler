@b = dso_local global i32 1, align 4
@d = dso_local constant i32 1, align 4
@a = dso_local global i32 0, align 4
@c = dso_local constant i32 0, align 4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 1, i32* %2, align 4
  store i32 1, i32* %4, align 4
  ret i32 0
}