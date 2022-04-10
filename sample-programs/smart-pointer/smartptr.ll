; ModuleID = 'smartptr.bc'
source_filename = "smartptr.cpp"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx12.0.0"

%"class.std::__1::unique_ptr" = type { %"class.std::__1::__compressed_pair" }
%"class.std::__1::__compressed_pair" = type { %"struct.std::__1::__compressed_pair_elem" }
%"struct.std::__1::__compressed_pair_elem" = type { %class.Base* }
%class.Base = type { i32 (...)** }
%"class.std::__1::unique_ptr.1" = type { %"class.std::__1::__compressed_pair.2" }
%"class.std::__1::__compressed_pair.2" = type { %"struct.std::__1::__compressed_pair_elem.3" }
%"struct.std::__1::__compressed_pair_elem.3" = type { %class.DerivedA* }
%class.DerivedA = type { %class.Base }
%"struct.std::__1::default_delete" = type { i8 }
%"struct.std::__1::default_delete.5" = type { i8 }
%"struct.std::__1::__default_init_tag" = type { i8 }
%"struct.std::__1::__compressed_pair_elem.0" = type { i8 }
%"struct.std::__1::__compressed_pair_elem.4" = type { i8 }

@_ZTV8DerivedA = linkonce_odr unnamed_addr constant { [3 x i8*] } { [3 x i8*] [i8* null, i8* bitcast ({ i8*, i8*, i8* }* @_ZTI8DerivedA to i8*), i8* bitcast (i32 (%class.DerivedA*)* @_ZN8DerivedA6actionEv to i8*)] }, align 8
@_ZTVN10__cxxabiv120__si_class_type_infoE = external global i8*
@_ZTS8DerivedA = linkonce_odr hidden constant [10 x i8] c"8DerivedA\00", align 1
@_ZTVN10__cxxabiv117__class_type_infoE = external global i8*
@_ZTS4Base = linkonce_odr hidden constant [6 x i8] c"4Base\00", align 1
@_ZTI4Base = linkonce_odr hidden constant { i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv117__class_type_infoE, i64 2) to i8*), i8* inttoptr (i64 add (i64 ptrtoint ([6 x i8]* @_ZTS4Base to i64), i64 -9223372036854775808) to i8*) }, align 8
@_ZTI8DerivedA = linkonce_odr hidden constant { i8*, i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv120__si_class_type_infoE, i64 2) to i8*), i8* inttoptr (i64 add (i64 ptrtoint ([10 x i8]* @_ZTS8DerivedA to i64), i64 -9223372036854775808) to i8*), i8* bitcast ({ i8*, i8* }* @_ZTI4Base to i8*) }, align 8
@_ZTV4Base = linkonce_odr unnamed_addr constant { [3 x i8*] } { [3 x i8*] [i8* null, i8* bitcast ({ i8*, i8* }* @_ZTI4Base to i8*), i8* bitcast (i32 (%class.Base*)* @_ZN4Base6actionEv to i8*)] }, align 8

; Function Attrs: mustprogress noinline norecurse optnone ssp uwtable
define i32 @main() #0 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %1 = alloca i32, align 4
  %2 = alloca %"class.std::__1::unique_ptr", align 8
  %3 = alloca %"class.std::__1::unique_ptr.1", align 8
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %6 = call %"class.std::__1::unique_ptr"* @_ZNSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEEC1ILb1EvEEv(%"class.std::__1::unique_ptr"* nonnull align 8 dereferenceable(8) %2) #9
  invoke void @_ZNSt3__111make_uniqueI8DerivedAJEEENS_11__unique_ifIT_E15__unique_singleEDpOT0_(%"class.std::__1::unique_ptr.1"* sret(%"class.std::__1::unique_ptr.1") align 8 %3)
          to label %7 unwind label %19

7:                                                ; preds = %0
  %8 = call nonnull align 8 dereferenceable(8) %"class.std::__1::unique_ptr"* @_ZNSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEEaSI8DerivedANS2_IS6_EEvvEERS4_ONS0_IT_T0_EE(%"class.std::__1::unique_ptr"* nonnull align 8 dereferenceable(8) %2, %"class.std::__1::unique_ptr.1"* nonnull align 8 dereferenceable(8) %3) #9
  %9 = call %"class.std::__1::unique_ptr.1"* @_ZNSt3__110unique_ptrI8DerivedANS_14default_deleteIS1_EEED1Ev(%"class.std::__1::unique_ptr.1"* nonnull align 8 dereferenceable(8) %3) #9
  %10 = call %class.Base* @_ZNKSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEEptEv(%"class.std::__1::unique_ptr"* nonnull align 8 dereferenceable(8) %2) #9
  %11 = bitcast %class.Base* %10 to i32 (%class.Base*)***
  %12 = load i32 (%class.Base*)**, i32 (%class.Base*)*** %11, align 8
  %13 = getelementptr inbounds i32 (%class.Base*)*, i32 (%class.Base*)** %12, i64 0
  %14 = load i32 (%class.Base*)*, i32 (%class.Base*)** %13, align 8
  %15 = invoke i32 %14(%class.Base* nonnull align 8 dereferenceable(8) %10)
          to label %16 unwind label %19

16:                                               ; preds = %7
  store i32 0, i32* %1, align 4
  %17 = call %"class.std::__1::unique_ptr"* @_ZNSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEED1Ev(%"class.std::__1::unique_ptr"* nonnull align 8 dereferenceable(8) %2) #9
  %18 = load i32, i32* %1, align 4
  ret i32 %18

19:                                               ; preds = %7, %0
  %20 = landingpad { i8*, i32 }
          cleanup
  %21 = extractvalue { i8*, i32 } %20, 0
  store i8* %21, i8** %4, align 8
  %22 = extractvalue { i8*, i32 } %20, 1
  store i32 %22, i32* %5, align 4
  %23 = call %"class.std::__1::unique_ptr"* @_ZNSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEED1Ev(%"class.std::__1::unique_ptr"* nonnull align 8 dereferenceable(8) %2) #9
  br label %24

24:                                               ; preds = %19
  %25 = load i8*, i8** %4, align 8
  %26 = load i32, i32* %5, align 4
  %27 = insertvalue { i8*, i32 } undef, i8* %25, 0
  %28 = insertvalue { i8*, i32 } %27, i32 %26, 1
  resume { i8*, i32 } %28
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %"class.std::__1::unique_ptr"* @_ZNSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEEC1ILb1EvEEv(%"class.std::__1::unique_ptr"* nonnull returned align 8 dereferenceable(8) %0) unnamed_addr #1 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr"*, align 8
  store %"class.std::__1::unique_ptr"* %0, %"class.std::__1::unique_ptr"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr"*, %"class.std::__1::unique_ptr"** %2, align 8
  %4 = call %"class.std::__1::unique_ptr"* @_ZNSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEEC2ILb1EvEEv(%"class.std::__1::unique_ptr"* nonnull align 8 dereferenceable(8) %3) #9
  ret %"class.std::__1::unique_ptr"* %3
}

; Function Attrs: mustprogress noinline optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__111make_uniqueI8DerivedAJEEENS_11__unique_ifIT_E15__unique_singleEDpOT0_(%"class.std::__1::unique_ptr.1"* noalias sret(%"class.std::__1::unique_ptr.1") align 8 %0) #2 {
  %2 = alloca i8*, align 8
  %3 = bitcast %"class.std::__1::unique_ptr.1"* %0 to i8*
  store i8* %3, i8** %2, align 8
  %4 = call noalias nonnull i8* @_Znwm(i64 8) #10
  %5 = bitcast i8* %4 to %class.DerivedA*
  %6 = bitcast %class.DerivedA* %5 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %6, i8 0, i64 8, i1 false)
  %7 = call %class.DerivedA* @_ZN8DerivedAC1Ev(%class.DerivedA* nonnull align 8 dereferenceable(8) %5) #9
  %8 = call %"class.std::__1::unique_ptr.1"* @_ZNSt3__110unique_ptrI8DerivedANS_14default_deleteIS1_EEEC1ILb1EvEEPS1_(%"class.std::__1::unique_ptr.1"* nonnull align 8 dereferenceable(8) %0, %class.DerivedA* %5) #9
  ret void
}

