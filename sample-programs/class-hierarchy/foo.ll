; ModuleID = 'foo.bc'
source_filename = "foo.cpp"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx11.0.0"

%class.Square = type { %class.Shape }
%class.Shape = type { i32 (...)** }
%class.Circle = type { %class.Shape }

@_ZTV6Square = unnamed_addr constant { [5 x i8*] } { [5 x i8*] [i8* null, i8* bitcast ({ i8*, i8*, i8* }* @_ZTI6Square to i8*), i8* bitcast (%class.Square* (%class.Square*)* @_ZN6SquareD1Ev to i8*), i8* bitcast (void (%class.Square*)* @_ZN6SquareD0Ev to i8*), i8* bitcast (double (%class.Square*, double)* @_ZN6Square4AreaEd to i8*)] }, align 8
@_ZTVN10__cxxabiv120__si_class_type_infoE = external global i8*
@_ZTS6Square = constant [8 x i8] c"6Square\00", align 1
@_ZTVN10__cxxabiv117__class_type_infoE = external global i8*
@_ZTS5Shape = linkonce_odr hidden constant [7 x i8] c"5Shape\00", align 1
@_ZTI5Shape = linkonce_odr hidden constant { i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv117__class_type_infoE, i64 2) to i8*), i8* inttoptr (i64 add (i64 ptrtoint ([7 x i8]* @_ZTS5Shape to i64), i64 -9223372036854775808) to i8*) }, align 8
@_ZTI6Square = constant { i8*, i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv120__si_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @_ZTS6Square, i32 0, i32 0), i8* bitcast ({ i8*, i8* }* @_ZTI5Shape to i8*) }, align 8
@_ZTV6Circle = unnamed_addr constant { [5 x i8*] } { [5 x i8*] [i8* null, i8* bitcast ({ i8*, i8*, i8* }* @_ZTI6Circle to i8*), i8* bitcast (%class.Circle* (%class.Circle*)* @_ZN6CircleD1Ev to i8*), i8* bitcast (void (%class.Circle*)* @_ZN6CircleD0Ev to i8*), i8* bitcast (double (%class.Circle*, double)* @_ZN6Circle4AreaEd to i8*)] }, align 8
@_ZTS6Circle = constant [8 x i8] c"6Circle\00", align 1
@_ZTI6Circle = constant { i8*, i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv120__si_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @_ZTS6Circle, i32 0, i32 0), i8* bitcast ({ i8*, i8* }* @_ZTI5Shape to i8*) }, align 8

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define double @_ZN6Square4AreaEd(%class.Square* nonnull align 8 dereferenceable(8) %0, double %1) unnamed_addr #0 align 2 {
  %3 = alloca %class.Square*, align 8
  %4 = alloca double, align 8
  store %class.Square* %0, %class.Square** %3, align 8
  store double %1, double* %4, align 8
  %5 = load %class.Square*, %class.Square** %3, align 8
  %6 = load double, double* %4, align 8
  %7 = load double, double* %4, align 8
  %8 = fmul double %6, %7
  ret double %8
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define double @_ZN6Circle4AreaEd(%class.Circle* nonnull align 8 dereferenceable(8) %0, double %1) unnamed_addr #0 align 2 {
  %3 = alloca %class.Circle*, align 8
  %4 = alloca double, align 8
  store %class.Circle* %0, %class.Circle** %3, align 8
  store double %1, double* %4, align 8
  %5 = load %class.Circle*, %class.Circle** %3, align 8
  %6 = load double, double* %4, align 8
  %7 = fmul double 0x400921FB4D12D84A, %6
  %8 = load double, double* %4, align 8
  %9 = fmul double %7, %8
  ret double %9
}

; Function Attrs: mustprogress noinline optnone ssp uwtable
define double @_Z3fooP5Shaped(%class.Shape* %0, double %1) #1 {
  %3 = alloca %class.Shape*, align 8
  %4 = alloca double, align 8
  %5 = alloca double, align 8
  store %class.Shape* %0, %class.Shape** %3, align 8
  store double %1, double* %4, align 8
  %6 = load %class.Shape*, %class.Shape** %3, align 8
  %7 = load double, double* %4, align 8
  %8 = bitcast %class.Shape* %6 to double (%class.Shape*, double)***
  %9 = load double (%class.Shape*, double)**, double (%class.Shape*, double)*** %8, align 8
  %10 = getelementptr inbounds double (%class.Shape*, double)*, double (%class.Shape*, double)** %9, i64 2
  %11 = load double (%class.Shape*, double)*, double (%class.Shape*, double)** %10, align 8
  %12 = call double %11(%class.Shape* nonnull align 8 dereferenceable(8) %6, double %7)
  store double %12, double* %5, align 8
  %13 = load double, double* %5, align 8
  ret double %13
}

