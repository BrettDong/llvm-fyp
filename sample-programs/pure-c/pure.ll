; ModuleID = 'pure.bc'
source_filename = "pure.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx11.0.0"

%struct.structA = type { i32 (i32, i32)* }
%struct.structB = type { i32 (i32, i32)*, %struct.structA }
%struct.structC = type { i32 (i32, i32)*, %struct.structA, %struct.structB }

@__const.funcZ.a = private unnamed_addr constant %struct.structA { i32 (i32, i32)* @funcA }, align 8
@__const.funcZ.b = private unnamed_addr constant %struct.structB { i32 (i32, i32)* @funcB, %struct.structA { i32 (i32, i32)* @funcD } }, align 8
@__const.funcZ.c = private unnamed_addr constant %struct.structC { i32 (i32, i32)* @funcC, %struct.structA { i32 (i32, i32)* @funcE }, %struct.structB { i32 (i32, i32)* @funcF, %struct.structA { i32 (i32, i32)* @funcG } } }, align 8

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @funcA(i32 %0, i32 %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = load i32, i32* %4, align 4
  %7 = add nsw i32 %5, %6
  ret i32 %7
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @funcB(i32 %0, i32 %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = load i32, i32* %4, align 4
  %7 = mul nsw i32 %5, %6
  ret i32 %7
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @funcC(i32 %0, i32 %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = load i32, i32* %4, align 4
  %7 = sub nsw i32 %5, %6
  ret i32 %7
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @funcD(i32 %0, i32 %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = load i32, i32* %4, align 4
  %7 = mul nsw i32 %5, %6
  %8 = load i32, i32* %3, align 4
  %9 = add nsw i32 %7, %8
  ret i32 %9
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @funcE(i32 %0, i32 %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = load i32, i32* %4, align 4
  %7 = mul nsw i32 %5, %6
  %8 = load i32, i32* %3, align 4
  %9 = sub nsw i32 %7, %8
  ret i32 %9
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @funcF(i32 %0, i32 %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = load i32, i32* %4, align 4
  %7 = mul nsw i32 %5, %6
  %8 = load i32, i32* %4, align 4
  %9 = add nsw i32 %7, %8
  ret i32 %9
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @funcG(i32 %0, i32 %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = load i32, i32* %4, align 4
  %7 = mul nsw i32 %5, %6
  %8 = load i32, i32* %4, align 4
  %9 = sub nsw i32 %7, %8
  ret i32 %9
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @funcZ() #0 {
  %1 = alloca %struct.structA, align 8
  %2 = alloca %struct.structB, align 8
  %3 = alloca %struct.structC, align 8
  %4 = bitcast %struct.structA* %1 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %4, i8* align 8 bitcast (%struct.structA* @__const.funcZ.a to i8*), i64 8, i1 false)
  %5 = bitcast %struct.structB* %2 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %5, i8* align 8 bitcast (%struct.structB* @__const.funcZ.b to i8*), i64 16, i1 false)
  %6 = bitcast %struct.structC* %3 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %6, i8* align 8 bitcast (%struct.structC* @__const.funcZ.c to i8*), i64 32, i1 false)
  %7 = getelementptr inbounds %struct.structB, %struct.structB* %2, i32 0, i32 1
  %8 = getelementptr inbounds %struct.structA, %struct.structA* %7, i32 0, i32 0
  %9 = load i32 (i32, i32)*, i32 (i32, i32)** %8, align 8
  %10 = call i32 %9(i32 2, i32 3)
  ret i32 %10
}

; Function Attrs: argmemonly nofree nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #1

attributes #0 = { noinline nounwind optnone ssp uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.5a,+zcm,+zcz" }
attributes #1 = { argmemonly nofree nounwind willreturn }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7}
!llvm.ident = !{!8}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 1, !"branch-target-enforcement", i32 0}
!2 = !{i32 1, !"sign-return-address", i32 0}
!3 = !{i32 1, !"sign-return-address-all", i32 0}
!4 = !{i32 1, !"sign-return-address-with-bkey", i32 0}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 1}
!8 = !{!"Homebrew clang version 13.0.0"}