declare i32 @__gxx_personality_v0(...)

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr nonnull align 8 dereferenceable(8) %"class.std::__1::unique_ptr"* @_ZNSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEEaSI8DerivedANS2_IS6_EEvvEERS4_ONS0_IT_T0_EE(%"class.std::__1::unique_ptr"* nonnull align 8 dereferenceable(8) %0, %"class.std::__1::unique_ptr.1"* nonnull align 8 dereferenceable(8) %1) #3 align 2 {
  %3 = alloca %"class.std::__1::unique_ptr"*, align 8
  %4 = alloca %"class.std::__1::unique_ptr.1"*, align 8
  %5 = alloca %"struct.std::__1::default_delete", align 1
  store %"class.std::__1::unique_ptr"* %0, %"class.std::__1::unique_ptr"** %3, align 8
  store %"class.std::__1::unique_ptr.1"* %1, %"class.std::__1::unique_ptr.1"** %4, align 8
  %6 = load %"class.std::__1::unique_ptr"*, %"class.std::__1::unique_ptr"** %3, align 8
  %7 = load %"class.std::__1::unique_ptr.1"*, %"class.std::__1::unique_ptr.1"** %4, align 8
  %8 = call %class.DerivedA* @_ZNSt3__110unique_ptrI8DerivedANS_14default_deleteIS1_EEE7releaseEv(%"class.std::__1::unique_ptr.1"* nonnull align 8 dereferenceable(8) %7) #9
  %9 = bitcast %class.DerivedA* %8 to %class.Base*
  call void @_ZNSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEE5resetEPS1_(%"class.std::__1::unique_ptr"* nonnull align 8 dereferenceable(8) %6, %class.Base* %9) #9
  %10 = load %"class.std::__1::unique_ptr.1"*, %"class.std::__1::unique_ptr.1"** %4, align 8
  %11 = call nonnull align 1 dereferenceable(1) %"struct.std::__1::default_delete.5"* @_ZNSt3__110unique_ptrI8DerivedANS_14default_deleteIS1_EEE11get_deleterEv(%"class.std::__1::unique_ptr.1"* nonnull align 8 dereferenceable(8) %10) #9
  %12 = call nonnull align 1 dereferenceable(1) %"struct.std::__1::default_delete.5"* @_ZNSt3__17forwardINS_14default_deleteI8DerivedAEEEEOT_RNS_16remove_referenceIS4_E4typeE(%"struct.std::__1::default_delete.5"* nonnull align 1 dereferenceable(1) %11) #9
  %13 = call %"struct.std::__1::default_delete"* @_ZNSt3__114default_deleteI4BaseEC1I8DerivedAEERKNS0_IT_EEPNS_9enable_ifIXsr14is_convertibleIPS5_PS1_EE5valueEvE4typeE(%"struct.std::__1::default_delete"* nonnull align 1 dereferenceable(1) %5, %"struct.std::__1::default_delete.5"* nonnull align 1 dereferenceable(1) %12, i8* null) #9
  %14 = getelementptr inbounds %"class.std::__1::unique_ptr", %"class.std::__1::unique_ptr"* %6, i32 0, i32 0
  %15 = call nonnull align 1 dereferenceable(1) %"struct.std::__1::default_delete"* @_ZNSt3__117__compressed_pairIP4BaseNS_14default_deleteIS1_EEE6secondEv(%"class.std::__1::__compressed_pair"* nonnull align 8 dereferenceable(8) %14) #9
  ret %"class.std::__1::unique_ptr"* %6
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"class.std::__1::unique_ptr.1"* @_ZNSt3__110unique_ptrI8DerivedANS_14default_deleteIS1_EEED1Ev(%"class.std::__1::unique_ptr.1"* nonnull returned align 8 dereferenceable(8) %0) unnamed_addr #1 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr.1"*, align 8
  store %"class.std::__1::unique_ptr.1"* %0, %"class.std::__1::unique_ptr.1"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr.1"*, %"class.std::__1::unique_ptr.1"** %2, align 8
  %4 = call %"class.std::__1::unique_ptr.1"* @_ZNSt3__110unique_ptrI8DerivedANS_14default_deleteIS1_EEED2Ev(%"class.std::__1::unique_ptr.1"* nonnull align 8 dereferenceable(8) %3) #9
  ret %"class.std::__1::unique_ptr.1"* %3
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %class.Base* @_ZNKSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEEptEv(%"class.std::__1::unique_ptr"* nonnull align 8 dereferenceable(8) %0) #3 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr"*, align 8
  store %"class.std::__1::unique_ptr"* %0, %"class.std::__1::unique_ptr"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr"*, %"class.std::__1::unique_ptr"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::unique_ptr", %"class.std::__1::unique_ptr"* %3, i32 0, i32 0
  %5 = call nonnull align 8 dereferenceable(8) %class.Base** @_ZNKSt3__117__compressed_pairIP4BaseNS_14default_deleteIS1_EEE5firstEv(%"class.std::__1::__compressed_pair"* nonnull align 8 dereferenceable(8) %4) #9
  %6 = load %class.Base*, %class.Base** %5, align 8
  ret %class.Base* %6
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"class.std::__1::unique_ptr"* @_ZNSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEED1Ev(%"class.std::__1::unique_ptr"* nonnull returned align 8 dereferenceable(8) %0) unnamed_addr #1 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr"*, align 8
  store %"class.std::__1::unique_ptr"* %0, %"class.std::__1::unique_ptr"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr"*, %"class.std::__1::unique_ptr"** %2, align 8
  %4 = call %"class.std::__1::unique_ptr"* @_ZNSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEED2Ev(%"class.std::__1::unique_ptr"* nonnull align 8 dereferenceable(8) %3) #9
  ret %"class.std::__1::unique_ptr"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %"class.std::__1::unique_ptr"* @_ZNSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEEC2ILb1EvEEv(%"class.std::__1::unique_ptr"* nonnull returned align 8 dereferenceable(8) %0) unnamed_addr #1 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %2 = alloca %"class.std::__1::unique_ptr"*, align 8
  %3 = alloca %class.Base*, align 8
  %4 = alloca %"struct.std::__1::__default_init_tag", align 1
  store %"class.std::__1::unique_ptr"* %0, %"class.std::__1::unique_ptr"** %2, align 8
  %5 = load %"class.std::__1::unique_ptr"*, %"class.std::__1::unique_ptr"** %2, align 8
  %6 = getelementptr inbounds %"class.std::__1::unique_ptr", %"class.std::__1::unique_ptr"* %5, i32 0, i32 0
  store %class.Base* null, %class.Base** %3, align 8
  %7 = invoke %"class.std::__1::__compressed_pair"* @_ZNSt3__117__compressed_pairIP4BaseNS_14default_deleteIS1_EEEC1IS2_NS_18__default_init_tagEEEOT_OT0_(%"class.std::__1::__compressed_pair"* nonnull align 8 dereferenceable(8) %6, %class.Base** nonnull align 8 dereferenceable(8) %3, %"struct.std::__1::__default_init_tag"* nonnull align 1 dereferenceable(1) %4)
          to label %8 unwind label %9

8:                                                ; preds = %1
  ret %"class.std::__1::unique_ptr"* %5

