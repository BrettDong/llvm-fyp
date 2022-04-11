; ModuleID = 'multi-inheritance.bc'
source_filename = "multi-inheritance.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%class.C = type { %class.A, %class.B }
%class.A = type { i32 (...)** }
%class.B = type { i32 (...)** }
%class.E = type { %class.C, %class.D }
%class.D = type { i32 (...)** }

$_ZN1EC2Ev = comdat any

$_ZN1CC2Ev = comdat any

$_ZN1DC2Ev = comdat any

$_ZN1C1fEv = comdat any

$_ZN1C1gEv = comdat any

$_ZN1E1hEv = comdat any

$_ZN1E1xEv = comdat any

$_ZThn8_N1C1gEv = comdat any

$_ZThn8_N1E1hEv = comdat any

$_ZThn16_N1E1xEv = comdat any

$_ZN1AC2Ev = comdat any

$_ZN1BC2Ev = comdat any

$_ZN1C1hEv = comdat any

$_ZThn8_N1C1hEv = comdat any

$_ZN1A1fEv = comdat any

$_ZN1B1gEv = comdat any

$_ZN1B1hEv = comdat any

$_ZN1D1xEv = comdat any

$_ZTV1E = comdat any

$_ZTS1E = comdat any

$_ZTS1C = comdat any

$_ZTS1A = comdat any

$_ZTI1A = comdat any

$_ZTS1B = comdat any

$_ZTI1B = comdat any

$_ZTI1C = comdat any

$_ZTS1D = comdat any

$_ZTI1D = comdat any

$_ZTI1E = comdat any

$_ZTV1C = comdat any

$_ZTV1A = comdat any

$_ZTV1B = comdat any

$_ZTV1D = comdat any

@_ZTV1E = linkonce_odr dso_local unnamed_addr constant { [6 x i8*], [4 x i8*], [3 x i8*] } { [6 x i8*] [i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64, i8*, i64 }* @_ZTI1E to i8*), i8* bitcast (i32 (%class.C*)* @_ZN1C1fEv to i8*), i8* bitcast (i32 (%class.C*)* @_ZN1C1gEv to i8*), i8* bitcast (i32 (%class.E*)* @_ZN1E1hEv to i8*), i8* bitcast (i32 (%class.E*)* @_ZN1E1xEv to i8*)], [4 x i8*] [i8* inttoptr (i64 -8 to i8*), i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64, i8*, i64 }* @_ZTI1E to i8*), i8* bitcast (i32 (%class.C*)* @_ZThn8_N1C1gEv to i8*), i8* bitcast (i32 (%class.E*)* @_ZThn8_N1E1hEv to i8*)], [3 x i8*] [i8* inttoptr (i64 -16 to i8*), i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64, i8*, i64 }* @_ZTI1E to i8*), i8* bitcast (i32 (%class.E*)* @_ZThn16_N1E1xEv to i8*)] }, comdat, align 8
@_ZTVN10__cxxabiv121__vmi_class_type_infoE = external dso_local global i8*
@_ZTS1E = linkonce_odr dso_local constant [3 x i8] c"1E\00", comdat, align 1
@_ZTS1C = linkonce_odr dso_local constant [3 x i8] c"1C\00", comdat, align 1
@_ZTVN10__cxxabiv117__class_type_infoE = external dso_local global i8*
@_ZTS1A = linkonce_odr dso_local constant [3 x i8] c"1A\00", comdat, align 1
@_ZTI1A = linkonce_odr dso_local constant { i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv117__class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1A, i32 0, i32 0) }, comdat, align 8
@_ZTS1B = linkonce_odr dso_local constant [3 x i8] c"1B\00", comdat, align 1
@_ZTI1B = linkonce_odr dso_local constant { i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv117__class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1B, i32 0, i32 0) }, comdat, align 8
@_ZTI1C = linkonce_odr dso_local constant { i8*, i8*, i32, i32, i8*, i64, i8*, i64 } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv121__vmi_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1C, i32 0, i32 0), i32 0, i32 2, i8* bitcast ({ i8*, i8* }* @_ZTI1A to i8*), i64 2, i8* bitcast ({ i8*, i8* }* @_ZTI1B to i8*), i64 2050 }, comdat, align 8
@_ZTS1D = linkonce_odr dso_local constant [3 x i8] c"1D\00", comdat, align 1
@_ZTI1D = linkonce_odr dso_local constant { i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv117__class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1D, i32 0, i32 0) }, comdat, align 8
@_ZTI1E = linkonce_odr dso_local constant { i8*, i8*, i32, i32, i8*, i64, i8*, i64 } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv121__vmi_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1E, i32 0, i32 0), i32 0, i32 2, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64, i8*, i64 }* @_ZTI1C to i8*), i64 2, i8* bitcast ({ i8*, i8* }* @_ZTI1D to i8*), i64 4098 }, comdat, align 8
@_ZTV1C = linkonce_odr dso_local unnamed_addr constant { [5 x i8*], [4 x i8*] } { [5 x i8*] [i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64, i8*, i64 }* @_ZTI1C to i8*), i8* bitcast (i32 (%class.C*)* @_ZN1C1fEv to i8*), i8* bitcast (i32 (%class.C*)* @_ZN1C1gEv to i8*), i8* bitcast (i32 (%class.C*)* @_ZN1C1hEv to i8*)], [4 x i8*] [i8* inttoptr (i64 -8 to i8*), i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64, i8*, i64 }* @_ZTI1C to i8*), i8* bitcast (i32 (%class.C*)* @_ZThn8_N1C1gEv to i8*), i8* bitcast (i32 (%class.C*)* @_ZThn8_N1C1hEv to i8*)] }, comdat, align 8
@_ZTV1A = linkonce_odr dso_local unnamed_addr constant { [3 x i8*] } { [3 x i8*] [i8* null, i8* bitcast ({ i8*, i8* }* @_ZTI1A to i8*), i8* bitcast (i32 (%class.A*)* @_ZN1A1fEv to i8*)] }, comdat, align 8
@_ZTV1B = linkonce_odr dso_local unnamed_addr constant { [4 x i8*] } { [4 x i8*] [i8* null, i8* bitcast ({ i8*, i8* }* @_ZTI1B to i8*), i8* bitcast (i32 (%class.B*)* @_ZN1B1gEv to i8*), i8* bitcast (i32 (%class.B*)* @_ZN1B1hEv to i8*)] }, comdat, align 8
@_ZTV1D = linkonce_odr dso_local unnamed_addr constant { [3 x i8*] } { [3 x i8*] [i8* null, i8* bitcast ({ i8*, i8* }* @_ZTI1D to i8*), i8* bitcast (i32 (%class.D*)* @_ZN1D1xEv to i8*)] }, comdat, align 8

