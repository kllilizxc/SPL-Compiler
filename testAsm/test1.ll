; ModuleID = 'Mine'
source_filename = "Mine"

@f = internal global i32, align 4
@k = internal global i32, align 4

declare i32 @printf(i8*, ...)

define void @hello() {
entry:
  store i32 0, i32* @k
  %k = load i32, i32* @k
  %0 = call i32 @go(i32 %k, i32 5)
  store i32 %0, i32* @f
  %1 = alloca [3 x i8]
  store [3 x i8] c"%d\00", [3 x i8]* %1
  %2 = bitcast [3 x i8]* %1 to i8*
  %f = load i32, i32* @f
  %3 = call i32 (i8*, ...) @printf(i8* %2, i32 %f)
  %4 = alloca [3 x i8]
  store [3 x i8] c"%d\00", [3 x i8]* %4
  %5 = bitcast [3 x i8]* %4 to i8*
  %k1 = load i32, i32* @k
  %6 = call i32 (i8*, ...) @printf(i8* %5, i32 %k1)
  ret void
}

define i32 @go(i32 %b, i32 %a) {
entry:
  %t = alloca double
  %fk = alloca i32
  %a2 = alloca i32
  %b1 = alloca i32
  %go = alloca i32
  store i32 %b, i32* %b1
  store i32 %a, i32* %a2
  %a23 = load i32, i32* %a2
  %0 = icmp ugt i32 %a23, 0
  br i1 %0, label %then, label %else

then:                                             ; preds = %entry
  %a24 = load i32, i32* %a2
  %b15 = load i32, i32* %b1
  %a26 = load i32, i32* %a2
  %1 = sub i32 %a26, 1
  %2 = call i32 @go(i32 %b15, i32 %1)
  %3 = mul i32 %a24, %2
  store i32 %3, i32* %go
  br label %final

else:                                             ; preds = %entry
  store i32 1, i32* %go
  br label %final

final:                                            ; preds = %else, %then
  %b17 = load i32, i32* %b1
  %go8 = load i32, i32* %go
  %4 = add i32 %b17, %go8
  store i32 %4, i32* %b1
  %k = load i32, i32* @k
  %go9 = load i32, i32* %go
  %5 = add i32 %k, %go9
  store i32 %5, i32* @k
  %go10 = load i32, i32* %go
  ret i32 %go10
}