9:                                                ; preds = %1
  %10 = landingpad { i8*, i32 }
          catch i8* null
  %11 = extractvalue { i8*, i32 } %10, 0
  call void @__clang_call_terminate(i8* %11) #11
  unreachable
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr %"class.std::__1::__compressed_pair"* @_ZNSt3__117__compressed_pairIP4BaseNS_14default_deleteIS1_EEEC1IS2_NS_18__default_init_tagEEEOT_OT0_(%"class.std::__1::__compressed_pair"* nonnull returned align 8 dereferenceable(8) %0, %class.Base** nonnull align 8 dereferenceable(8) %1, %"struct.std::__1::__default_init_tag"* nonnull align 1 dereferenceable(1) %2) unnamed_addr #4 align 2 {
  %4 = alloca %"class.std::__1::__compressed_pair"*, align 8
  %5 = alloca %class.Base**, align 8
  %6 = alloca %"struct.std::__1::__default_init_tag"*, align 8
  store %"class.std::__1::__compressed_pair"* %0, %"class.std::__1::__compressed_pair"** %4, align 8
  store %class.Base** %1, %class.Base*** %5, align 8
  store %"struct.std::__1::__default_init_tag"* %2, %"struct.std::__1::__default_init_tag"** %6, align 8
  %7 = load %"class.std::__1::__compressed_pair"*, %"class.std::__1::__compressed_pair"** %4, align 8
  %8 = load %class.Base**, %class.Base*** %5, align 8
  %9 = load %"struct.std::__1::__default_init_tag"*, %"struct.std::__1::__default_init_tag"** %6, align 8
  %10 = call %"class.std::__1::__compressed_pair"* @_ZNSt3__117__compressed_pairIP4BaseNS_14default_deleteIS1_EEEC2IS2_NS_18__default_init_tagEEEOT_OT0_(%"class.std::__1::__compressed_pair"* nonnull align 8 dereferenceable(8) %7, %class.Base** nonnull align 8 dereferenceable(8) %8, %"struct.std::__1::__default_init_tag"* nonnull align 1 dereferenceable(1) %9)
  ret %"class.std::__1::__compressed_pair"* %7
}

; Function Attrs: noinline noreturn nounwind
define linkonce_odr hidden void @__clang_call_terminate(i8* %0) #5 {
  %2 = call i8* @__cxa_begin_catch(i8* %0) #9
  call void @_ZSt9terminatev() #11
  unreachable
}

declare i8* @__cxa_begin_catch(i8*)

declare void @_ZSt9terminatev()

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr %"class.std::__1::__compressed_pair"* @_ZNSt3__117__compressed_pairIP4BaseNS_14default_deleteIS1_EEEC2IS2_NS_18__default_init_tagEEEOT_OT0_(%"class.std::__1::__compressed_pair"* nonnull returned align 8 dereferenceable(8) %0, %class.Base** nonnull align 8 dereferenceable(8) %1, %"struct.std::__1::__default_init_tag"* nonnull align 1 dereferenceable(1) %2) unnamed_addr #4 align 2 {
  %4 = alloca %"class.std::__1::__compressed_pair"*, align 8
  %5 = alloca %class.Base**, align 8
  %6 = alloca %"struct.std::__1::__default_init_tag"*, align 8
  %7 = alloca %"struct.std::__1::__default_init_tag", align 1
  store %"class.std::__1::__compressed_pair"* %0, %"class.std::__1::__compressed_pair"** %4, align 8
  store %class.Base** %1, %class.Base*** %5, align 8
  store %"struct.std::__1::__default_init_tag"* %2, %"struct.std::__1::__default_init_tag"** %6, align 8
  %8 = load %"class.std::__1::__compressed_pair"*, %"class.std::__1::__compressed_pair"** %4, align 8
  %9 = bitcast %"class.std::__1::__compressed_pair"* %8 to %"struct.std::__1::__compressed_pair_elem"*
  %10 = load %class.Base**, %class.Base*** %5, align 8
  %11 = call nonnull align 8 dereferenceable(8) %class.Base** @_ZNSt3__17forwardIP4BaseEEOT_RNS_16remove_referenceIS3_E4typeE(%class.Base** nonnull align 8 dereferenceable(8) %10) #9
  %12 = call %"struct.std::__1::__compressed_pair_elem"* @_ZNSt3__122__compressed_pair_elemIP4BaseLi0ELb0EEC2IS2_vEEOT_(%"struct.std::__1::__compressed_pair_elem"* nonnull align 8 dereferenceable(8) %9, %class.Base** nonnull align 8 dereferenceable(8) %11)
  %13 = bitcast %"class.std::__1::__compressed_pair"* %8 to %"struct.std::__1::__compressed_pair_elem.0"*
  %14 = load %"struct.std::__1::__default_init_tag"*, %"struct.std::__1::__default_init_tag"** %6, align 8
  %15 = call nonnull align 1 dereferenceable(1) %"struct.std::__1::__default_init_tag"* @_ZNSt3__17forwardINS_18__default_init_tagEEEOT_RNS_16remove_referenceIS2_E4typeE(%"struct.std::__1::__default_init_tag"* nonnull align 1 dereferenceable(1) %14) #9
  %16 = call %"struct.std::__1::__compressed_pair_elem.0"* @_ZNSt3__122__compressed_pair_elemINS_14default_deleteI4BaseEELi1ELb1EEC2ENS_18__default_init_tagE(%"struct.std::__1::__compressed_pair_elem.0"* nonnull align 1 dereferenceable(1) %13)
  ret %"class.std::__1::__compressed_pair"* %8
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 8 dereferenceable(8) %class.Base** @_ZNSt3__17forwardIP4BaseEEOT_RNS_16remove_referenceIS3_E4typeE(%class.Base** nonnull align 8 dereferenceable(8) %0) #3 {
  %2 = alloca %class.Base**, align 8
  store %class.Base** %0, %class.Base*** %2, align 8
  %3 = load %class.Base**, %class.Base*** %2, align 8
  ret %class.Base** %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %"struct.std::__1::__compressed_pair_elem"* @_ZNSt3__122__compressed_pair_elemIP4BaseLi0ELb0EEC2IS2_vEEOT_(%"struct.std::__1::__compressed_pair_elem"* nonnull returned align 8 dereferenceable(8) %0, %class.Base** nonnull align 8 dereferenceable(8) %1) unnamed_addr #1 align 2 {
  %3 = alloca %"struct.std::__1::__compressed_pair_elem"*, align 8
  %4 = alloca %class.Base**, align 8
  store %"struct.std::__1::__compressed_pair_elem"* %0, %"struct.std::__1::__compressed_pair_elem"** %3, align 8
  store %class.Base** %1, %class.Base*** %4, align 8
  %5 = load %"struct.std::__1::__compressed_pair_elem"*, %"struct.std::__1::__compressed_pair_elem"** %3, align 8
  %6 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem", %"struct.std::__1::__compressed_pair_elem"* %5, i32 0, i32 0
  %7 = load %class.Base**, %class.Base*** %4, align 8
  %8 = call nonnull align 8 dereferenceable(8) %class.Base** @_ZNSt3__17forwardIP4BaseEEOT_RNS_16remove_referenceIS3_E4typeE(%class.Base** nonnull align 8 dereferenceable(8) %7) #9
  %9 = load %class.Base*, %class.Base** %8, align 8
  store %class.Base* %9, %class.Base** %6, align 8
  ret %"struct.std::__1::__compressed_pair_elem"* %5
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 1 dereferenceable(1) %"struct.std::__1::__default_init_tag"* @_ZNSt3__17forwardINS_18__default_init_tagEEEOT_RNS_16remove_referenceIS2_E4typeE(%"struct.std::__1::__default_init_tag"* nonnull align 1 dereferenceable(1) %0) #3 {
  %2 = alloca %"struct.std::__1::__default_init_tag"*, align 8
  store %"struct.std::__1::__default_init_tag"* %0, %"struct.std::__1::__default_init_tag"** %2, align 8
  %3 = load %"struct.std::__1::__default_init_tag"*, %"struct.std::__1::__default_init_tag"** %2, align 8
  ret %"struct.std::__1::__default_init_tag"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::__compressed_pair_elem.0"* @_ZNSt3__122__compressed_pair_elemINS_14default_deleteI4BaseEELi1ELb1EEC2ENS_18__default_init_tagE(%"struct.std::__1::__compressed_pair_elem.0"* nonnull returned align 1 dereferenceable(1) %0) unnamed_addr #1 align 2 {
  %2 = alloca %"struct.std::__1::__default_init_tag", align 1
  %3 = alloca %"struct.std::__1::__compressed_pair_elem.0"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.0"* %0, %"struct.std::__1::__compressed_pair_elem.0"** %3, align 8
  %4 = load %"struct.std::__1::__compressed_pair_elem.0"*, %"struct.std::__1::__compressed_pair_elem.0"** %3, align 8
  %5 = bitcast %"struct.std::__1::__compressed_pair_elem.0"* %4 to %"struct.std::__1::default_delete"*
  ret %"struct.std::__1::__compressed_pair_elem.0"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"class.std::__1::unique_ptr"* @_ZNSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEED2Ev(%"class.std::__1::unique_ptr"* nonnull returned align 8 dereferenceable(8) %0) unnamed_addr #1 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr"*, align 8
  store %"class.std::__1::unique_ptr"* %0, %"class.std::__1::unique_ptr"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr"*, %"class.std::__1::unique_ptr"** %2, align 8
  call void @_ZNSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEE5resetEPS1_(%"class.std::__1::unique_ptr"* nonnull align 8 dereferenceable(8) %3, %class.Base* null) #9
  ret %"class.std::__1::unique_ptr"* %3
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__110unique_ptrI4BaseNS_14default_deleteIS1_EEE5resetEPS1_(%"class.std::__1::unique_ptr"* nonnull align 8 dereferenceable(8) %0, %class.Base* %1) #3 align 2 {
  %3 = alloca %"class.std::__1::unique_ptr"*, align 8
  %4 = alloca %class.Base*, align 8
  %5 = alloca %class.Base*, align 8
  store %"class.std::__1::unique_ptr"* %0, %"class.std::__1::unique_ptr"** %3, align 8
  store %class.Base* %1, %class.Base** %4, align 8
  %6 = load %"class.std::__1::unique_ptr"*, %"class.std::__1::unique_ptr"** %3, align 8
  %7 = getelementptr inbounds %"class.std::__1::unique_ptr", %"class.std::__1::unique_ptr"* %6, i32 0, i32 0
  %8 = call nonnull align 8 dereferenceable(8) %class.Base** @_ZNSt3__117__compressed_pairIP4BaseNS_14default_deleteIS1_EEE5firstEv(%"class.std::__1::__compressed_pair"* nonnull align 8 dereferenceable(8) %7) #9
  %9 = load %class.Base*, %class.Base** %8, align 8
  store %class.Base* %9, %class.Base** %5, align 8
  %10 = load %class.Base*, %class.Base** %4, align 8
  %11 = getelementptr inbounds %"class.std::__1::unique_ptr", %"class.std::__1::unique_ptr"* %6, i32 0, i32 0
  %12 = call nonnull align 8 dereferenceable(8) %class.Base** @_ZNSt3__117__compressed_pairIP4BaseNS_14default_deleteIS1_EEE5firstEv(%"class.std::__1::__compressed_pair"* nonnull align 8 dereferenceable(8) %11) #9
  store %class.Base* %10, %class.Base** %12, align 8
  %13 = load %class.Base*, %class.Base** %5, align 8
  %14 = icmp ne %class.Base* %13, null
  br i1 %14, label %15, label %19