; Function Attrs: mustprogress noinline norecurse optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca %class.C*, align 8
  store i32 0, i32* %1, align 4
  %3 = call noalias nonnull i8* @_Znwm(i64 24) #6
  %4 = bitcast i8* %3 to %class.E*
  %5 = bitcast %class.E* %4 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %5, i8 0, i64 24, i1 false)
  call void @_ZN1EC2Ev(%class.E* nonnull align 8 dereferenceable(24) %4) #7
  %6 = bitcast %class.E* %4 to %class.C*
  store %class.C* %6, %class.C** %2, align 8
  %7 = load %class.C*, %class.C** %2, align 8
  %8 = bitcast %class.C* %7 to i32 (%class.C*)***
  %9 = load i32 (%class.C*)**, i32 (%class.C*)*** %8, align 8
  %10 = getelementptr inbounds i32 (%class.C*)*, i32 (%class.C*)** %9, i64 2
  %11 = load i32 (%class.C*)*, i32 (%class.C*)** %10, align 8
  %12 = call i32 %11(%class.C* nonnull align 8 dereferenceable(16) %7)
  ret i32 %12
}

; Function Attrs: nobuiltin allocsize(0)
declare dso_local nonnull i8* @_Znwm(i64) #1

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #2

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1EC2Ev(%class.E* nonnull align 8 dereferenceable(24) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.E*, align 8
  store %class.E* %0, %class.E** %2, align 8
  %3 = load %class.E*, %class.E** %2, align 8
  %4 = bitcast %class.E* %3 to %class.C*
  call void @_ZN1CC2Ev(%class.C* nonnull align 8 dereferenceable(16) %4) #7
  %5 = bitcast %class.E* %3 to i8*
  %6 = getelementptr inbounds i8, i8* %5, i64 16
  %7 = bitcast i8* %6 to %class.D*
  call void @_ZN1DC2Ev(%class.D* nonnull align 8 dereferenceable(8) %7) #7
  %8 = bitcast %class.E* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [6 x i8*], [4 x i8*], [3 x i8*] }, { [6 x i8*], [4 x i8*], [3 x i8*] }* @_ZTV1E, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %8, align 8
  %9 = bitcast %class.E* %3 to i8*
  %10 = getelementptr inbounds i8, i8* %9, i64 8
  %11 = bitcast i8* %10 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [6 x i8*], [4 x i8*], [3 x i8*] }, { [6 x i8*], [4 x i8*], [3 x i8*] }* @_ZTV1E, i32 0, inrange i32 1, i32 2) to i32 (...)**), i32 (...)*** %11, align 8
  %12 = bitcast %class.E* %3 to i8*
  %13 = getelementptr inbounds i8, i8* %12, i64 16
  %14 = bitcast i8* %13 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [6 x i8*], [4 x i8*], [3 x i8*] }, { [6 x i8*], [4 x i8*], [3 x i8*] }* @_ZTV1E, i32 0, inrange i32 2, i32 2) to i32 (...)**), i32 (...)*** %14, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1CC2Ev(%class.C* nonnull align 8 dereferenceable(16) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.C*, align 8
  store %class.C* %0, %class.C** %2, align 8
  %3 = load %class.C*, %class.C** %2, align 8
  %4 = bitcast %class.C* %3 to %class.A*
  call void @_ZN1AC2Ev(%class.A* nonnull align 8 dereferenceable(8) %4) #7
  %5 = bitcast %class.C* %3 to i8*
  %6 = getelementptr inbounds i8, i8* %5, i64 8
  %7 = bitcast i8* %6 to %class.B*
  call void @_ZN1BC2Ev(%class.B* nonnull align 8 dereferenceable(8) %7) #7
  %8 = bitcast %class.C* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [5 x i8*], [4 x i8*] }, { [5 x i8*], [4 x i8*] }* @_ZTV1C, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %8, align 8
  %9 = bitcast %class.C* %3 to i8*
  %10 = getelementptr inbounds i8, i8* %9, i64 8
  %11 = bitcast i8* %10 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [5 x i8*], [4 x i8*] }, { [5 x i8*], [4 x i8*] }* @_ZTV1C, i32 0, inrange i32 1, i32 2) to i32 (...)**), i32 (...)*** %11, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1DC2Ev(%class.D* nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.D*, align 8
  store %class.D* %0, %class.D** %2, align 8
  %3 = load %class.D*, %class.D** %2, align 8
  %4 = bitcast %class.D* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [3 x i8*] }, { [3 x i8*] }* @_ZTV1D, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %4, align 8
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local i32 @_ZN1C1fEv(%class.C* nonnull align 8 dereferenceable(16) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.C*, align 8
  store %class.C* %0, %class.C** %2, align 8
  %3 = load %class.C*, %class.C** %2, align 8
  ret i32 4
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local i32 @_ZN1C1gEv(%class.C* nonnull align 8 dereferenceable(16) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.C*, align 8
  store %class.C* %0, %class.C** %2, align 8
  %3 = load %class.C*, %class.C** %2, align 8
  ret i32 5
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local i32 @_ZN1E1hEv(%class.E* nonnull align 8 dereferenceable(24) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.E*, align 8
  store %class.E* %0, %class.E** %2, align 8
  %3 = load %class.E*, %class.E** %2, align 8
  ret i32 0
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local i32 @_ZN1E1xEv(%class.E* nonnull align 8 dereferenceable(24) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.E*, align 8
  store %class.E* %0, %class.E** %2, align 8
  %3 = load %class.E*, %class.E** %2, align 8
  ret i32 7
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local i32 @_ZThn8_N1C1gEv(%class.C* %0) unnamed_addr #5 comdat align 2 {
  %2 = alloca %class.C*, align 8
  store %class.C* %0, %class.C** %2, align 8
  %3 = load %class.C*, %class.C** %2, align 8
  %4 = bitcast %class.C* %3 to i8*
  %5 = getelementptr inbounds i8, i8* %4, i64 -8
  %6 = bitcast i8* %5 to %class.C*
  %7 = tail call i32 @_ZN1C1gEv(%class.C* nonnull align 8 dereferenceable(16) %6)
  ret i32 %7
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local i32 @_ZThn8_N1E1hEv(%class.E* %0) unnamed_addr #5 comdat align 2 {
  %2 = alloca %class.E*, align 8
  store %class.E* %0, %class.E** %2, align 8
  %3 = load %class.E*, %class.E** %2, align 8
  %4 = bitcast %class.E* %3 to i8*
  %5 = getelementptr inbounds i8, i8* %4, i64 -8
  %6 = bitcast i8* %5 to %class.E*
  %7 = tail call i32 @_ZN1E1hEv(%class.E* nonnull align 8 dereferenceable(24) %6)
  ret i32 %7
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local i32 @_ZThn16_N1E1xEv(%class.E* %0) unnamed_addr #5 comdat align 2 {
  %2 = alloca %class.E*, align 8
  store %class.E* %0, %class.E** %2, align 8
  %3 = load %class.E*, %class.E** %2, align 8
  %4 = bitcast %class.E* %3 to i8*
  %5 = getelementptr inbounds i8, i8* %4, i64 -16
  %6 = bitcast i8* %5 to %class.E*
  %7 = tail call i32 @_ZN1E1xEv(%class.E* nonnull align 8 dereferenceable(24) %6)
  ret i32 %7
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1AC2Ev(%class.A* nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.A*, align 8
  store %class.A* %0, %class.A** %2, align 8
  %3 = load %class.A*, %class.A** %2, align 8
  %4 = bitcast %class.A* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [3 x i8*] }, { [3 x i8*] }* @_ZTV1A, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %4, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1BC2Ev(%class.B* nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.B*, align 8
  store %class.B* %0, %class.B** %2, align 8
  %3 = load %class.B*, %class.B** %2, align 8
  %4 = bitcast %class.B* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [4 x i8*] }, { [4 x i8*] }* @_ZTV1B, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %4, align 8
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local i32 @_ZN1C1hEv(%class.C* nonnull align 8 dereferenceable(16) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.C*, align 8
  store %class.C* %0, %class.C** %2, align 8
  %3 = load %class.C*, %class.C** %2, align 8
  ret i32 6
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local i32 @_ZThn8_N1C1hEv(%class.C* %0) unnamed_addr #5 comdat align 2 {
  %2 = alloca %class.C*, align 8
  store %class.C* %0, %class.C** %2, align 8
  %3 = load %class.C*, %class.C** %2, align 8
  %4 = bitcast %class.C* %3 to i8*
  %5 = getelementptr inbounds i8, i8* %4, i64 -8
  %6 = bitcast i8* %5 to %class.C*
  %7 = tail call i32 @_ZN1C1hEv(%class.C* nonnull align 8 dereferenceable(16) %6)
  ret i32 %7
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local i32 @_ZN1A1fEv(%class.A* nonnull align 8 dereferenceable(8) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.A*, align 8
  store %class.A* %0, %class.A** %2, align 8
  %3 = load %class.A*, %class.A** %2, align 8
  ret i32 1
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local i32 @_ZN1B1gEv(%class.B* nonnull align 8 dereferenceable(8) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.B*, align 8
  store %class.B* %0, %class.B** %2, align 8
  %3 = load %class.B*, %class.B** %2, align 8
  ret i32 2
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local i32 @_ZN1B1hEv(%class.B* nonnull align 8 dereferenceable(8) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.B*, align 8
  store %class.B* %0, %class.B** %2, align 8
  %3 = load %class.B*, %class.B** %2, align 8
  ret i32 3
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local i32 @_ZN1D1xEv(%class.D* nonnull align 8 dereferenceable(8) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.D*, align 8
  store %class.D* %0, %class.D** %2, align 8
  %3 = load %class.D*, %class.D** %2, align 8
  ret i32 0
}

attributes #0 = { mustprogress noinline norecurse optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nobuiltin allocsize(0) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { argmemonly nofree nounwind willreturn writeonly }
attributes #3 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { mustprogress noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { noinline optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { builtin allocsize(0) }
attributes #7 = { nounwind }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{!"clang version 13.0.1"}