; Function Attrs: mustprogress noinline optnone ssp uwtable
define double @_Z3gooP6Squared(%class.Square* %0, double %1) #1 {
  %3 = alloca %class.Square*, align 8
  %4 = alloca double, align 8
  %5 = alloca double, align 8
  store %class.Square* %0, %class.Square** %3, align 8
  store double %1, double* %4, align 8
  %6 = load %class.Square*, %class.Square** %3, align 8
  %7 = load double, double* %4, align 8
  %8 = bitcast %class.Square* %6 to double (%class.Square*, double)***
  %9 = load double (%class.Square*, double)**, double (%class.Square*, double)*** %8, align 8
  %10 = getelementptr inbounds double (%class.Square*, double)*, double (%class.Square*, double)** %9, i64 2
  %11 = load double (%class.Square*, double)*, double (%class.Square*, double)** %10, align 8
  %12 = call double %11(%class.Square* nonnull align 8 dereferenceable(8) %6, double %7)
  store double %12, double* %5, align 8
  %13 = load double, double* %5, align 8
  ret double %13
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %class.Square* @_ZN6SquareD1Ev(%class.Square* nonnull returned align 8 dereferenceable(8) %0) unnamed_addr #2 align 2 {
  %2 = alloca %class.Square*, align 8
  store %class.Square* %0, %class.Square** %2, align 8
  %3 = load %class.Square*, %class.Square** %2, align 8
  %4 = call %class.Square* @_ZN6SquareD2Ev(%class.Square* nonnull align 8 dereferenceable(8) %3) #4
  ret %class.Square* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZN6SquareD0Ev(%class.Square* nonnull align 8 dereferenceable(8) %0) unnamed_addr #2 align 2 {
  %2 = alloca %class.Square*, align 8
  store %class.Square* %0, %class.Square** %2, align 8
  %3 = load %class.Square*, %class.Square** %2, align 8
  %4 = call %class.Square* @_ZN6SquareD1Ev(%class.Square* nonnull align 8 dereferenceable(8) %3) #4
  %5 = bitcast %class.Square* %3 to i8*
  call void @_ZdlPv(i8* %5) #5
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %class.Circle* @_ZN6CircleD1Ev(%class.Circle* nonnull returned align 8 dereferenceable(8) %0) unnamed_addr #2 align 2 {
  %2 = alloca %class.Circle*, align 8
  store %class.Circle* %0, %class.Circle** %2, align 8
  %3 = load %class.Circle*, %class.Circle** %2, align 8
  %4 = call %class.Circle* @_ZN6CircleD2Ev(%class.Circle* nonnull align 8 dereferenceable(8) %3) #4
  ret %class.Circle* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZN6CircleD0Ev(%class.Circle* nonnull align 8 dereferenceable(8) %0) unnamed_addr #2 align 2 {
  %2 = alloca %class.Circle*, align 8
  store %class.Circle* %0, %class.Circle** %2, align 8
  %3 = load %class.Circle*, %class.Circle** %2, align 8
  %4 = call %class.Circle* @_ZN6CircleD1Ev(%class.Circle* nonnull align 8 dereferenceable(8) %3) #4
  %5 = bitcast %class.Circle* %3 to i8*
  call void @_ZdlPv(i8* %5) #5
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %class.Square* @_ZN6SquareD2Ev(%class.Square* nonnull returned align 8 dereferenceable(8) %0) unnamed_addr #2 align 2 {
  %2 = alloca %class.Square*, align 8
  store %class.Square* %0, %class.Square** %2, align 8
  %3 = load %class.Square*, %class.Square** %2, align 8
  %4 = bitcast %class.Square* %3 to %class.Shape*
  %5 = call %class.Shape* @_ZN5ShapeD2Ev(%class.Shape* nonnull align 8 dereferenceable(8) %4) #4
  ret %class.Square* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %class.Shape* @_ZN5ShapeD2Ev(%class.Shape* nonnull returned align 8 dereferenceable(8) %0) unnamed_addr #2 align 2 {
  %2 = alloca %class.Shape*, align 8
  store %class.Shape* %0, %class.Shape** %2, align 8
  %3 = load %class.Shape*, %class.Shape** %2, align 8
  ret %class.Shape* %3
}

; Function Attrs: nobuiltin nounwind
declare void @_ZdlPv(i8*) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %class.Circle* @_ZN6CircleD2Ev(%class.Circle* nonnull returned align 8 dereferenceable(8) %0) unnamed_addr #2 align 2 {
  %2 = alloca %class.Circle*, align 8
  store %class.Circle* %0, %class.Circle** %2, align 8
  %3 = load %class.Circle*, %class.Circle** %2, align 8
  %4 = bitcast %class.Circle* %3 to %class.Shape*
  %5 = call %class.Shape* @_ZN5ShapeD2Ev(%class.Shape* nonnull align 8 dereferenceable(8) %4) #4
  ret %class.Circle* %3
}

attributes #0 = { mustprogress noinline nounwind optnone ssp uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.5a,+zcm,+zcz" }
attributes #1 = { mustprogress noinline optnone ssp uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.5a,+zcm,+zcz" }
attributes #2 = { noinline nounwind optnone ssp uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.5a,+zcm,+zcz" }
attributes #3 = { nobuiltin nounwind "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.5a,+zcm,+zcz" }
attributes #4 = { nounwind }
attributes #5 = { builtin nounwind }

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