15:                                               ; preds = %2
  %16 = getelementptr inbounds %"class.std::__1::unique_ptr", %"class.std::__1::unique_ptr"* %6, i32 0, i32 0
  %17 = call nonnull align 1 dereferenceable(1) %"struct.std::__1::default_delete"* @_ZNSt3__117__compressed_pairIP4BaseNS_14default_deleteIS1_EEE6secondEv(%"class.std::__1::__compressed_pair"* nonnull align 8 dereferenceable(8) %16) #9
  %18 = load %class.Base*, %class.Base** %5, align 8
  call void @_ZNKSt3__114default_deleteI4BaseEclEPS1_(%"struct.std::__1::default_delete"* nonnull align 1 dereferenceable(1) %17, %class.Base* %18) #9
  br label %19

19:                                               ; preds = %15, %2
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 8 dereferenceable(8) %class.Base** @_ZNSt3__117__compressed_pairIP4BaseNS_14default_deleteIS1_EEE5firstEv(%"class.std::__1::__compressed_pair"* nonnull align 8 dereferenceable(8) %0) #3 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair"*, align 8
  store %"class.std::__1::__compressed_pair"* %0, %"class.std::__1::__compressed_pair"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair"*, %"class.std::__1::__compressed_pair"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair"* %3 to %"struct.std::__1::__compressed_pair_elem"*
  %5 = call nonnull align 8 dereferenceable(8) %class.Base** @_ZNSt3__122__compressed_pair_elemIP4BaseLi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem"* nonnull align 8 dereferenceable(8) %4) #9
  ret %class.Base** %5
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 1 dereferenceable(1) %"struct.std::__1::default_delete"* @_ZNSt3__117__compressed_pairIP4BaseNS_14default_deleteIS1_EEE6secondEv(%"class.std::__1::__compressed_pair"* nonnull align 8 dereferenceable(8) %0) #3 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair"*, align 8
  store %"class.std::__1::__compressed_pair"* %0, %"class.std::__1::__compressed_pair"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair"*, %"class.std::__1::__compressed_pair"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair"* %3 to %"struct.std::__1::__compressed_pair_elem.0"*
  %5 = call nonnull align 1 dereferenceable(1) %"struct.std::__1::default_delete"* @_ZNSt3__122__compressed_pair_elemINS_14default_deleteI4BaseEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.0"* nonnull align 1 dereferenceable(1) %4) #9
  ret %"struct.std::__1::default_delete"* %5
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNKSt3__114default_deleteI4BaseEclEPS1_(%"struct.std::__1::default_delete"* nonnull align 1 dereferenceable(1) %0, %class.Base* %1) #3 align 2 {
  %3 = alloca %"struct.std::__1::default_delete"*, align 8
  %4 = alloca %class.Base*, align 8
  store %"struct.std::__1::default_delete"* %0, %"struct.std::__1::default_delete"** %3, align 8
  store %class.Base* %1, %class.Base** %4, align 8
  %5 = load %"struct.std::__1::default_delete"*, %"struct.std::__1::default_delete"** %3, align 8
  %6 = load %class.Base*, %class.Base** %4, align 8
  %7 = icmp eq %class.Base* %6, null
  br i1 %7, label %10, label %8

8:                                                ; preds = %2
  %9 = bitcast %class.Base* %6 to i8*
  call void @_ZdlPv(i8* %9) #12
  br label %10

10:                                               ; preds = %8, %2
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 8 dereferenceable(8) %class.Base** @_ZNSt3__122__compressed_pair_elemIP4BaseLi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem"* nonnull align 8 dereferenceable(8) %0) #3 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem"*, align 8
  store %"struct.std::__1::__compressed_pair_elem"* %0, %"struct.std::__1::__compressed_pair_elem"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem"*, %"struct.std::__1::__compressed_pair_elem"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem", %"struct.std::__1::__compressed_pair_elem"* %3, i32 0, i32 0
  ret %class.Base** %4
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 1 dereferenceable(1) %"struct.std::__1::default_delete"* @_ZNSt3__122__compressed_pair_elemINS_14default_deleteI4BaseEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.0"* nonnull align 1 dereferenceable(1) %0) #3 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.0"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.0"* %0, %"struct.std::__1::__compressed_pair_elem.0"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.0"*, %"struct.std::__1::__compressed_pair_elem.0"** %2, align 8
  %4 = bitcast %"struct.std::__1::__compressed_pair_elem.0"* %3 to %"struct.std::__1::default_delete"*
  ret %"struct.std::__1::default_delete"* %4
}

