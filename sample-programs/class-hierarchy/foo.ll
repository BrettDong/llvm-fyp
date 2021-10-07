; ModuleID = 'foo.bc'
source_filename = "foo.cpp"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx11.0.0"

%class.Square = type { %class.Shape }
%class.Shape = type { i32 (...)** }

@_ZTV6Square = unnamed_addr constant { [5 x i8*] } { [5 x i8*] [i8* null, i8* bitcast ({ i8*, i8*, i8* }* @_ZTI6Square to i8*), i8* bitcast (%class.Square* (%class.Square*)* @_ZN6SquareD1Ev to i8*), i8* bitcast (void (%class.Square*)* @_ZN6SquareD0Ev to i8*), i8* bitcast (double (%class.Square*, double)* @_ZN6Square4AreaEd to i8*)] }, align 8
@_ZTVN10__cxxabiv120__si_class_type_infoE = external global i8*
@_ZTS6Square = constant [8 x i8] c"6Square\00", align 1
@_ZTVN10__cxxabiv117__class_type_infoE = external global i8*
@_ZTS5Shape = linkonce_odr hidden constant [7 x i8] c"5Shape\00", align 1
@_ZTI5Shape = linkonce_odr hidden constant { i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv117__class_type_infoE, i64 2) to i8*), i8* inttoptr (i64 add (i64 ptrtoint ([7 x i8]* @_ZTS5Shape to i64), i64 -9223372036854775808) to i8*) }, align 8
@_ZTI6Square = constant { i8*, i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv120__si_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @_ZTS6Square, i32 0, i32 0), i8* bitcast ({ i8*, i8* }* @_ZTI5Shape to i8*) }, align 8

; Function Attrs: noinline nounwind optnone ssp uwtable
define double @_ZN6Square4AreaEd(%class.Square* %0, double %1) unnamed_addr #0 align 2 {
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

; Function Attrs: noinline optnone ssp uwtable
define double @_Z3food(double %0) #1 {
  %2 = alloca double, align 8
  %3 = alloca %class.Shape*, align 8
  %4 = alloca double, align 8
  store double %0, double* %2, align 8
  %5 = load %class.Shape*, %class.Shape** %3, align 8
  %6 = load double, double* %2, align 8
  %7 = bitcast %class.Shape* %5 to double (%class.Shape*, double)***
  %8 = load double (%class.Shape*, double)**, double (%class.Shape*, double)*** %7, align 8
  %9 = getelementptr inbounds double (%class.Shape*, double)*, double (%class.Shape*, double)** %8, i64 2
  %10 = load double (%class.Shape*, double)*, double (%class.Shape*, double)** %9, align 8
  %11 = call double %10(%class.Shape* %5, double %6)
  store double %11, double* %4, align 8
  %12 = load double, double* %4, align 8
  ret double %12
}

; Function Attrs: noinline optnone ssp uwtable
define double @_Z3good(double %0) #1 {
  %2 = alloca double, align 8
  %3 = alloca %class.Square*, align 8
  %4 = alloca double, align 8
  store double %0, double* %2, align 8
  %5 = load %class.Square*, %class.Square** %3, align 8
  %6 = load double, double* %2, align 8
  %7 = bitcast %class.Square* %5 to double (%class.Square*, double)***
  %8 = load double (%class.Square*, double)**, double (%class.Square*, double)*** %7, align 8
  %9 = getelementptr inbounds double (%class.Square*, double)*, double (%class.Square*, double)** %8, i64 2
  %10 = load double (%class.Square*, double)*, double (%class.Square*, double)** %9, align 8
  %11 = call double %10(%class.Square* %5, double %6)
  store double %11, double* %4, align 8
  %12 = load double, double* %4, align 8
  ret double %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %class.Square* @_ZN6SquareD1Ev(%class.Square* returned %0) unnamed_addr #0 align 2 {
  %2 = alloca %class.Square*, align 8
  store %class.Square* %0, %class.Square** %2, align 8
  %3 = load %class.Square*, %class.Square** %2, align 8
  %4 = call %class.Square* @_ZN6SquareD2Ev(%class.Square* %3) #3
  ret %class.Square* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZN6SquareD0Ev(%class.Square* %0) unnamed_addr #0 align 2 {
  %2 = alloca %class.Square*, align 8
  store %class.Square* %0, %class.Square** %2, align 8
  %3 = load %class.Square*, %class.Square** %2, align 8
  %4 = call %class.Square* @_ZN6SquareD1Ev(%class.Square* %3) #3
  %5 = bitcast %class.Square* %3 to i8*
  call void @_ZdlPv(i8* %5) #4
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %class.Square* @_ZN6SquareD2Ev(%class.Square* returned %0) unnamed_addr #0 align 2 {
  %2 = alloca %class.Square*, align 8
  store %class.Square* %0, %class.Square** %2, align 8
  %3 = load %class.Square*, %class.Square** %2, align 8
  %4 = bitcast %class.Square* %3 to %class.Shape*
  %5 = call %class.Shape* @_ZN5ShapeD2Ev(%class.Shape* %4) #3
  ret %class.Square* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %class.Shape* @_ZN5ShapeD2Ev(%class.Shape* returned %0) unnamed_addr #0 align 2 {
  %2 = alloca %class.Shape*, align 8
  store %class.Shape* %0, %class.Shape** %2, align 8
  %3 = load %class.Shape*, %class.Shape** %2, align 8
  ret %class.Shape* %3
}

; Function Attrs: nobuiltin nounwind
declare void @_ZdlPv(i8*) #2

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-a12" "target-features"="+aes,+crc,+crypto,+fp-armv8,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.3a,+zcm,+zcz" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-a12" "target-features"="+aes,+crc,+crypto,+fp-armv8,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.3a,+zcm,+zcz" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nobuiltin nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-a12" "target-features"="+aes,+crc,+crypto,+fp-armv8,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.3a,+zcm,+zcz" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }
attributes #4 = { builtin nounwind }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 11, i32 3]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"Apple clang version 12.0.5 (clang-1205.0.22.9)"}