; Function Attrs: nobuiltin nounwind
declare void @_ZdlPv(i8*) #6

; Function Attrs: nobuiltin allocsize(0)
declare nonnull i8* @_Znwm(i64) #7

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #8

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %class.DerivedA* @_ZN8DerivedAC1Ev(%class.DerivedA* nonnull returned align 8 dereferenceable(8) %0) unnamed_addr #1 align 2 {
  %2 = alloca %class.DerivedA*, align 8
  store %class.DerivedA* %0, %class.DerivedA** %2, align 8
  %3 = load %class.DerivedA*, %class.DerivedA** %2, align 8
  %4 = call %class.DerivedA* @_ZN8DerivedAC2Ev(%class.DerivedA* nonnull align 8 dereferenceable(8) %3) #9
  ret %class.DerivedA* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %"class.std::__1::unique_ptr.1"* @_ZNSt3__110unique_ptrI8DerivedANS_14default_deleteIS1_EEEC1ILb1EvEEPS1_(%"class.std::__1::unique_ptr.1"* nonnull returned align 8 dereferenceable(8) %0, %class.DerivedA* %1) unnamed_addr #1 align 2 {
  %3 = alloca %"class.std::__1::unique_ptr.1"*, align 8
  %4 = alloca %class.DerivedA*, align 8
  store %"class.std::__1::unique_ptr.1"* %0, %"class.std::__1::unique_ptr.1"** %3, align 8
  store %class.DerivedA* %1, %class.DerivedA** %4, align 8
  %5 = load %"class.std::__1::unique_ptr.1"*, %"class.std::__1::unique_ptr.1"** %3, align 8
  %6 = load %class.DerivedA*, %class.DerivedA** %4, align 8
  %7 = call %"class.std::__1::unique_ptr.1"* @_ZNSt3__110unique_ptrI8DerivedANS_14default_deleteIS1_EEEC2ILb1EvEEPS1_(%"class.std::__1::unique_ptr.1"* nonnull align 8 dereferenceable(8) %5, %class.DerivedA* %6) #9
  ret %"class.std::__1::unique_ptr.1"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %class.DerivedA* @_ZN8DerivedAC2Ev(%class.DerivedA* nonnull returned align 8 dereferenceable(8) %0) unnamed_addr #1 align 2 {
  %2 = alloca %class.DerivedA*, align 8
  store %class.DerivedA* %0, %class.DerivedA** %2, align 8
  %3 = load %class.DerivedA*, %class.DerivedA** %2, align 8
  %4 = bitcast %class.DerivedA* %3 to %class.Base*
  %5 = call %class.Base* @_ZN4BaseC2Ev(%class.Base* nonnull align 8 dereferenceable(8) %4) #9
  %6 = bitcast %class.DerivedA* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [3 x i8*] }, { [3 x i8*] }* @_ZTV8DerivedA, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %6, align 8
  ret %class.DerivedA* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %class.Base* @_ZN4BaseC2Ev(%class.Base* nonnull returned align 8 dereferenceable(8) %0) unnamed_addr #1 align 2 {
  %2 = alloca %class.Base*, align 8
  store %class.Base* %0, %class.Base** %2, align 8
  %3 = load %class.Base*, %class.Base** %2, align 8
  %4 = bitcast %class.Base* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [3 x i8*] }, { [3 x i8*] }* @_ZTV4Base, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %4, align 8
  ret %class.Base* %3
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr i32 @_ZN8DerivedA6actionEv(%class.DerivedA* nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 align 2 {
  %2 = alloca %class.DerivedA*, align 8
  store %class.DerivedA* %0, %class.DerivedA** %2, align 8
  %3 = load %class.DerivedA*, %class.DerivedA** %2, align 8
  ret i32 2
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr i32 @_ZN4Base6actionEv(%class.Base* nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 align 2 {
  %2 = alloca %class.Base*, align 8
  store %class.Base* %0, %class.Base** %2, align 8
  %3 = load %class.Base*, %class.Base** %2, align 8
  ret i32 1
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %"class.std::__1::unique_ptr.1"* @_ZNSt3__110unique_ptrI8DerivedANS_14default_deleteIS1_EEEC2ILb1EvEEPS1_(%"class.std::__1::unique_ptr.1"* nonnull returned align 8 dereferenceable(8) %0, %class.DerivedA* %1) unnamed_addr #1 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = alloca %"class.std::__1::unique_ptr.1"*, align 8
  %4 = alloca %class.DerivedA*, align 8
  %5 = alloca %"struct.std::__1::__default_init_tag", align 1
  store %"class.std::__1::unique_ptr.1"* %0, %"class.std::__1::unique_ptr.1"** %3, align 8
  store %class.DerivedA* %1, %class.DerivedA** %4, align 8
  %6 = load %"class.std::__1::unique_ptr.1"*, %"class.std::__1::unique_ptr.1"** %3, align 8
  %7 = getelementptr inbounds %"class.std::__1::unique_ptr.1", %"class.std::__1::unique_ptr.1"* %6, i32 0, i32 0
  %8 = invoke %"class.std::__1::__compressed_pair.2"* @_ZNSt3__117__compressed_pairIP8DerivedANS_14default_deleteIS1_EEEC1IRS2_NS_18__default_init_tagEEEOT_OT0_(%"class.std::__1::__compressed_pair.2"* nonnull align 8 dereferenceable(8) %7, %class.DerivedA** nonnull align 8 dereferenceable(8) %4, %"struct.std::__1::__default_init_tag"* nonnull align 1 dereferenceable(1) %5)
          to label %9 unwind label %10

9:                                                ; preds = %2
  ret %"class.std::__1::unique_ptr.1"* %6

10:                                               ; preds = %2
  %11 = landingpad { i8*, i32 }
          catch i8* null
  %12 = extractvalue { i8*, i32 } %11, 0
  call void @__clang_call_terminate(i8* %12) #11
  unreachable
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr %"class.std::__1::__compressed_pair.2"* @_ZNSt3__117__compressed_pairIP8DerivedANS_14default_deleteIS1_EEEC1IRS2_NS_18__default_init_tagEEEOT_OT0_(%"class.std::__1::__compressed_pair.2"* nonnull returned align 8 dereferenceable(8) %0, %class.DerivedA** nonnull align 8 dereferenceable(8) %1, %"struct.std::__1::__default_init_tag"* nonnull align 1 dereferenceable(1) %2) unnamed_addr #4 align 2 {
  %4 = alloca %"class.std::__1::__compressed_pair.2"*, align 8
  %5 = alloca %class.DerivedA**, align 8
  %6 = alloca %"struct.std::__1::__default_init_tag"*, align 8
  store %"class.std::__1::__compressed_pair.2"* %0, %"class.std::__1::__compressed_pair.2"** %4, align 8
  store %class.DerivedA** %1, %class.DerivedA*** %5, align 8
  store %"struct.std::__1::__default_init_tag"* %2, %"struct.std::__1::__default_init_tag"** %6, align 8
  %7 = load %"class.std::__1::__compressed_pair.2"*, %"class.std::__1::__compressed_pair.2"** %4, align 8
  %8 = load %class.DerivedA**, %class.DerivedA*** %5, align 8
  %9 = load %"struct.std::__1::__default_init_tag"*, %"struct.std::__1::__default_init_tag"** %6, align 8
  %10 = call %"class.std::__1::__compressed_pair.2"* @_ZNSt3__117__compressed_pairIP8DerivedANS_14default_deleteIS1_EEEC2IRS2_NS_18__default_init_tagEEEOT_OT0_(%"class.std::__1::__compressed_pair.2"* nonnull align 8 dereferenceable(8) %7, %class.DerivedA** nonnull align 8 dereferenceable(8) %8, %"struct.std::__1::__default_init_tag"* nonnull align 1 dereferenceable(1) %9)
  ret %"class.std::__1::__compressed_pair.2"* %7
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr %"class.std::__1::__compressed_pair.2"* @_ZNSt3__117__compressed_pairIP8DerivedANS_14default_deleteIS1_EEEC2IRS2_NS_18__default_init_tagEEEOT_OT0_(%"class.std::__1::__compressed_pair.2"* nonnull returned align 8 dereferenceable(8) %0, %class.DerivedA** nonnull align 8 dereferenceable(8) %1, %"struct.std::__1::__default_init_tag"* nonnull align 1 dereferenceable(1) %2) unnamed_addr #4 align 2 {
  %4 = alloca %"class.std::__1::__compressed_pair.2"*, align 8
  %5 = alloca %class.DerivedA**, align 8
  %6 = alloca %"struct.std::__1::__default_init_tag"*, align 8
  %7 = alloca %"struct.std::__1::__default_init_tag", align 1
  store %"class.std::__1::__compressed_pair.2"* %0, %"class.std::__1::__compressed_pair.2"** %4, align 8
  store %class.DerivedA** %1, %class.DerivedA*** %5, align 8
  store %"struct.std::__1::__default_init_tag"* %2, %"struct.std::__1::__default_init_tag"** %6, align 8
  %8 = load %"class.std::__1::__compressed_pair.2"*, %"class.std::__1::__compressed_pair.2"** %4, align 8
  %9 = bitcast %"class.std::__1::__compressed_pair.2"* %8 to %"struct.std::__1::__compressed_pair_elem.3"*
  %10 = load %class.DerivedA**, %class.DerivedA*** %5, align 8
  %11 = call nonnull align 8 dereferenceable(8) %class.DerivedA** @_ZNSt3__17forwardIRP8DerivedAEEOT_RNS_16remove_referenceIS4_E4typeE(%class.DerivedA** nonnull align 8 dereferenceable(8) %10) #9
  %12 = call %"struct.std::__1::__compressed_pair_elem.3"* @_ZNSt3__122__compressed_pair_elemIP8DerivedALi0ELb0EEC2IRS2_vEEOT_(%"struct.std::__1::__compressed_pair_elem.3"* nonnull align 8 dereferenceable(8) %9, %class.DerivedA** nonnull align 8 dereferenceable(8) %11)
  %13 = bitcast %"class.std::__1::__compressed_pair.2"* %8 to %"struct.std::__1::__compressed_pair_elem.4"*
  %14 = load %"struct.std::__1::__default_init_tag"*, %"struct.std::__1::__default_init_tag"** %6, align 8
  %15 = call nonnull align 1 dereferenceable(1) %"struct.std::__1::__default_init_tag"* @_ZNSt3__17forwardINS_18__default_init_tagEEEOT_RNS_16remove_referenceIS2_E4typeE(%"struct.std::__1::__default_init_tag"* nonnull align 1 dereferenceable(1) %14) #9
  %16 = call %"struct.std::__1::__compressed_pair_elem.4"* @_ZNSt3__122__compressed_pair_elemINS_14default_deleteI8DerivedAEELi1ELb1EEC2ENS_18__default_init_tagE(%"struct.std::__1::__compressed_pair_elem.4"* nonnull align 1 dereferenceable(1) %13)
  ret %"class.std::__1::__compressed_pair.2"* %8
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 8 dereferenceable(8) %class.DerivedA** @_ZNSt3__17forwardIRP8DerivedAEEOT_RNS_16remove_referenceIS4_E4typeE(%class.DerivedA** nonnull align 8 dereferenceable(8) %0) #3 {
  %2 = alloca %class.DerivedA**, align 8
  store %class.DerivedA** %0, %class.DerivedA*** %2, align 8
  %3 = load %class.DerivedA**, %class.DerivedA*** %2, align 8
  ret %class.DerivedA** %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %"struct.std::__1::__compressed_pair_elem.3"* @_ZNSt3__122__compressed_pair_elemIP8DerivedALi0ELb0EEC2IRS2_vEEOT_(%"struct.std::__1::__compressed_pair_elem.3"* nonnull returned align 8 dereferenceable(8) %0, %class.DerivedA** nonnull align 8 dereferenceable(8) %1) unnamed_addr #1 align 2 {
  %3 = alloca %"struct.std::__1::__compressed_pair_elem.3"*, align 8
  %4 = alloca %class.DerivedA**, align 8
  store %"struct.std::__1::__compressed_pair_elem.3"* %0, %"struct.std::__1::__compressed_pair_elem.3"** %3, align 8
  store %class.DerivedA** %1, %class.DerivedA*** %4, align 8
  %5 = load %"struct.std::__1::__compressed_pair_elem.3"*, %"struct.std::__1::__compressed_pair_elem.3"** %3, align 8
  %6 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.3", %"struct.std::__1::__compressed_pair_elem.3"* %5, i32 0, i32 0
  %7 = load %class.DerivedA**, %class.DerivedA*** %4, align 8
  %8 = call nonnull align 8 dereferenceable(8) %class.DerivedA** @_ZNSt3__17forwardIRP8DerivedAEEOT_RNS_16remove_referenceIS4_E4typeE(%class.DerivedA** nonnull align 8 dereferenceable(8) %7) #9
  %9 = load %class.DerivedA*, %class.DerivedA** %8, align 8
  store %class.DerivedA* %9, %class.DerivedA** %6, align 8
  ret %"struct.std::__1::__compressed_pair_elem.3"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::__compressed_pair_elem.4"* @_ZNSt3__122__compressed_pair_elemINS_14default_deleteI8DerivedAEELi1ELb1EEC2ENS_18__default_init_tagE(%"struct.std::__1::__compressed_pair_elem.4"* nonnull returned align 1 dereferenceable(1) %0) unnamed_addr #1 align 2 {
  %2 = alloca %"struct.std::__1::__default_init_tag", align 1
  %3 = alloca %"struct.std::__1::__compressed_pair_elem.4"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.4"* %0, %"struct.std::__1::__compressed_pair_elem.4"** %3, align 8
  %4 = load %"struct.std::__1::__compressed_pair_elem.4"*, %"struct.std::__1::__compressed_pair_elem.4"** %3, align 8
  %5 = bitcast %"struct.std::__1::__compressed_pair_elem.4"* %4 to %"struct.std::__1::default_delete.5"*
  ret %"struct.std::__1::__compressed_pair_elem.4"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"class.std::__1::unique_ptr.1"* @_ZNSt3__110unique_ptrI8DerivedANS_14default_deleteIS1_EEED2Ev(%"class.std::__1::unique_ptr.1"* nonnull returned align 8 dereferenceable(8) %0) unnamed_addr #1 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr.1"*, align 8
  store %"class.std::__1::unique_ptr.1"* %0, %"class.std::__1::unique_ptr.1"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr.1"*, %"class.std::__1::unique_ptr.1"** %2, align 8
  call void @_ZNSt3__110unique_ptrI8DerivedANS_14default_deleteIS1_EEE5resetEPS1_(%"class.std::__1::unique_ptr.1"* nonnull align 8 dereferenceable(8) %3, %class.DerivedA* null) #9
  ret %"class.std::__1::unique_ptr.1"* %3
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__110unique_ptrI8DerivedANS_14default_deleteIS1_EEE5resetEPS1_(%"class.std::__1::unique_ptr.1"* nonnull align 8 dereferenceable(8) %0, %class.DerivedA* %1) #3 align 2 {
  %3 = alloca %"class.std::__1::unique_ptr.1"*, align 8
  %4 = alloca %class.DerivedA*, align 8
  %5 = alloca %class.DerivedA*, align 8
  store %"class.std::__1::unique_ptr.1"* %0, %"class.std::__1::unique_ptr.1"** %3, align 8
  store %class.DerivedA* %1, %class.DerivedA** %4, align 8
  %6 = load %"class.std::__1::unique_ptr.1"*, %"class.std::__1::unique_ptr.1"** %3, align 8
  %7 = getelementptr inbounds %"class.std::__1::unique_ptr.1", %"class.std::__1::unique_ptr.1"* %6, i32 0, i32 0
  %8 = call nonnull align 8 dereferenceable(8) %class.DerivedA** @_ZNSt3__117__compressed_pairIP8DerivedANS_14default_deleteIS1_EEE5firstEv(%"class.std::__1::__compressed_pair.2"* nonnull align 8 dereferenceable(8) %7) #9
  %9 = load %class.DerivedA*, %class.DerivedA** %8, align 8
  store %class.DerivedA* %9, %class.DerivedA** %5, align 8
  %10 = load %class.DerivedA*, %class.DerivedA** %4, align 8
  %11 = getelementptr inbounds %"class.std::__1::unique_ptr.1", %"class.std::__1::unique_ptr.1"* %6, i32 0, i32 0
  %12 = call nonnull align 8 dereferenceable(8) %class.DerivedA** @_ZNSt3__117__compressed_pairIP8DerivedANS_14default_deleteIS1_EEE5firstEv(%"class.std::__1::__compressed_pair.2"* nonnull align 8 dereferenceable(8) %11) #9
  store %class.DerivedA* %10, %class.DerivedA** %12, align 8
  %13 = load %class.DerivedA*, %class.DerivedA** %5, align 8
  %14 = icmp ne %class.DerivedA* %13, null
  br i1 %14, label %15, label %19

15:                                               ; preds = %2
  %16 = getelementptr inbounds %"class.std::__1::unique_ptr.1", %"class.std::__1::unique_ptr.1"* %6, i32 0, i32 0
  %17 = call nonnull align 1 dereferenceable(1) %"struct.std::__1::default_delete.5"* @_ZNSt3__117__compressed_pairIP8DerivedANS_14default_deleteIS1_EEE6secondEv(%"class.std::__1::__compressed_pair.2"* nonnull align 8 dereferenceable(8) %16) #9
  %18 = load %class.DerivedA*, %class.DerivedA** %5, align 8
  call void @_ZNKSt3__114default_deleteI8DerivedAEclEPS1_(%"struct.std::__1::default_delete.5"* nonnull align 1 dereferenceable(1) %17, %class.DerivedA* %18) #9
  br label %19

19:                                               ; preds = %15, %2
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 8 dereferenceable(8) %class.DerivedA** @_ZNSt3__117__compressed_pairIP8DerivedANS_14default_deleteIS1_EEE5firstEv(%"class.std::__1::__compressed_pair.2"* nonnull align 8 dereferenceable(8) %0) #3 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.2"*, align 8
  store %"class.std::__1::__compressed_pair.2"* %0, %"class.std::__1::__compressed_pair.2"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.2"*, %"class.std::__1::__compressed_pair.2"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.2"* %3 to %"struct.std::__1::__compressed_pair_elem.3"*
  %5 = call nonnull align 8 dereferenceable(8) %class.DerivedA** @_ZNSt3__122__compressed_pair_elemIP8DerivedALi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.3"* nonnull align 8 dereferenceable(8) %4) #9
  ret %class.DerivedA** %5
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 1 dereferenceable(1) %"struct.std::__1::default_delete.5"* @_ZNSt3__117__compressed_pairIP8DerivedANS_14default_deleteIS1_EEE6secondEv(%"class.std::__1::__compressed_pair.2"* nonnull align 8 dereferenceable(8) %0) #3 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.2"*, align 8
  store %"class.std::__1::__compressed_pair.2"* %0, %"class.std::__1::__compressed_pair.2"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.2"*, %"class.std::__1::__compressed_pair.2"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.2"* %3 to %"struct.std::__1::__compressed_pair_elem.4"*
  %5 = call nonnull align 1 dereferenceable(1) %"struct.std::__1::default_delete.5"* @_ZNSt3__122__compressed_pair_elemINS_14default_deleteI8DerivedAEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.4"* nonnull align 1 dereferenceable(1) %4) #9
  ret %"struct.std::__1::default_delete.5"* %5
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNKSt3__114default_deleteI8DerivedAEclEPS1_(%"struct.std::__1::default_delete.5"* nonnull align 1 dereferenceable(1) %0, %class.DerivedA* %1) #3 align 2 {
  %3 = alloca %"struct.std::__1::default_delete.5"*, align 8
  %4 = alloca %class.DerivedA*, align 8
  store %"struct.std::__1::default_delete.5"* %0, %"struct.std::__1::default_delete.5"** %3, align 8
  store %class.DerivedA* %1, %class.DerivedA** %4, align 8
  %5 = load %"struct.std::__1::default_delete.5"*, %"struct.std::__1::default_delete.5"** %3, align 8
  %6 = load %class.DerivedA*, %class.DerivedA** %4, align 8
  %7 = icmp eq %class.DerivedA* %6, null
  br i1 %7, label %10, label %8

8:                                                ; preds = %2
  %9 = bitcast %class.DerivedA* %6 to i8*
  call void @_ZdlPv(i8* %9) #12
  br label %10

10:                                               ; preds = %8, %2
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 8 dereferenceable(8) %class.DerivedA** @_ZNSt3__122__compressed_pair_elemIP8DerivedALi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.3"* nonnull align 8 dereferenceable(8) %0) #3 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.3"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.3"* %0, %"struct.std::__1::__compressed_pair_elem.3"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.3"*, %"struct.std::__1::__compressed_pair_elem.3"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.3", %"struct.std::__1::__compressed_pair_elem.3"* %3, i32 0, i32 0
  ret %class.DerivedA** %4
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 1 dereferenceable(1) %"struct.std::__1::default_delete.5"* @_ZNSt3__122__compressed_pair_elemINS_14default_deleteI8DerivedAEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.4"* nonnull align 1 dereferenceable(1) %0) #3 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.4"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.4"* %0, %"struct.std::__1::__compressed_pair_elem.4"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.4"*, %"struct.std::__1::__compressed_pair_elem.4"** %2, align 8
  %4 = bitcast %"struct.std::__1::__compressed_pair_elem.4"* %3 to %"struct.std::__1::default_delete.5"*
  ret %"struct.std::__1::default_delete.5"* %4
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %class.DerivedA* @_ZNSt3__110unique_ptrI8DerivedANS_14default_deleteIS1_EEE7releaseEv(%"class.std::__1::unique_ptr.1"* nonnull align 8 dereferenceable(8) %0) #3 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr.1"*, align 8
  %3 = alloca %class.DerivedA*, align 8
  store %"class.std::__1::unique_ptr.1"* %0, %"class.std::__1::unique_ptr.1"** %2, align 8
  %4 = load %"class.std::__1::unique_ptr.1"*, %"class.std::__1::unique_ptr.1"** %2, align 8
  %5 = getelementptr inbounds %"class.std::__1::unique_ptr.1", %"class.std::__1::unique_ptr.1"* %4, i32 0, i32 0
  %6 = call nonnull align 8 dereferenceable(8) %class.DerivedA** @_ZNSt3__117__compressed_pairIP8DerivedANS_14default_deleteIS1_EEE5firstEv(%"class.std::__1::__compressed_pair.2"* nonnull align 8 dereferenceable(8) %5) #9
  %7 = load %class.DerivedA*, %class.DerivedA** %6, align 8
  store %class.DerivedA* %7, %class.DerivedA** %3, align 8
  %8 = getelementptr inbounds %"class.std::__1::unique_ptr.1", %"class.std::__1::unique_ptr.1"* %4, i32 0, i32 0
  %9 = call nonnull align 8 dereferenceable(8) %class.DerivedA** @_ZNSt3__117__compressed_pairIP8DerivedANS_14default_deleteIS1_EEE5firstEv(%"class.std::__1::__compressed_pair.2"* nonnull align 8 dereferenceable(8) %8) #9
  store %class.DerivedA* null, %class.DerivedA** %9, align 8
  %10 = load %class.DerivedA*, %class.DerivedA** %3, align 8
  ret %class.DerivedA* %10
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 1 dereferenceable(1) %"struct.std::__1::default_delete.5"* @_ZNSt3__17forwardINS_14default_deleteI8DerivedAEEEEOT_RNS_16remove_referenceIS4_E4typeE(%"struct.std::__1::default_delete.5"* nonnull align 1 dereferenceable(1) %0) #3 {
  %2 = alloca %"struct.std::__1::default_delete.5"*, align 8
  store %"struct.std::__1::default_delete.5"* %0, %"struct.std::__1::default_delete.5"** %2, align 8
  %3 = load %"struct.std::__1::default_delete.5"*, %"struct.std::__1::default_delete.5"** %2, align 8
  ret %"struct.std::__1::default_delete.5"* %3
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 1 dereferenceable(1) %"struct.std::__1::default_delete.5"* @_ZNSt3__110unique_ptrI8DerivedANS_14default_deleteIS1_EEE11get_deleterEv(%"class.std::__1::unique_ptr.1"* nonnull align 8 dereferenceable(8) %0) #3 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr.1"*, align 8
  store %"class.std::__1::unique_ptr.1"* %0, %"class.std::__1::unique_ptr.1"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr.1"*, %"class.std::__1::unique_ptr.1"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::unique_ptr.1", %"class.std::__1::unique_ptr.1"* %3, i32 0, i32 0
  %5 = call nonnull align 1 dereferenceable(1) %"struct.std::__1::default_delete.5"* @_ZNSt3__117__compressed_pairIP8DerivedANS_14default_deleteIS1_EEE6secondEv(%"class.std::__1::__compressed_pair.2"* nonnull align 8 dereferenceable(8) %4) #9
  ret %"struct.std::__1::default_delete.5"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %"struct.std::__1::default_delete"* @_ZNSt3__114default_deleteI4BaseEC1I8DerivedAEERKNS0_IT_EEPNS_9enable_ifIXsr14is_convertibleIPS5_PS1_EE5valueEvE4typeE(%"struct.std::__1::default_delete"* nonnull returned align 1 dereferenceable(1) %0, %"struct.std::__1::default_delete.5"* nonnull align 1 dereferenceable(1) %1, i8* %2) unnamed_addr #1 align 2 {
  %4 = alloca %"struct.std::__1::default_delete"*, align 8
  %5 = alloca %"struct.std::__1::default_delete.5"*, align 8
  %6 = alloca i8*, align 8
  store %"struct.std::__1::default_delete"* %0, %"struct.std::__1::default_delete"** %4, align 8
  store %"struct.std::__1::default_delete.5"* %1, %"struct.std::__1::default_delete.5"** %5, align 8
  store i8* %2, i8** %6, align 8
  %7 = load %"struct.std::__1::default_delete"*, %"struct.std::__1::default_delete"** %4, align 8
  %8 = load %"struct.std::__1::default_delete.5"*, %"struct.std::__1::default_delete.5"** %5, align 8
  %9 = load i8*, i8** %6, align 8
  %10 = call %"struct.std::__1::default_delete"* @_ZNSt3__114default_deleteI4BaseEC2I8DerivedAEERKNS0_IT_EEPNS_9enable_ifIXsr14is_convertibleIPS5_PS1_EE5valueEvE4typeE(%"struct.std::__1::default_delete"* nonnull align 1 dereferenceable(1) %7, %"struct.std::__1::default_delete.5"* nonnull align 1 dereferenceable(1) %8, i8* %9) #9
  ret %"struct.std::__1::default_delete"* %7
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %"struct.std::__1::default_delete"* @_ZNSt3__114default_deleteI4BaseEC2I8DerivedAEERKNS0_IT_EEPNS_9enable_ifIXsr14is_convertibleIPS5_PS1_EE5valueEvE4typeE(%"struct.std::__1::default_delete"* nonnull returned align 1 dereferenceable(1) %0, %"struct.std::__1::default_delete.5"* nonnull align 1 dereferenceable(1) %1, i8* %2) unnamed_addr #1 align 2 {
  %4 = alloca %"struct.std::__1::default_delete"*, align 8
  %5 = alloca %"struct.std::__1::default_delete.5"*, align 8
  %6 = alloca i8*, align 8
  store %"struct.std::__1::default_delete"* %0, %"struct.std::__1::default_delete"** %4, align 8
  store %"struct.std::__1::default_delete.5"* %1, %"struct.std::__1::default_delete.5"** %5, align 8
  store i8* %2, i8** %6, align 8
  %7 = load %"struct.std::__1::default_delete"*, %"struct.std::__1::default_delete"** %4, align 8
  ret %"struct.std::__1::default_delete"* %7
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 8 dereferenceable(8) %class.Base** @_ZNKSt3__117__compressed_pairIP4BaseNS_14default_deleteIS1_EEE5firstEv(%"class.std::__1::__compressed_pair"* nonnull align 8 dereferenceable(8) %0) #3 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair"*, align 8
  store %"class.std::__1::__compressed_pair"* %0, %"class.std::__1::__compressed_pair"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair"*, %"class.std::__1::__compressed_pair"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair"* %3 to %"struct.std::__1::__compressed_pair_elem"*
  %5 = call nonnull align 8 dereferenceable(8) %class.Base** @_ZNKSt3__122__compressed_pair_elemIP4BaseLi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem"* nonnull align 8 dereferenceable(8) %4) #9
  ret %class.Base** %5
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define linkonce_odr hidden nonnull align 8 dereferenceable(8) %class.Base** @_ZNKSt3__122__compressed_pair_elemIP4BaseLi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem"* nonnull align 8 dereferenceable(8) %0) #3 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem"*, align 8
  store %"struct.std::__1::__compressed_pair_elem"* %0, %"struct.std::__1::__compressed_pair_elem"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem"*, %"struct.std::__1::__compressed_pair_elem"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem", %"struct.std::__1::__compressed_pair_elem"* %3, i32 0, i32 0
  ret %class.Base** %4
}

attributes #0 = { mustprogress noinline norecurse optnone ssp uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.5a,+zcm,+zcz" }
attributes #1 = { noinline nounwind optnone ssp uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.5a,+zcm,+zcz" }
attributes #2 = { mustprogress noinline optnone ssp uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.5a,+zcm,+zcz" }
attributes #3 = { mustprogress noinline nounwind optnone ssp uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.5a,+zcm,+zcz" }
attributes #4 = { noinline optnone ssp uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.5a,+zcm,+zcz" }
attributes #5 = { noinline noreturn nounwind }
attributes #6 = { nobuiltin nounwind "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.5a,+zcm,+zcz" }
attributes #7 = { nobuiltin allocsize(0) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.5a,+zcm,+zcz" }
attributes #8 = { argmemonly nofree nounwind willreturn writeonly }
attributes #9 = { nounwind }
attributes #10 = { builtin allocsize(0) }
attributes #11 = { noreturn nounwind }
attributes #12 = { builtin nounwind }

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
!8 = !{!"Homebrew clang version 13.0.1"}
