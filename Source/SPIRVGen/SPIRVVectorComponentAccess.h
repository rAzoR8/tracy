#ifndef TRACY_SPIRVVECTORCOMPONENTACCESS_H
#define TRACY_SPIRVVECTORCOMPONENTACCESS_H
TExtractType<1> X() { return ExtractComponent<1, 0>(); } 
template <spv::StorageClass C1> void X(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) { InsertComponent<1, 0>(_var);}
void X(const vec_type_t<base_type_t<T>, 1>& _var) { InsertComponent<1, 0>(var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = X, put = X)) TExtractType<1> x;
__declspec(property(get = X, put = X)) TExtractType<1> r;
TExtractType<2> XX() { return ExtractComponent<2, 0, 0>(); } 
template <spv::StorageClass C1> void XX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 0, 0>(_var);}
void XX(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XX, put = XX)) TExtractType<2> xx;
__declspec(property(get = XX, put = XX)) TExtractType<2> rr;
TExtractType<3> XXX() { return ExtractComponent<3, 0, 0, 0>(); } 
template <spv::StorageClass C1> void XXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 0>(_var);}
void XXX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXX, put = XXX)) TExtractType<3> xxx;
__declspec(property(get = XXX, put = XXX)) TExtractType<3> rrr;
TExtractType<4> XXXX() { return ExtractComponent<3, 0, 0, 0, 0>(); } 
template <spv::StorageClass C1> void XXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 0, 0>(_var);}
void XXXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXXX, put = XXXX)) TExtractType<4> xxx;
__declspec(property(get = XXXX, put = XXXX)) TExtractType<4> rrr;
TExtractType<4> XXXY() { return ExtractComponent<3, 0, 0, 0, 1>(); } 
template <spv::StorageClass C1> void XXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 0, 1>(_var);}
void XXXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXXY, put = XXXY)) TExtractType<4> xxx;
__declspec(property(get = XXXY, put = XXXY)) TExtractType<4> rrr;
TExtractType<4> XXXZ() { return ExtractComponent<3, 0, 0, 0, 2>(); } 
template <spv::StorageClass C1> void XXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 0, 2>(_var);}
void XXXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXXZ, put = XXXZ)) TExtractType<4> xxx;
__declspec(property(get = XXXZ, put = XXXZ)) TExtractType<4> rrr;
TExtractType<4> XXXW() { return ExtractComponent<3, 0, 0, 0, 3>(); } 
template <spv::StorageClass C1> void XXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 0, 3>(_var);}
void XXXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXXW, put = XXXW)) TExtractType<4> xxx;
__declspec(property(get = XXXW, put = XXXW)) TExtractType<4> rrr;
TExtractType<3> XXY() { return ExtractComponent<3, 0, 0, 1>(); } 
template <spv::StorageClass C1> void XXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 1>(_var);}
void XXY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXY, put = XXY)) TExtractType<3> xxy;
__declspec(property(get = XXY, put = XXY)) TExtractType<3> rrg;
TExtractType<4> XXYX() { return ExtractComponent<3, 0, 0, 1, 0>(); } 
template <spv::StorageClass C1> void XXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 1, 0>(_var);}
void XXYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXYX, put = XXYX)) TExtractType<4> xxy;
__declspec(property(get = XXYX, put = XXYX)) TExtractType<4> rrg;
TExtractType<4> XXYY() { return ExtractComponent<3, 0, 0, 1, 1>(); } 
template <spv::StorageClass C1> void XXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 1, 1>(_var);}
void XXYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXYY, put = XXYY)) TExtractType<4> xxy;
__declspec(property(get = XXYY, put = XXYY)) TExtractType<4> rrg;
TExtractType<4> XXYZ() { return ExtractComponent<3, 0, 0, 1, 2>(); } 
template <spv::StorageClass C1> void XXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 1, 2>(_var);}
void XXYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXYZ, put = XXYZ)) TExtractType<4> xxy;
__declspec(property(get = XXYZ, put = XXYZ)) TExtractType<4> rrg;
TExtractType<4> XXYW() { return ExtractComponent<3, 0, 0, 1, 3>(); } 
template <spv::StorageClass C1> void XXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 1, 3>(_var);}
void XXYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXYW, put = XXYW)) TExtractType<4> xxy;
__declspec(property(get = XXYW, put = XXYW)) TExtractType<4> rrg;
TExtractType<3> XXZ() { return ExtractComponent<3, 0, 0, 2>(); } 
template <spv::StorageClass C1> void XXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 2>(_var);}
void XXZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZ, put = XXZ)) TExtractType<3> xxz;
__declspec(property(get = XXZ, put = XXZ)) TExtractType<3> rrb;
TExtractType<4> XXZX() { return ExtractComponent<3, 0, 0, 2, 0>(); } 
template <spv::StorageClass C1> void XXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 2, 0>(_var);}
void XXZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZX, put = XXZX)) TExtractType<4> xxz;
__declspec(property(get = XXZX, put = XXZX)) TExtractType<4> rrb;
TExtractType<4> XXZY() { return ExtractComponent<3, 0, 0, 2, 1>(); } 
template <spv::StorageClass C1> void XXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 2, 1>(_var);}
void XXZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZY, put = XXZY)) TExtractType<4> xxz;
__declspec(property(get = XXZY, put = XXZY)) TExtractType<4> rrb;
TExtractType<4> XXZZ() { return ExtractComponent<3, 0, 0, 2, 2>(); } 
template <spv::StorageClass C1> void XXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 2, 2>(_var);}
void XXZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZZ, put = XXZZ)) TExtractType<4> xxz;
__declspec(property(get = XXZZ, put = XXZZ)) TExtractType<4> rrb;
TExtractType<4> XXZW() { return ExtractComponent<3, 0, 0, 2, 3>(); } 
template <spv::StorageClass C1> void XXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 2, 3>(_var);}
void XXZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZW, put = XXZW)) TExtractType<4> xxz;
__declspec(property(get = XXZW, put = XXZW)) TExtractType<4> rrb;
TExtractType<3> XXW() { return ExtractComponent<3, 0, 0, 3>(); } 
template <spv::StorageClass C1> void XXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 3>(_var);}
void XXW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXW, put = XXW)) TExtractType<3> xxw;
__declspec(property(get = XXW, put = XXW)) TExtractType<3> rra;
TExtractType<4> XXWX() { return ExtractComponent<3, 0, 0, 3, 0>(); } 
template <spv::StorageClass C1> void XXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 3, 0>(_var);}
void XXWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXWX, put = XXWX)) TExtractType<4> xxw;
__declspec(property(get = XXWX, put = XXWX)) TExtractType<4> rra;
TExtractType<4> XXWY() { return ExtractComponent<3, 0, 0, 3, 1>(); } 
template <spv::StorageClass C1> void XXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 3, 1>(_var);}
void XXWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXWY, put = XXWY)) TExtractType<4> xxw;
__declspec(property(get = XXWY, put = XXWY)) TExtractType<4> rra;
TExtractType<4> XXWZ() { return ExtractComponent<3, 0, 0, 3, 2>(); } 
template <spv::StorageClass C1> void XXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 3, 2>(_var);}
void XXWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXWZ, put = XXWZ)) TExtractType<4> xxw;
__declspec(property(get = XXWZ, put = XXWZ)) TExtractType<4> rra;
TExtractType<4> XXWW() { return ExtractComponent<3, 0, 0, 3, 3>(); } 
template <spv::StorageClass C1> void XXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 3, 3>(_var);}
void XXWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXWW, put = XXWW)) TExtractType<4> xxw;
__declspec(property(get = XXWW, put = XXWW)) TExtractType<4> rra;
TExtractType<2> XY() { return ExtractComponent<2, 0, 1>(); } 
template <spv::StorageClass C1> void XY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 0, 1>(_var);}
void XY(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XY, put = XY)) TExtractType<2> xy;
__declspec(property(get = XY, put = XY)) TExtractType<2> rg;
TExtractType<3> XYX() { return ExtractComponent<3, 0, 1, 0>(); } 
template <spv::StorageClass C1> void XYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 0>(_var);}
void XYX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYX, put = XYX)) TExtractType<3> xyx;
__declspec(property(get = XYX, put = XYX)) TExtractType<3> rgr;
TExtractType<4> XYXX() { return ExtractComponent<3, 0, 1, 0, 0>(); } 
template <spv::StorageClass C1> void XYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 0, 0>(_var);}
void XYXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYXX, put = XYXX)) TExtractType<4> xyx;
__declspec(property(get = XYXX, put = XYXX)) TExtractType<4> rgr;
TExtractType<4> XYXY() { return ExtractComponent<3, 0, 1, 0, 1>(); } 
template <spv::StorageClass C1> void XYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 0, 1>(_var);}
void XYXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYXY, put = XYXY)) TExtractType<4> xyx;
__declspec(property(get = XYXY, put = XYXY)) TExtractType<4> rgr;
TExtractType<4> XYXZ() { return ExtractComponent<3, 0, 1, 0, 2>(); } 
template <spv::StorageClass C1> void XYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 0, 2>(_var);}
void XYXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYXZ, put = XYXZ)) TExtractType<4> xyx;
__declspec(property(get = XYXZ, put = XYXZ)) TExtractType<4> rgr;
TExtractType<4> XYXW() { return ExtractComponent<3, 0, 1, 0, 3>(); } 
template <spv::StorageClass C1> void XYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 0, 3>(_var);}
void XYXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYXW, put = XYXW)) TExtractType<4> xyx;
__declspec(property(get = XYXW, put = XYXW)) TExtractType<4> rgr;
TExtractType<3> XYY() { return ExtractComponent<3, 0, 1, 1>(); } 
template <spv::StorageClass C1> void XYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 1>(_var);}
void XYY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYY, put = XYY)) TExtractType<3> xyy;
__declspec(property(get = XYY, put = XYY)) TExtractType<3> rgg;
TExtractType<4> XYYX() { return ExtractComponent<3, 0, 1, 1, 0>(); } 
template <spv::StorageClass C1> void XYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 1, 0>(_var);}
void XYYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYYX, put = XYYX)) TExtractType<4> xyy;
__declspec(property(get = XYYX, put = XYYX)) TExtractType<4> rgg;
TExtractType<4> XYYY() { return ExtractComponent<3, 0, 1, 1, 1>(); } 
template <spv::StorageClass C1> void XYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 1, 1>(_var);}
void XYYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYYY, put = XYYY)) TExtractType<4> xyy;
__declspec(property(get = XYYY, put = XYYY)) TExtractType<4> rgg;
TExtractType<4> XYYZ() { return ExtractComponent<3, 0, 1, 1, 2>(); } 
template <spv::StorageClass C1> void XYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 1, 2>(_var);}
void XYYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYYZ, put = XYYZ)) TExtractType<4> xyy;
__declspec(property(get = XYYZ, put = XYYZ)) TExtractType<4> rgg;
TExtractType<4> XYYW() { return ExtractComponent<3, 0, 1, 1, 3>(); } 
template <spv::StorageClass C1> void XYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 1, 3>(_var);}
void XYYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYYW, put = XYYW)) TExtractType<4> xyy;
__declspec(property(get = XYYW, put = XYYW)) TExtractType<4> rgg;
TExtractType<3> XYZ() { return ExtractComponent<3, 0, 1, 2>(); } 
template <spv::StorageClass C1> void XYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 2>(_var);}
void XYZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZ, put = XYZ)) TExtractType<3> xyz;
__declspec(property(get = XYZ, put = XYZ)) TExtractType<3> rgb;
TExtractType<4> XYZX() { return ExtractComponent<3, 0, 1, 2, 0>(); } 
template <spv::StorageClass C1> void XYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 2, 0>(_var);}
void XYZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZX, put = XYZX)) TExtractType<4> xyz;
__declspec(property(get = XYZX, put = XYZX)) TExtractType<4> rgb;
TExtractType<4> XYZY() { return ExtractComponent<3, 0, 1, 2, 1>(); } 
template <spv::StorageClass C1> void XYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 2, 1>(_var);}
void XYZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZY, put = XYZY)) TExtractType<4> xyz;
__declspec(property(get = XYZY, put = XYZY)) TExtractType<4> rgb;
TExtractType<4> XYZZ() { return ExtractComponent<3, 0, 1, 2, 2>(); } 
template <spv::StorageClass C1> void XYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 2, 2>(_var);}
void XYZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZZ, put = XYZZ)) TExtractType<4> xyz;
__declspec(property(get = XYZZ, put = XYZZ)) TExtractType<4> rgb;
TExtractType<4> XYZW() { return ExtractComponent<3, 0, 1, 2, 3>(); } 
template <spv::StorageClass C1> void XYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 2, 3>(_var);}
void XYZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZW, put = XYZW)) TExtractType<4> xyz;
__declspec(property(get = XYZW, put = XYZW)) TExtractType<4> rgb;
TExtractType<3> XYW() { return ExtractComponent<3, 0, 1, 3>(); } 
template <spv::StorageClass C1> void XYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 3>(_var);}
void XYW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYW, put = XYW)) TExtractType<3> xyw;
__declspec(property(get = XYW, put = XYW)) TExtractType<3> rga;
TExtractType<4> XYWX() { return ExtractComponent<3, 0, 1, 3, 0>(); } 
template <spv::StorageClass C1> void XYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 3, 0>(_var);}
void XYWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYWX, put = XYWX)) TExtractType<4> xyw;
__declspec(property(get = XYWX, put = XYWX)) TExtractType<4> rga;
TExtractType<4> XYWY() { return ExtractComponent<3, 0, 1, 3, 1>(); } 
template <spv::StorageClass C1> void XYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 3, 1>(_var);}
void XYWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYWY, put = XYWY)) TExtractType<4> xyw;
__declspec(property(get = XYWY, put = XYWY)) TExtractType<4> rga;
TExtractType<4> XYWZ() { return ExtractComponent<3, 0, 1, 3, 2>(); } 
template <spv::StorageClass C1> void XYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 3, 2>(_var);}
void XYWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYWZ, put = XYWZ)) TExtractType<4> xyw;
__declspec(property(get = XYWZ, put = XYWZ)) TExtractType<4> rga;
TExtractType<4> XYWW() { return ExtractComponent<3, 0, 1, 3, 3>(); } 
template <spv::StorageClass C1> void XYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 3, 3>(_var);}
void XYWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYWW, put = XYWW)) TExtractType<4> xyw;
__declspec(property(get = XYWW, put = XYWW)) TExtractType<4> rga;
TExtractType<2> XZ() { return ExtractComponent<2, 0, 2>(); } 
template <spv::StorageClass C1> void XZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 0, 2>(_var);}
void XZ(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZ, put = XZ)) TExtractType<2> xz;
__declspec(property(get = XZ, put = XZ)) TExtractType<2> rb;
TExtractType<3> XZX() { return ExtractComponent<3, 0, 2, 0>(); } 
template <spv::StorageClass C1> void XZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 0>(_var);}
void XZX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZX, put = XZX)) TExtractType<3> xzx;
__declspec(property(get = XZX, put = XZX)) TExtractType<3> rbr;
TExtractType<4> XZXX() { return ExtractComponent<3, 0, 2, 0, 0>(); } 
template <spv::StorageClass C1> void XZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 0, 0>(_var);}
void XZXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZXX, put = XZXX)) TExtractType<4> xzx;
__declspec(property(get = XZXX, put = XZXX)) TExtractType<4> rbr;
TExtractType<4> XZXY() { return ExtractComponent<3, 0, 2, 0, 1>(); } 
template <spv::StorageClass C1> void XZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 0, 1>(_var);}
void XZXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZXY, put = XZXY)) TExtractType<4> xzx;
__declspec(property(get = XZXY, put = XZXY)) TExtractType<4> rbr;
TExtractType<4> XZXZ() { return ExtractComponent<3, 0, 2, 0, 2>(); } 
template <spv::StorageClass C1> void XZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 0, 2>(_var);}
void XZXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZXZ, put = XZXZ)) TExtractType<4> xzx;
__declspec(property(get = XZXZ, put = XZXZ)) TExtractType<4> rbr;
TExtractType<4> XZXW() { return ExtractComponent<3, 0, 2, 0, 3>(); } 
template <spv::StorageClass C1> void XZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 0, 3>(_var);}
void XZXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZXW, put = XZXW)) TExtractType<4> xzx;
__declspec(property(get = XZXW, put = XZXW)) TExtractType<4> rbr;
TExtractType<3> XZY() { return ExtractComponent<3, 0, 2, 1>(); } 
template <spv::StorageClass C1> void XZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 1>(_var);}
void XZY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZY, put = XZY)) TExtractType<3> xzy;
__declspec(property(get = XZY, put = XZY)) TExtractType<3> rbg;
TExtractType<4> XZYX() { return ExtractComponent<3, 0, 2, 1, 0>(); } 
template <spv::StorageClass C1> void XZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 1, 0>(_var);}
void XZYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZYX, put = XZYX)) TExtractType<4> xzy;
__declspec(property(get = XZYX, put = XZYX)) TExtractType<4> rbg;
TExtractType<4> XZYY() { return ExtractComponent<3, 0, 2, 1, 1>(); } 
template <spv::StorageClass C1> void XZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 1, 1>(_var);}
void XZYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZYY, put = XZYY)) TExtractType<4> xzy;
__declspec(property(get = XZYY, put = XZYY)) TExtractType<4> rbg;
TExtractType<4> XZYZ() { return ExtractComponent<3, 0, 2, 1, 2>(); } 
template <spv::StorageClass C1> void XZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 1, 2>(_var);}
void XZYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZYZ, put = XZYZ)) TExtractType<4> xzy;
__declspec(property(get = XZYZ, put = XZYZ)) TExtractType<4> rbg;
TExtractType<4> XZYW() { return ExtractComponent<3, 0, 2, 1, 3>(); } 
template <spv::StorageClass C1> void XZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 1, 3>(_var);}
void XZYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZYW, put = XZYW)) TExtractType<4> xzy;
__declspec(property(get = XZYW, put = XZYW)) TExtractType<4> rbg;
TExtractType<3> XZZ() { return ExtractComponent<3, 0, 2, 2>(); } 
template <spv::StorageClass C1> void XZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 2>(_var);}
void XZZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZ, put = XZZ)) TExtractType<3> xzz;
__declspec(property(get = XZZ, put = XZZ)) TExtractType<3> rbb;
TExtractType<4> XZZX() { return ExtractComponent<3, 0, 2, 2, 0>(); } 
template <spv::StorageClass C1> void XZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 2, 0>(_var);}
void XZZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZX, put = XZZX)) TExtractType<4> xzz;
__declspec(property(get = XZZX, put = XZZX)) TExtractType<4> rbb;
TExtractType<4> XZZY() { return ExtractComponent<3, 0, 2, 2, 1>(); } 
template <spv::StorageClass C1> void XZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 2, 1>(_var);}
void XZZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZY, put = XZZY)) TExtractType<4> xzz;
__declspec(property(get = XZZY, put = XZZY)) TExtractType<4> rbb;
TExtractType<4> XZZZ() { return ExtractComponent<3, 0, 2, 2, 2>(); } 
template <spv::StorageClass C1> void XZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 2, 2>(_var);}
void XZZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZZ, put = XZZZ)) TExtractType<4> xzz;
__declspec(property(get = XZZZ, put = XZZZ)) TExtractType<4> rbb;
TExtractType<4> XZZW() { return ExtractComponent<3, 0, 2, 2, 3>(); } 
template <spv::StorageClass C1> void XZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 2, 3>(_var);}
void XZZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZW, put = XZZW)) TExtractType<4> xzz;
__declspec(property(get = XZZW, put = XZZW)) TExtractType<4> rbb;
TExtractType<3> XZW() { return ExtractComponent<3, 0, 2, 3>(); } 
template <spv::StorageClass C1> void XZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 3>(_var);}
void XZW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZW, put = XZW)) TExtractType<3> xzw;
__declspec(property(get = XZW, put = XZW)) TExtractType<3> rba;
TExtractType<4> XZWX() { return ExtractComponent<3, 0, 2, 3, 0>(); } 
template <spv::StorageClass C1> void XZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 3, 0>(_var);}
void XZWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZWX, put = XZWX)) TExtractType<4> xzw;
__declspec(property(get = XZWX, put = XZWX)) TExtractType<4> rba;
TExtractType<4> XZWY() { return ExtractComponent<3, 0, 2, 3, 1>(); } 
template <spv::StorageClass C1> void XZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 3, 1>(_var);}
void XZWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZWY, put = XZWY)) TExtractType<4> xzw;
__declspec(property(get = XZWY, put = XZWY)) TExtractType<4> rba;
TExtractType<4> XZWZ() { return ExtractComponent<3, 0, 2, 3, 2>(); } 
template <spv::StorageClass C1> void XZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 3, 2>(_var);}
void XZWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZWZ, put = XZWZ)) TExtractType<4> xzw;
__declspec(property(get = XZWZ, put = XZWZ)) TExtractType<4> rba;
TExtractType<4> XZWW() { return ExtractComponent<3, 0, 2, 3, 3>(); } 
template <spv::StorageClass C1> void XZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 3, 3>(_var);}
void XZWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZWW, put = XZWW)) TExtractType<4> xzw;
__declspec(property(get = XZWW, put = XZWW)) TExtractType<4> rba;
TExtractType<2> XW() { return ExtractComponent<2, 0, 3>(); } 
template <spv::StorageClass C1> void XW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 0, 3>(_var);}
void XW(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XW, put = XW)) TExtractType<2> xw;
__declspec(property(get = XW, put = XW)) TExtractType<2> ra;
TExtractType<3> XWX() { return ExtractComponent<3, 0, 3, 0>(); } 
template <spv::StorageClass C1> void XWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 0>(_var);}
void XWX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWX, put = XWX)) TExtractType<3> xwx;
__declspec(property(get = XWX, put = XWX)) TExtractType<3> rar;
TExtractType<4> XWXX() { return ExtractComponent<3, 0, 3, 0, 0>(); } 
template <spv::StorageClass C1> void XWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 0, 0>(_var);}
void XWXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWXX, put = XWXX)) TExtractType<4> xwx;
__declspec(property(get = XWXX, put = XWXX)) TExtractType<4> rar;
TExtractType<4> XWXY() { return ExtractComponent<3, 0, 3, 0, 1>(); } 
template <spv::StorageClass C1> void XWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 0, 1>(_var);}
void XWXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWXY, put = XWXY)) TExtractType<4> xwx;
__declspec(property(get = XWXY, put = XWXY)) TExtractType<4> rar;
TExtractType<4> XWXZ() { return ExtractComponent<3, 0, 3, 0, 2>(); } 
template <spv::StorageClass C1> void XWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 0, 2>(_var);}
void XWXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWXZ, put = XWXZ)) TExtractType<4> xwx;
__declspec(property(get = XWXZ, put = XWXZ)) TExtractType<4> rar;
TExtractType<4> XWXW() { return ExtractComponent<3, 0, 3, 0, 3>(); } 
template <spv::StorageClass C1> void XWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 0, 3>(_var);}
void XWXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWXW, put = XWXW)) TExtractType<4> xwx;
__declspec(property(get = XWXW, put = XWXW)) TExtractType<4> rar;
TExtractType<3> XWY() { return ExtractComponent<3, 0, 3, 1>(); } 
template <spv::StorageClass C1> void XWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 1>(_var);}
void XWY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWY, put = XWY)) TExtractType<3> xwy;
__declspec(property(get = XWY, put = XWY)) TExtractType<3> rag;
TExtractType<4> XWYX() { return ExtractComponent<3, 0, 3, 1, 0>(); } 
template <spv::StorageClass C1> void XWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 1, 0>(_var);}
void XWYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWYX, put = XWYX)) TExtractType<4> xwy;
__declspec(property(get = XWYX, put = XWYX)) TExtractType<4> rag;
TExtractType<4> XWYY() { return ExtractComponent<3, 0, 3, 1, 1>(); } 
template <spv::StorageClass C1> void XWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 1, 1>(_var);}
void XWYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWYY, put = XWYY)) TExtractType<4> xwy;
__declspec(property(get = XWYY, put = XWYY)) TExtractType<4> rag;
TExtractType<4> XWYZ() { return ExtractComponent<3, 0, 3, 1, 2>(); } 
template <spv::StorageClass C1> void XWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 1, 2>(_var);}
void XWYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWYZ, put = XWYZ)) TExtractType<4> xwy;
__declspec(property(get = XWYZ, put = XWYZ)) TExtractType<4> rag;
TExtractType<4> XWYW() { return ExtractComponent<3, 0, 3, 1, 3>(); } 
template <spv::StorageClass C1> void XWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 1, 3>(_var);}
void XWYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWYW, put = XWYW)) TExtractType<4> xwy;
__declspec(property(get = XWYW, put = XWYW)) TExtractType<4> rag;
TExtractType<3> XWZ() { return ExtractComponent<3, 0, 3, 2>(); } 
template <spv::StorageClass C1> void XWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 2>(_var);}
void XWZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZ, put = XWZ)) TExtractType<3> xwz;
__declspec(property(get = XWZ, put = XWZ)) TExtractType<3> rab;
TExtractType<4> XWZX() { return ExtractComponent<3, 0, 3, 2, 0>(); } 
template <spv::StorageClass C1> void XWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 2, 0>(_var);}
void XWZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZX, put = XWZX)) TExtractType<4> xwz;
__declspec(property(get = XWZX, put = XWZX)) TExtractType<4> rab;
TExtractType<4> XWZY() { return ExtractComponent<3, 0, 3, 2, 1>(); } 
template <spv::StorageClass C1> void XWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 2, 1>(_var);}
void XWZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZY, put = XWZY)) TExtractType<4> xwz;
__declspec(property(get = XWZY, put = XWZY)) TExtractType<4> rab;
TExtractType<4> XWZZ() { return ExtractComponent<3, 0, 3, 2, 2>(); } 
template <spv::StorageClass C1> void XWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 2, 2>(_var);}
void XWZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZZ, put = XWZZ)) TExtractType<4> xwz;
__declspec(property(get = XWZZ, put = XWZZ)) TExtractType<4> rab;
TExtractType<4> XWZW() { return ExtractComponent<3, 0, 3, 2, 3>(); } 
template <spv::StorageClass C1> void XWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 2, 3>(_var);}
void XWZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZW, put = XWZW)) TExtractType<4> xwz;
__declspec(property(get = XWZW, put = XWZW)) TExtractType<4> rab;
TExtractType<3> XWW() { return ExtractComponent<3, 0, 3, 3>(); } 
template <spv::StorageClass C1> void XWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 3>(_var);}
void XWW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWW, put = XWW)) TExtractType<3> xww;
__declspec(property(get = XWW, put = XWW)) TExtractType<3> raa;
TExtractType<4> XWWX() { return ExtractComponent<3, 0, 3, 3, 0>(); } 
template <spv::StorageClass C1> void XWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 3, 0>(_var);}
void XWWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWWX, put = XWWX)) TExtractType<4> xww;
__declspec(property(get = XWWX, put = XWWX)) TExtractType<4> raa;
TExtractType<4> XWWY() { return ExtractComponent<3, 0, 3, 3, 1>(); } 
template <spv::StorageClass C1> void XWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 3, 1>(_var);}
void XWWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWWY, put = XWWY)) TExtractType<4> xww;
__declspec(property(get = XWWY, put = XWWY)) TExtractType<4> raa;
TExtractType<4> XWWZ() { return ExtractComponent<3, 0, 3, 3, 2>(); } 
template <spv::StorageClass C1> void XWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 3, 2>(_var);}
void XWWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWWZ, put = XWWZ)) TExtractType<4> xww;
__declspec(property(get = XWWZ, put = XWWZ)) TExtractType<4> raa;
TExtractType<4> XWWW() { return ExtractComponent<3, 0, 3, 3, 3>(); } 
template <spv::StorageClass C1> void XWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 3, 3>(_var);}
void XWWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWWW, put = XWWW)) TExtractType<4> xww;
__declspec(property(get = XWWW, put = XWWW)) TExtractType<4> raa;
TExtractType<1> Y() { return ExtractComponent<1, 1>(); } 
template <spv::StorageClass C1> void Y(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) { InsertComponent<1, 1>(_var);}
void Y(const vec_type_t<base_type_t<T>, 1>& _var) { InsertComponent<1, 1>(var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = Y, put = Y)) TExtractType<1> y;
__declspec(property(get = Y, put = Y)) TExtractType<1> g;
TExtractType<2> YX() { return ExtractComponent<2, 1, 0>(); } 
template <spv::StorageClass C1> void YX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 1, 0>(_var);}
void YX(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YX, put = YX)) TExtractType<2> yx;
__declspec(property(get = YX, put = YX)) TExtractType<2> gr;
TExtractType<3> YXX() { return ExtractComponent<3, 1, 0, 0>(); } 
template <spv::StorageClass C1> void YXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 0>(_var);}
void YXX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXX, put = YXX)) TExtractType<3> yxx;
__declspec(property(get = YXX, put = YXX)) TExtractType<3> grr;
TExtractType<4> YXXX() { return ExtractComponent<3, 1, 0, 0, 0>(); } 
template <spv::StorageClass C1> void YXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 0, 0>(_var);}
void YXXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXXX, put = YXXX)) TExtractType<4> yxx;
__declspec(property(get = YXXX, put = YXXX)) TExtractType<4> grr;
TExtractType<4> YXXY() { return ExtractComponent<3, 1, 0, 0, 1>(); } 
template <spv::StorageClass C1> void YXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 0, 1>(_var);}
void YXXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXXY, put = YXXY)) TExtractType<4> yxx;
__declspec(property(get = YXXY, put = YXXY)) TExtractType<4> grr;
TExtractType<4> YXXZ() { return ExtractComponent<3, 1, 0, 0, 2>(); } 
template <spv::StorageClass C1> void YXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 0, 2>(_var);}
void YXXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXXZ, put = YXXZ)) TExtractType<4> yxx;
__declspec(property(get = YXXZ, put = YXXZ)) TExtractType<4> grr;
TExtractType<4> YXXW() { return ExtractComponent<3, 1, 0, 0, 3>(); } 
template <spv::StorageClass C1> void YXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 0, 3>(_var);}
void YXXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXXW, put = YXXW)) TExtractType<4> yxx;
__declspec(property(get = YXXW, put = YXXW)) TExtractType<4> grr;
TExtractType<3> YXY() { return ExtractComponent<3, 1, 0, 1>(); } 
template <spv::StorageClass C1> void YXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 1>(_var);}
void YXY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXY, put = YXY)) TExtractType<3> yxy;
__declspec(property(get = YXY, put = YXY)) TExtractType<3> grg;
TExtractType<4> YXYX() { return ExtractComponent<3, 1, 0, 1, 0>(); } 
template <spv::StorageClass C1> void YXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 1, 0>(_var);}
void YXYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXYX, put = YXYX)) TExtractType<4> yxy;
__declspec(property(get = YXYX, put = YXYX)) TExtractType<4> grg;
TExtractType<4> YXYY() { return ExtractComponent<3, 1, 0, 1, 1>(); } 
template <spv::StorageClass C1> void YXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 1, 1>(_var);}
void YXYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXYY, put = YXYY)) TExtractType<4> yxy;
__declspec(property(get = YXYY, put = YXYY)) TExtractType<4> grg;
TExtractType<4> YXYZ() { return ExtractComponent<3, 1, 0, 1, 2>(); } 
template <spv::StorageClass C1> void YXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 1, 2>(_var);}
void YXYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXYZ, put = YXYZ)) TExtractType<4> yxy;
__declspec(property(get = YXYZ, put = YXYZ)) TExtractType<4> grg;
TExtractType<4> YXYW() { return ExtractComponent<3, 1, 0, 1, 3>(); } 
template <spv::StorageClass C1> void YXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 1, 3>(_var);}
void YXYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXYW, put = YXYW)) TExtractType<4> yxy;
__declspec(property(get = YXYW, put = YXYW)) TExtractType<4> grg;
TExtractType<3> YXZ() { return ExtractComponent<3, 1, 0, 2>(); } 
template <spv::StorageClass C1> void YXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 2>(_var);}
void YXZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZ, put = YXZ)) TExtractType<3> yxz;
__declspec(property(get = YXZ, put = YXZ)) TExtractType<3> grb;
TExtractType<4> YXZX() { return ExtractComponent<3, 1, 0, 2, 0>(); } 
template <spv::StorageClass C1> void YXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 2, 0>(_var);}
void YXZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZX, put = YXZX)) TExtractType<4> yxz;
__declspec(property(get = YXZX, put = YXZX)) TExtractType<4> grb;
TExtractType<4> YXZY() { return ExtractComponent<3, 1, 0, 2, 1>(); } 
template <spv::StorageClass C1> void YXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 2, 1>(_var);}
void YXZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZY, put = YXZY)) TExtractType<4> yxz;
__declspec(property(get = YXZY, put = YXZY)) TExtractType<4> grb;
TExtractType<4> YXZZ() { return ExtractComponent<3, 1, 0, 2, 2>(); } 
template <spv::StorageClass C1> void YXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 2, 2>(_var);}
void YXZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZZ, put = YXZZ)) TExtractType<4> yxz;
__declspec(property(get = YXZZ, put = YXZZ)) TExtractType<4> grb;
TExtractType<4> YXZW() { return ExtractComponent<3, 1, 0, 2, 3>(); } 
template <spv::StorageClass C1> void YXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 2, 3>(_var);}
void YXZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZW, put = YXZW)) TExtractType<4> yxz;
__declspec(property(get = YXZW, put = YXZW)) TExtractType<4> grb;
TExtractType<3> YXW() { return ExtractComponent<3, 1, 0, 3>(); } 
template <spv::StorageClass C1> void YXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 3>(_var);}
void YXW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXW, put = YXW)) TExtractType<3> yxw;
__declspec(property(get = YXW, put = YXW)) TExtractType<3> gra;
TExtractType<4> YXWX() { return ExtractComponent<3, 1, 0, 3, 0>(); } 
template <spv::StorageClass C1> void YXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 3, 0>(_var);}
void YXWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXWX, put = YXWX)) TExtractType<4> yxw;
__declspec(property(get = YXWX, put = YXWX)) TExtractType<4> gra;
TExtractType<4> YXWY() { return ExtractComponent<3, 1, 0, 3, 1>(); } 
template <spv::StorageClass C1> void YXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 3, 1>(_var);}
void YXWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXWY, put = YXWY)) TExtractType<4> yxw;
__declspec(property(get = YXWY, put = YXWY)) TExtractType<4> gra;
TExtractType<4> YXWZ() { return ExtractComponent<3, 1, 0, 3, 2>(); } 
template <spv::StorageClass C1> void YXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 3, 2>(_var);}
void YXWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXWZ, put = YXWZ)) TExtractType<4> yxw;
__declspec(property(get = YXWZ, put = YXWZ)) TExtractType<4> gra;
TExtractType<4> YXWW() { return ExtractComponent<3, 1, 0, 3, 3>(); } 
template <spv::StorageClass C1> void YXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 3, 3>(_var);}
void YXWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXWW, put = YXWW)) TExtractType<4> yxw;
__declspec(property(get = YXWW, put = YXWW)) TExtractType<4> gra;
TExtractType<2> YY() { return ExtractComponent<2, 1, 1>(); } 
template <spv::StorageClass C1> void YY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 1, 1>(_var);}
void YY(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YY, put = YY)) TExtractType<2> yy;
__declspec(property(get = YY, put = YY)) TExtractType<2> gg;
TExtractType<3> YYX() { return ExtractComponent<3, 1, 1, 0>(); } 
template <spv::StorageClass C1> void YYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 0>(_var);}
void YYX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYX, put = YYX)) TExtractType<3> yyx;
__declspec(property(get = YYX, put = YYX)) TExtractType<3> ggr;
TExtractType<4> YYXX() { return ExtractComponent<3, 1, 1, 0, 0>(); } 
template <spv::StorageClass C1> void YYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 0, 0>(_var);}
void YYXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYXX, put = YYXX)) TExtractType<4> yyx;
__declspec(property(get = YYXX, put = YYXX)) TExtractType<4> ggr;
TExtractType<4> YYXY() { return ExtractComponent<3, 1, 1, 0, 1>(); } 
template <spv::StorageClass C1> void YYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 0, 1>(_var);}
void YYXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYXY, put = YYXY)) TExtractType<4> yyx;
__declspec(property(get = YYXY, put = YYXY)) TExtractType<4> ggr;
TExtractType<4> YYXZ() { return ExtractComponent<3, 1, 1, 0, 2>(); } 
template <spv::StorageClass C1> void YYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 0, 2>(_var);}
void YYXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYXZ, put = YYXZ)) TExtractType<4> yyx;
__declspec(property(get = YYXZ, put = YYXZ)) TExtractType<4> ggr;
TExtractType<4> YYXW() { return ExtractComponent<3, 1, 1, 0, 3>(); } 
template <spv::StorageClass C1> void YYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 0, 3>(_var);}
void YYXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYXW, put = YYXW)) TExtractType<4> yyx;
__declspec(property(get = YYXW, put = YYXW)) TExtractType<4> ggr;
TExtractType<3> YYY() { return ExtractComponent<3, 1, 1, 1>(); } 
template <spv::StorageClass C1> void YYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 1>(_var);}
void YYY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYY, put = YYY)) TExtractType<3> yyy;
__declspec(property(get = YYY, put = YYY)) TExtractType<3> ggg;
TExtractType<4> YYYX() { return ExtractComponent<3, 1, 1, 1, 0>(); } 
template <spv::StorageClass C1> void YYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 1, 0>(_var);}
void YYYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYYX, put = YYYX)) TExtractType<4> yyy;
__declspec(property(get = YYYX, put = YYYX)) TExtractType<4> ggg;
TExtractType<4> YYYY() { return ExtractComponent<3, 1, 1, 1, 1>(); } 
template <spv::StorageClass C1> void YYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 1, 1>(_var);}
void YYYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYYY, put = YYYY)) TExtractType<4> yyy;
__declspec(property(get = YYYY, put = YYYY)) TExtractType<4> ggg;
TExtractType<4> YYYZ() { return ExtractComponent<3, 1, 1, 1, 2>(); } 
template <spv::StorageClass C1> void YYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 1, 2>(_var);}
void YYYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYYZ, put = YYYZ)) TExtractType<4> yyy;
__declspec(property(get = YYYZ, put = YYYZ)) TExtractType<4> ggg;
TExtractType<4> YYYW() { return ExtractComponent<3, 1, 1, 1, 3>(); } 
template <spv::StorageClass C1> void YYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 1, 3>(_var);}
void YYYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYYW, put = YYYW)) TExtractType<4> yyy;
__declspec(property(get = YYYW, put = YYYW)) TExtractType<4> ggg;
TExtractType<3> YYZ() { return ExtractComponent<3, 1, 1, 2>(); } 
template <spv::StorageClass C1> void YYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 2>(_var);}
void YYZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZ, put = YYZ)) TExtractType<3> yyz;
__declspec(property(get = YYZ, put = YYZ)) TExtractType<3> ggb;
TExtractType<4> YYZX() { return ExtractComponent<3, 1, 1, 2, 0>(); } 
template <spv::StorageClass C1> void YYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 2, 0>(_var);}
void YYZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZX, put = YYZX)) TExtractType<4> yyz;
__declspec(property(get = YYZX, put = YYZX)) TExtractType<4> ggb;
TExtractType<4> YYZY() { return ExtractComponent<3, 1, 1, 2, 1>(); } 
template <spv::StorageClass C1> void YYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 2, 1>(_var);}
void YYZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZY, put = YYZY)) TExtractType<4> yyz;
__declspec(property(get = YYZY, put = YYZY)) TExtractType<4> ggb;
TExtractType<4> YYZZ() { return ExtractComponent<3, 1, 1, 2, 2>(); } 
template <spv::StorageClass C1> void YYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 2, 2>(_var);}
void YYZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZZ, put = YYZZ)) TExtractType<4> yyz;
__declspec(property(get = YYZZ, put = YYZZ)) TExtractType<4> ggb;
TExtractType<4> YYZW() { return ExtractComponent<3, 1, 1, 2, 3>(); } 
template <spv::StorageClass C1> void YYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 2, 3>(_var);}
void YYZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZW, put = YYZW)) TExtractType<4> yyz;
__declspec(property(get = YYZW, put = YYZW)) TExtractType<4> ggb;
TExtractType<3> YYW() { return ExtractComponent<3, 1, 1, 3>(); } 
template <spv::StorageClass C1> void YYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 3>(_var);}
void YYW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYW, put = YYW)) TExtractType<3> yyw;
__declspec(property(get = YYW, put = YYW)) TExtractType<3> gga;
TExtractType<4> YYWX() { return ExtractComponent<3, 1, 1, 3, 0>(); } 
template <spv::StorageClass C1> void YYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 3, 0>(_var);}
void YYWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYWX, put = YYWX)) TExtractType<4> yyw;
__declspec(property(get = YYWX, put = YYWX)) TExtractType<4> gga;
TExtractType<4> YYWY() { return ExtractComponent<3, 1, 1, 3, 1>(); } 
template <spv::StorageClass C1> void YYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 3, 1>(_var);}
void YYWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYWY, put = YYWY)) TExtractType<4> yyw;
__declspec(property(get = YYWY, put = YYWY)) TExtractType<4> gga;
TExtractType<4> YYWZ() { return ExtractComponent<3, 1, 1, 3, 2>(); } 
template <spv::StorageClass C1> void YYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 3, 2>(_var);}
void YYWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYWZ, put = YYWZ)) TExtractType<4> yyw;
__declspec(property(get = YYWZ, put = YYWZ)) TExtractType<4> gga;
TExtractType<4> YYWW() { return ExtractComponent<3, 1, 1, 3, 3>(); } 
template <spv::StorageClass C1> void YYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 3, 3>(_var);}
void YYWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYWW, put = YYWW)) TExtractType<4> yyw;
__declspec(property(get = YYWW, put = YYWW)) TExtractType<4> gga;
TExtractType<2> YZ() { return ExtractComponent<2, 1, 2>(); } 
template <spv::StorageClass C1> void YZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 1, 2>(_var);}
void YZ(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZ, put = YZ)) TExtractType<2> yz;
__declspec(property(get = YZ, put = YZ)) TExtractType<2> gb;
TExtractType<3> YZX() { return ExtractComponent<3, 1, 2, 0>(); } 
template <spv::StorageClass C1> void YZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 0>(_var);}
void YZX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZX, put = YZX)) TExtractType<3> yzx;
__declspec(property(get = YZX, put = YZX)) TExtractType<3> gbr;
TExtractType<4> YZXX() { return ExtractComponent<3, 1, 2, 0, 0>(); } 
template <spv::StorageClass C1> void YZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 0, 0>(_var);}
void YZXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZXX, put = YZXX)) TExtractType<4> yzx;
__declspec(property(get = YZXX, put = YZXX)) TExtractType<4> gbr;
TExtractType<4> YZXY() { return ExtractComponent<3, 1, 2, 0, 1>(); } 
template <spv::StorageClass C1> void YZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 0, 1>(_var);}
void YZXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZXY, put = YZXY)) TExtractType<4> yzx;
__declspec(property(get = YZXY, put = YZXY)) TExtractType<4> gbr;
TExtractType<4> YZXZ() { return ExtractComponent<3, 1, 2, 0, 2>(); } 
template <spv::StorageClass C1> void YZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 0, 2>(_var);}
void YZXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZXZ, put = YZXZ)) TExtractType<4> yzx;
__declspec(property(get = YZXZ, put = YZXZ)) TExtractType<4> gbr;
TExtractType<4> YZXW() { return ExtractComponent<3, 1, 2, 0, 3>(); } 
template <spv::StorageClass C1> void YZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 0, 3>(_var);}
void YZXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZXW, put = YZXW)) TExtractType<4> yzx;
__declspec(property(get = YZXW, put = YZXW)) TExtractType<4> gbr;
TExtractType<3> YZY() { return ExtractComponent<3, 1, 2, 1>(); } 
template <spv::StorageClass C1> void YZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 1>(_var);}
void YZY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZY, put = YZY)) TExtractType<3> yzy;
__declspec(property(get = YZY, put = YZY)) TExtractType<3> gbg;
TExtractType<4> YZYX() { return ExtractComponent<3, 1, 2, 1, 0>(); } 
template <spv::StorageClass C1> void YZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 1, 0>(_var);}
void YZYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZYX, put = YZYX)) TExtractType<4> yzy;
__declspec(property(get = YZYX, put = YZYX)) TExtractType<4> gbg;
TExtractType<4> YZYY() { return ExtractComponent<3, 1, 2, 1, 1>(); } 
template <spv::StorageClass C1> void YZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 1, 1>(_var);}
void YZYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZYY, put = YZYY)) TExtractType<4> yzy;
__declspec(property(get = YZYY, put = YZYY)) TExtractType<4> gbg;
TExtractType<4> YZYZ() { return ExtractComponent<3, 1, 2, 1, 2>(); } 
template <spv::StorageClass C1> void YZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 1, 2>(_var);}
void YZYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZYZ, put = YZYZ)) TExtractType<4> yzy;
__declspec(property(get = YZYZ, put = YZYZ)) TExtractType<4> gbg;
TExtractType<4> YZYW() { return ExtractComponent<3, 1, 2, 1, 3>(); } 
template <spv::StorageClass C1> void YZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 1, 3>(_var);}
void YZYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZYW, put = YZYW)) TExtractType<4> yzy;
__declspec(property(get = YZYW, put = YZYW)) TExtractType<4> gbg;
TExtractType<3> YZZ() { return ExtractComponent<3, 1, 2, 2>(); } 
template <spv::StorageClass C1> void YZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 2>(_var);}
void YZZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZ, put = YZZ)) TExtractType<3> yzz;
__declspec(property(get = YZZ, put = YZZ)) TExtractType<3> gbb;
TExtractType<4> YZZX() { return ExtractComponent<3, 1, 2, 2, 0>(); } 
template <spv::StorageClass C1> void YZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 2, 0>(_var);}
void YZZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZX, put = YZZX)) TExtractType<4> yzz;
__declspec(property(get = YZZX, put = YZZX)) TExtractType<4> gbb;
TExtractType<4> YZZY() { return ExtractComponent<3, 1, 2, 2, 1>(); } 
template <spv::StorageClass C1> void YZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 2, 1>(_var);}
void YZZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZY, put = YZZY)) TExtractType<4> yzz;
__declspec(property(get = YZZY, put = YZZY)) TExtractType<4> gbb;
TExtractType<4> YZZZ() { return ExtractComponent<3, 1, 2, 2, 2>(); } 
template <spv::StorageClass C1> void YZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 2, 2>(_var);}
void YZZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZZ, put = YZZZ)) TExtractType<4> yzz;
__declspec(property(get = YZZZ, put = YZZZ)) TExtractType<4> gbb;
TExtractType<4> YZZW() { return ExtractComponent<3, 1, 2, 2, 3>(); } 
template <spv::StorageClass C1> void YZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 2, 3>(_var);}
void YZZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZW, put = YZZW)) TExtractType<4> yzz;
__declspec(property(get = YZZW, put = YZZW)) TExtractType<4> gbb;
TExtractType<3> YZW() { return ExtractComponent<3, 1, 2, 3>(); } 
template <spv::StorageClass C1> void YZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 3>(_var);}
void YZW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZW, put = YZW)) TExtractType<3> yzw;
__declspec(property(get = YZW, put = YZW)) TExtractType<3> gba;
TExtractType<4> YZWX() { return ExtractComponent<3, 1, 2, 3, 0>(); } 
template <spv::StorageClass C1> void YZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 3, 0>(_var);}
void YZWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZWX, put = YZWX)) TExtractType<4> yzw;
__declspec(property(get = YZWX, put = YZWX)) TExtractType<4> gba;
TExtractType<4> YZWY() { return ExtractComponent<3, 1, 2, 3, 1>(); } 
template <spv::StorageClass C1> void YZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 3, 1>(_var);}
void YZWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZWY, put = YZWY)) TExtractType<4> yzw;
__declspec(property(get = YZWY, put = YZWY)) TExtractType<4> gba;
TExtractType<4> YZWZ() { return ExtractComponent<3, 1, 2, 3, 2>(); } 
template <spv::StorageClass C1> void YZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 3, 2>(_var);}
void YZWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZWZ, put = YZWZ)) TExtractType<4> yzw;
__declspec(property(get = YZWZ, put = YZWZ)) TExtractType<4> gba;
TExtractType<4> YZWW() { return ExtractComponent<3, 1, 2, 3, 3>(); } 
template <spv::StorageClass C1> void YZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 3, 3>(_var);}
void YZWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZWW, put = YZWW)) TExtractType<4> yzw;
__declspec(property(get = YZWW, put = YZWW)) TExtractType<4> gba;
TExtractType<2> YW() { return ExtractComponent<2, 1, 3>(); } 
template <spv::StorageClass C1> void YW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 1, 3>(_var);}
void YW(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YW, put = YW)) TExtractType<2> yw;
__declspec(property(get = YW, put = YW)) TExtractType<2> ga;
TExtractType<3> YWX() { return ExtractComponent<3, 1, 3, 0>(); } 
template <spv::StorageClass C1> void YWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 0>(_var);}
void YWX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWX, put = YWX)) TExtractType<3> ywx;
__declspec(property(get = YWX, put = YWX)) TExtractType<3> gar;
TExtractType<4> YWXX() { return ExtractComponent<3, 1, 3, 0, 0>(); } 
template <spv::StorageClass C1> void YWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 0, 0>(_var);}
void YWXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWXX, put = YWXX)) TExtractType<4> ywx;
__declspec(property(get = YWXX, put = YWXX)) TExtractType<4> gar;
TExtractType<4> YWXY() { return ExtractComponent<3, 1, 3, 0, 1>(); } 
template <spv::StorageClass C1> void YWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 0, 1>(_var);}
void YWXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWXY, put = YWXY)) TExtractType<4> ywx;
__declspec(property(get = YWXY, put = YWXY)) TExtractType<4> gar;
TExtractType<4> YWXZ() { return ExtractComponent<3, 1, 3, 0, 2>(); } 
template <spv::StorageClass C1> void YWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 0, 2>(_var);}
void YWXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWXZ, put = YWXZ)) TExtractType<4> ywx;
__declspec(property(get = YWXZ, put = YWXZ)) TExtractType<4> gar;
TExtractType<4> YWXW() { return ExtractComponent<3, 1, 3, 0, 3>(); } 
template <spv::StorageClass C1> void YWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 0, 3>(_var);}
void YWXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWXW, put = YWXW)) TExtractType<4> ywx;
__declspec(property(get = YWXW, put = YWXW)) TExtractType<4> gar;
TExtractType<3> YWY() { return ExtractComponent<3, 1, 3, 1>(); } 
template <spv::StorageClass C1> void YWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 1>(_var);}
void YWY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWY, put = YWY)) TExtractType<3> ywy;
__declspec(property(get = YWY, put = YWY)) TExtractType<3> gag;
TExtractType<4> YWYX() { return ExtractComponent<3, 1, 3, 1, 0>(); } 
template <spv::StorageClass C1> void YWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 1, 0>(_var);}
void YWYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWYX, put = YWYX)) TExtractType<4> ywy;
__declspec(property(get = YWYX, put = YWYX)) TExtractType<4> gag;
TExtractType<4> YWYY() { return ExtractComponent<3, 1, 3, 1, 1>(); } 
template <spv::StorageClass C1> void YWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 1, 1>(_var);}
void YWYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWYY, put = YWYY)) TExtractType<4> ywy;
__declspec(property(get = YWYY, put = YWYY)) TExtractType<4> gag;
TExtractType<4> YWYZ() { return ExtractComponent<3, 1, 3, 1, 2>(); } 
template <spv::StorageClass C1> void YWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 1, 2>(_var);}
void YWYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWYZ, put = YWYZ)) TExtractType<4> ywy;
__declspec(property(get = YWYZ, put = YWYZ)) TExtractType<4> gag;
TExtractType<4> YWYW() { return ExtractComponent<3, 1, 3, 1, 3>(); } 
template <spv::StorageClass C1> void YWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 1, 3>(_var);}
void YWYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWYW, put = YWYW)) TExtractType<4> ywy;
__declspec(property(get = YWYW, put = YWYW)) TExtractType<4> gag;
TExtractType<3> YWZ() { return ExtractComponent<3, 1, 3, 2>(); } 
template <spv::StorageClass C1> void YWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 2>(_var);}
void YWZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZ, put = YWZ)) TExtractType<3> ywz;
__declspec(property(get = YWZ, put = YWZ)) TExtractType<3> gab;
TExtractType<4> YWZX() { return ExtractComponent<3, 1, 3, 2, 0>(); } 
template <spv::StorageClass C1> void YWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 2, 0>(_var);}
void YWZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZX, put = YWZX)) TExtractType<4> ywz;
__declspec(property(get = YWZX, put = YWZX)) TExtractType<4> gab;
TExtractType<4> YWZY() { return ExtractComponent<3, 1, 3, 2, 1>(); } 
template <spv::StorageClass C1> void YWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 2, 1>(_var);}
void YWZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZY, put = YWZY)) TExtractType<4> ywz;
__declspec(property(get = YWZY, put = YWZY)) TExtractType<4> gab;
TExtractType<4> YWZZ() { return ExtractComponent<3, 1, 3, 2, 2>(); } 
template <spv::StorageClass C1> void YWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 2, 2>(_var);}
void YWZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZZ, put = YWZZ)) TExtractType<4> ywz;
__declspec(property(get = YWZZ, put = YWZZ)) TExtractType<4> gab;
TExtractType<4> YWZW() { return ExtractComponent<3, 1, 3, 2, 3>(); } 
template <spv::StorageClass C1> void YWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 2, 3>(_var);}
void YWZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZW, put = YWZW)) TExtractType<4> ywz;
__declspec(property(get = YWZW, put = YWZW)) TExtractType<4> gab;
TExtractType<3> YWW() { return ExtractComponent<3, 1, 3, 3>(); } 
template <spv::StorageClass C1> void YWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 3>(_var);}
void YWW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWW, put = YWW)) TExtractType<3> yww;
__declspec(property(get = YWW, put = YWW)) TExtractType<3> gaa;
TExtractType<4> YWWX() { return ExtractComponent<3, 1, 3, 3, 0>(); } 
template <spv::StorageClass C1> void YWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 3, 0>(_var);}
void YWWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWWX, put = YWWX)) TExtractType<4> yww;
__declspec(property(get = YWWX, put = YWWX)) TExtractType<4> gaa;
TExtractType<4> YWWY() { return ExtractComponent<3, 1, 3, 3, 1>(); } 
template <spv::StorageClass C1> void YWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 3, 1>(_var);}
void YWWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWWY, put = YWWY)) TExtractType<4> yww;
__declspec(property(get = YWWY, put = YWWY)) TExtractType<4> gaa;
TExtractType<4> YWWZ() { return ExtractComponent<3, 1, 3, 3, 2>(); } 
template <spv::StorageClass C1> void YWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 3, 2>(_var);}
void YWWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWWZ, put = YWWZ)) TExtractType<4> yww;
__declspec(property(get = YWWZ, put = YWWZ)) TExtractType<4> gaa;
TExtractType<4> YWWW() { return ExtractComponent<3, 1, 3, 3, 3>(); } 
template <spv::StorageClass C1> void YWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 3, 3>(_var);}
void YWWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWWW, put = YWWW)) TExtractType<4> yww;
__declspec(property(get = YWWW, put = YWWW)) TExtractType<4> gaa;
TExtractType<1> Z() { return ExtractComponent<1, 2>(); } 
template <spv::StorageClass C1> void Z(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) { InsertComponent<1, 2>(_var);}
void Z(const vec_type_t<base_type_t<T>, 1>& _var) { InsertComponent<1, 2>(var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = Z, put = Z)) TExtractType<1> z;
__declspec(property(get = Z, put = Z)) TExtractType<1> b;
TExtractType<2> ZX() { return ExtractComponent<2, 2, 0>(); } 
template <spv::StorageClass C1> void ZX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 2, 0>(_var);}
void ZX(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZX, put = ZX)) TExtractType<2> zx;
__declspec(property(get = ZX, put = ZX)) TExtractType<2> br;
TExtractType<3> ZXX() { return ExtractComponent<3, 2, 0, 0>(); } 
template <spv::StorageClass C1> void ZXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 0>(_var);}
void ZXX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXX, put = ZXX)) TExtractType<3> zxx;
__declspec(property(get = ZXX, put = ZXX)) TExtractType<3> brr;
TExtractType<4> ZXXX() { return ExtractComponent<3, 2, 0, 0, 0>(); } 
template <spv::StorageClass C1> void ZXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 0, 0>(_var);}
void ZXXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXXX, put = ZXXX)) TExtractType<4> zxx;
__declspec(property(get = ZXXX, put = ZXXX)) TExtractType<4> brr;
TExtractType<4> ZXXY() { return ExtractComponent<3, 2, 0, 0, 1>(); } 
template <spv::StorageClass C1> void ZXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 0, 1>(_var);}
void ZXXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXXY, put = ZXXY)) TExtractType<4> zxx;
__declspec(property(get = ZXXY, put = ZXXY)) TExtractType<4> brr;
TExtractType<4> ZXXZ() { return ExtractComponent<3, 2, 0, 0, 2>(); } 
template <spv::StorageClass C1> void ZXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 0, 2>(_var);}
void ZXXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXXZ, put = ZXXZ)) TExtractType<4> zxx;
__declspec(property(get = ZXXZ, put = ZXXZ)) TExtractType<4> brr;
TExtractType<4> ZXXW() { return ExtractComponent<3, 2, 0, 0, 3>(); } 
template <spv::StorageClass C1> void ZXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 0, 3>(_var);}
void ZXXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXXW, put = ZXXW)) TExtractType<4> zxx;
__declspec(property(get = ZXXW, put = ZXXW)) TExtractType<4> brr;
TExtractType<3> ZXY() { return ExtractComponent<3, 2, 0, 1>(); } 
template <spv::StorageClass C1> void ZXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 1>(_var);}
void ZXY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXY, put = ZXY)) TExtractType<3> zxy;
__declspec(property(get = ZXY, put = ZXY)) TExtractType<3> brg;
TExtractType<4> ZXYX() { return ExtractComponent<3, 2, 0, 1, 0>(); } 
template <spv::StorageClass C1> void ZXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 1, 0>(_var);}
void ZXYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXYX, put = ZXYX)) TExtractType<4> zxy;
__declspec(property(get = ZXYX, put = ZXYX)) TExtractType<4> brg;
TExtractType<4> ZXYY() { return ExtractComponent<3, 2, 0, 1, 1>(); } 
template <spv::StorageClass C1> void ZXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 1, 1>(_var);}
void ZXYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXYY, put = ZXYY)) TExtractType<4> zxy;
__declspec(property(get = ZXYY, put = ZXYY)) TExtractType<4> brg;
TExtractType<4> ZXYZ() { return ExtractComponent<3, 2, 0, 1, 2>(); } 
template <spv::StorageClass C1> void ZXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 1, 2>(_var);}
void ZXYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXYZ, put = ZXYZ)) TExtractType<4> zxy;
__declspec(property(get = ZXYZ, put = ZXYZ)) TExtractType<4> brg;
TExtractType<4> ZXYW() { return ExtractComponent<3, 2, 0, 1, 3>(); } 
template <spv::StorageClass C1> void ZXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 1, 3>(_var);}
void ZXYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXYW, put = ZXYW)) TExtractType<4> zxy;
__declspec(property(get = ZXYW, put = ZXYW)) TExtractType<4> brg;
TExtractType<3> ZXZ() { return ExtractComponent<3, 2, 0, 2>(); } 
template <spv::StorageClass C1> void ZXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 2>(_var);}
void ZXZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZ, put = ZXZ)) TExtractType<3> zxz;
__declspec(property(get = ZXZ, put = ZXZ)) TExtractType<3> brb;
TExtractType<4> ZXZX() { return ExtractComponent<3, 2, 0, 2, 0>(); } 
template <spv::StorageClass C1> void ZXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 2, 0>(_var);}
void ZXZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZX, put = ZXZX)) TExtractType<4> zxz;
__declspec(property(get = ZXZX, put = ZXZX)) TExtractType<4> brb;
TExtractType<4> ZXZY() { return ExtractComponent<3, 2, 0, 2, 1>(); } 
template <spv::StorageClass C1> void ZXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 2, 1>(_var);}
void ZXZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZY, put = ZXZY)) TExtractType<4> zxz;
__declspec(property(get = ZXZY, put = ZXZY)) TExtractType<4> brb;
TExtractType<4> ZXZZ() { return ExtractComponent<3, 2, 0, 2, 2>(); } 
template <spv::StorageClass C1> void ZXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 2, 2>(_var);}
void ZXZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZZ, put = ZXZZ)) TExtractType<4> zxz;
__declspec(property(get = ZXZZ, put = ZXZZ)) TExtractType<4> brb;
TExtractType<4> ZXZW() { return ExtractComponent<3, 2, 0, 2, 3>(); } 
template <spv::StorageClass C1> void ZXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 2, 3>(_var);}
void ZXZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZW, put = ZXZW)) TExtractType<4> zxz;
__declspec(property(get = ZXZW, put = ZXZW)) TExtractType<4> brb;
TExtractType<3> ZXW() { return ExtractComponent<3, 2, 0, 3>(); } 
template <spv::StorageClass C1> void ZXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 3>(_var);}
void ZXW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXW, put = ZXW)) TExtractType<3> zxw;
__declspec(property(get = ZXW, put = ZXW)) TExtractType<3> bra;
TExtractType<4> ZXWX() { return ExtractComponent<3, 2, 0, 3, 0>(); } 
template <spv::StorageClass C1> void ZXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 3, 0>(_var);}
void ZXWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXWX, put = ZXWX)) TExtractType<4> zxw;
__declspec(property(get = ZXWX, put = ZXWX)) TExtractType<4> bra;
TExtractType<4> ZXWY() { return ExtractComponent<3, 2, 0, 3, 1>(); } 
template <spv::StorageClass C1> void ZXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 3, 1>(_var);}
void ZXWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXWY, put = ZXWY)) TExtractType<4> zxw;
__declspec(property(get = ZXWY, put = ZXWY)) TExtractType<4> bra;
TExtractType<4> ZXWZ() { return ExtractComponent<3, 2, 0, 3, 2>(); } 
template <spv::StorageClass C1> void ZXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 3, 2>(_var);}
void ZXWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXWZ, put = ZXWZ)) TExtractType<4> zxw;
__declspec(property(get = ZXWZ, put = ZXWZ)) TExtractType<4> bra;
TExtractType<4> ZXWW() { return ExtractComponent<3, 2, 0, 3, 3>(); } 
template <spv::StorageClass C1> void ZXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 3, 3>(_var);}
void ZXWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXWW, put = ZXWW)) TExtractType<4> zxw;
__declspec(property(get = ZXWW, put = ZXWW)) TExtractType<4> bra;
TExtractType<2> ZY() { return ExtractComponent<2, 2, 1>(); } 
template <spv::StorageClass C1> void ZY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 2, 1>(_var);}
void ZY(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZY, put = ZY)) TExtractType<2> zy;
__declspec(property(get = ZY, put = ZY)) TExtractType<2> bg;
TExtractType<3> ZYX() { return ExtractComponent<3, 2, 1, 0>(); } 
template <spv::StorageClass C1> void ZYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 0>(_var);}
void ZYX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYX, put = ZYX)) TExtractType<3> zyx;
__declspec(property(get = ZYX, put = ZYX)) TExtractType<3> bgr;
TExtractType<4> ZYXX() { return ExtractComponent<3, 2, 1, 0, 0>(); } 
template <spv::StorageClass C1> void ZYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 0, 0>(_var);}
void ZYXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYXX, put = ZYXX)) TExtractType<4> zyx;
__declspec(property(get = ZYXX, put = ZYXX)) TExtractType<4> bgr;
TExtractType<4> ZYXY() { return ExtractComponent<3, 2, 1, 0, 1>(); } 
template <spv::StorageClass C1> void ZYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 0, 1>(_var);}
void ZYXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYXY, put = ZYXY)) TExtractType<4> zyx;
__declspec(property(get = ZYXY, put = ZYXY)) TExtractType<4> bgr;
TExtractType<4> ZYXZ() { return ExtractComponent<3, 2, 1, 0, 2>(); } 
template <spv::StorageClass C1> void ZYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 0, 2>(_var);}
void ZYXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYXZ, put = ZYXZ)) TExtractType<4> zyx;
__declspec(property(get = ZYXZ, put = ZYXZ)) TExtractType<4> bgr;
TExtractType<4> ZYXW() { return ExtractComponent<3, 2, 1, 0, 3>(); } 
template <spv::StorageClass C1> void ZYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 0, 3>(_var);}
void ZYXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYXW, put = ZYXW)) TExtractType<4> zyx;
__declspec(property(get = ZYXW, put = ZYXW)) TExtractType<4> bgr;
TExtractType<3> ZYY() { return ExtractComponent<3, 2, 1, 1>(); } 
template <spv::StorageClass C1> void ZYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 1>(_var);}
void ZYY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYY, put = ZYY)) TExtractType<3> zyy;
__declspec(property(get = ZYY, put = ZYY)) TExtractType<3> bgg;
TExtractType<4> ZYYX() { return ExtractComponent<3, 2, 1, 1, 0>(); } 
template <spv::StorageClass C1> void ZYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 1, 0>(_var);}
void ZYYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYYX, put = ZYYX)) TExtractType<4> zyy;
__declspec(property(get = ZYYX, put = ZYYX)) TExtractType<4> bgg;
TExtractType<4> ZYYY() { return ExtractComponent<3, 2, 1, 1, 1>(); } 
template <spv::StorageClass C1> void ZYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 1, 1>(_var);}
void ZYYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYYY, put = ZYYY)) TExtractType<4> zyy;
__declspec(property(get = ZYYY, put = ZYYY)) TExtractType<4> bgg;
TExtractType<4> ZYYZ() { return ExtractComponent<3, 2, 1, 1, 2>(); } 
template <spv::StorageClass C1> void ZYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 1, 2>(_var);}
void ZYYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYYZ, put = ZYYZ)) TExtractType<4> zyy;
__declspec(property(get = ZYYZ, put = ZYYZ)) TExtractType<4> bgg;
TExtractType<4> ZYYW() { return ExtractComponent<3, 2, 1, 1, 3>(); } 
template <spv::StorageClass C1> void ZYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 1, 3>(_var);}
void ZYYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYYW, put = ZYYW)) TExtractType<4> zyy;
__declspec(property(get = ZYYW, put = ZYYW)) TExtractType<4> bgg;
TExtractType<3> ZYZ() { return ExtractComponent<3, 2, 1, 2>(); } 
template <spv::StorageClass C1> void ZYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 2>(_var);}
void ZYZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZ, put = ZYZ)) TExtractType<3> zyz;
__declspec(property(get = ZYZ, put = ZYZ)) TExtractType<3> bgb;
TExtractType<4> ZYZX() { return ExtractComponent<3, 2, 1, 2, 0>(); } 
template <spv::StorageClass C1> void ZYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 2, 0>(_var);}
void ZYZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZX, put = ZYZX)) TExtractType<4> zyz;
__declspec(property(get = ZYZX, put = ZYZX)) TExtractType<4> bgb;
TExtractType<4> ZYZY() { return ExtractComponent<3, 2, 1, 2, 1>(); } 
template <spv::StorageClass C1> void ZYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 2, 1>(_var);}
void ZYZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZY, put = ZYZY)) TExtractType<4> zyz;
__declspec(property(get = ZYZY, put = ZYZY)) TExtractType<4> bgb;
TExtractType<4> ZYZZ() { return ExtractComponent<3, 2, 1, 2, 2>(); } 
template <spv::StorageClass C1> void ZYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 2, 2>(_var);}
void ZYZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZZ, put = ZYZZ)) TExtractType<4> zyz;
__declspec(property(get = ZYZZ, put = ZYZZ)) TExtractType<4> bgb;
TExtractType<4> ZYZW() { return ExtractComponent<3, 2, 1, 2, 3>(); } 
template <spv::StorageClass C1> void ZYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 2, 3>(_var);}
void ZYZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZW, put = ZYZW)) TExtractType<4> zyz;
__declspec(property(get = ZYZW, put = ZYZW)) TExtractType<4> bgb;
TExtractType<3> ZYW() { return ExtractComponent<3, 2, 1, 3>(); } 
template <spv::StorageClass C1> void ZYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 3>(_var);}
void ZYW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYW, put = ZYW)) TExtractType<3> zyw;
__declspec(property(get = ZYW, put = ZYW)) TExtractType<3> bga;
TExtractType<4> ZYWX() { return ExtractComponent<3, 2, 1, 3, 0>(); } 
template <spv::StorageClass C1> void ZYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 3, 0>(_var);}
void ZYWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYWX, put = ZYWX)) TExtractType<4> zyw;
__declspec(property(get = ZYWX, put = ZYWX)) TExtractType<4> bga;
TExtractType<4> ZYWY() { return ExtractComponent<3, 2, 1, 3, 1>(); } 
template <spv::StorageClass C1> void ZYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 3, 1>(_var);}
void ZYWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYWY, put = ZYWY)) TExtractType<4> zyw;
__declspec(property(get = ZYWY, put = ZYWY)) TExtractType<4> bga;
TExtractType<4> ZYWZ() { return ExtractComponent<3, 2, 1, 3, 2>(); } 
template <spv::StorageClass C1> void ZYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 3, 2>(_var);}
void ZYWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYWZ, put = ZYWZ)) TExtractType<4> zyw;
__declspec(property(get = ZYWZ, put = ZYWZ)) TExtractType<4> bga;
TExtractType<4> ZYWW() { return ExtractComponent<3, 2, 1, 3, 3>(); } 
template <spv::StorageClass C1> void ZYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 3, 3>(_var);}
void ZYWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYWW, put = ZYWW)) TExtractType<4> zyw;
__declspec(property(get = ZYWW, put = ZYWW)) TExtractType<4> bga;
TExtractType<2> ZZ() { return ExtractComponent<2, 2, 2>(); } 
template <spv::StorageClass C1> void ZZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 2, 2>(_var);}
void ZZ(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZ, put = ZZ)) TExtractType<2> zz;
__declspec(property(get = ZZ, put = ZZ)) TExtractType<2> bb;
TExtractType<3> ZZX() { return ExtractComponent<3, 2, 2, 0>(); } 
template <spv::StorageClass C1> void ZZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 0>(_var);}
void ZZX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZX, put = ZZX)) TExtractType<3> zzx;
__declspec(property(get = ZZX, put = ZZX)) TExtractType<3> bbr;
TExtractType<4> ZZXX() { return ExtractComponent<3, 2, 2, 0, 0>(); } 
template <spv::StorageClass C1> void ZZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 0, 0>(_var);}
void ZZXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZXX, put = ZZXX)) TExtractType<4> zzx;
__declspec(property(get = ZZXX, put = ZZXX)) TExtractType<4> bbr;
TExtractType<4> ZZXY() { return ExtractComponent<3, 2, 2, 0, 1>(); } 
template <spv::StorageClass C1> void ZZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 0, 1>(_var);}
void ZZXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZXY, put = ZZXY)) TExtractType<4> zzx;
__declspec(property(get = ZZXY, put = ZZXY)) TExtractType<4> bbr;
TExtractType<4> ZZXZ() { return ExtractComponent<3, 2, 2, 0, 2>(); } 
template <spv::StorageClass C1> void ZZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 0, 2>(_var);}
void ZZXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZXZ, put = ZZXZ)) TExtractType<4> zzx;
__declspec(property(get = ZZXZ, put = ZZXZ)) TExtractType<4> bbr;
TExtractType<4> ZZXW() { return ExtractComponent<3, 2, 2, 0, 3>(); } 
template <spv::StorageClass C1> void ZZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 0, 3>(_var);}
void ZZXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZXW, put = ZZXW)) TExtractType<4> zzx;
__declspec(property(get = ZZXW, put = ZZXW)) TExtractType<4> bbr;
TExtractType<3> ZZY() { return ExtractComponent<3, 2, 2, 1>(); } 
template <spv::StorageClass C1> void ZZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 1>(_var);}
void ZZY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZY, put = ZZY)) TExtractType<3> zzy;
__declspec(property(get = ZZY, put = ZZY)) TExtractType<3> bbg;
TExtractType<4> ZZYX() { return ExtractComponent<3, 2, 2, 1, 0>(); } 
template <spv::StorageClass C1> void ZZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 1, 0>(_var);}
void ZZYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZYX, put = ZZYX)) TExtractType<4> zzy;
__declspec(property(get = ZZYX, put = ZZYX)) TExtractType<4> bbg;
TExtractType<4> ZZYY() { return ExtractComponent<3, 2, 2, 1, 1>(); } 
template <spv::StorageClass C1> void ZZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 1, 1>(_var);}
void ZZYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZYY, put = ZZYY)) TExtractType<4> zzy;
__declspec(property(get = ZZYY, put = ZZYY)) TExtractType<4> bbg;
TExtractType<4> ZZYZ() { return ExtractComponent<3, 2, 2, 1, 2>(); } 
template <spv::StorageClass C1> void ZZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 1, 2>(_var);}
void ZZYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZYZ, put = ZZYZ)) TExtractType<4> zzy;
__declspec(property(get = ZZYZ, put = ZZYZ)) TExtractType<4> bbg;
TExtractType<4> ZZYW() { return ExtractComponent<3, 2, 2, 1, 3>(); } 
template <spv::StorageClass C1> void ZZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 1, 3>(_var);}
void ZZYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZYW, put = ZZYW)) TExtractType<4> zzy;
__declspec(property(get = ZZYW, put = ZZYW)) TExtractType<4> bbg;
TExtractType<3> ZZZ() { return ExtractComponent<3, 2, 2, 2>(); } 
template <spv::StorageClass C1> void ZZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 2>(_var);}
void ZZZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZ, put = ZZZ)) TExtractType<3> zzz;
__declspec(property(get = ZZZ, put = ZZZ)) TExtractType<3> bbb;
TExtractType<4> ZZZX() { return ExtractComponent<3, 2, 2, 2, 0>(); } 
template <spv::StorageClass C1> void ZZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 2, 0>(_var);}
void ZZZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZX, put = ZZZX)) TExtractType<4> zzz;
__declspec(property(get = ZZZX, put = ZZZX)) TExtractType<4> bbb;
TExtractType<4> ZZZY() { return ExtractComponent<3, 2, 2, 2, 1>(); } 
template <spv::StorageClass C1> void ZZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 2, 1>(_var);}
void ZZZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZY, put = ZZZY)) TExtractType<4> zzz;
__declspec(property(get = ZZZY, put = ZZZY)) TExtractType<4> bbb;
TExtractType<4> ZZZZ() { return ExtractComponent<3, 2, 2, 2, 2>(); } 
template <spv::StorageClass C1> void ZZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 2, 2>(_var);}
void ZZZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZZ, put = ZZZZ)) TExtractType<4> zzz;
__declspec(property(get = ZZZZ, put = ZZZZ)) TExtractType<4> bbb;
TExtractType<4> ZZZW() { return ExtractComponent<3, 2, 2, 2, 3>(); } 
template <spv::StorageClass C1> void ZZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 2, 3>(_var);}
void ZZZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZW, put = ZZZW)) TExtractType<4> zzz;
__declspec(property(get = ZZZW, put = ZZZW)) TExtractType<4> bbb;
TExtractType<3> ZZW() { return ExtractComponent<3, 2, 2, 3>(); } 
template <spv::StorageClass C1> void ZZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 3>(_var);}
void ZZW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZW, put = ZZW)) TExtractType<3> zzw;
__declspec(property(get = ZZW, put = ZZW)) TExtractType<3> bba;
TExtractType<4> ZZWX() { return ExtractComponent<3, 2, 2, 3, 0>(); } 
template <spv::StorageClass C1> void ZZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 3, 0>(_var);}
void ZZWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZWX, put = ZZWX)) TExtractType<4> zzw;
__declspec(property(get = ZZWX, put = ZZWX)) TExtractType<4> bba;
TExtractType<4> ZZWY() { return ExtractComponent<3, 2, 2, 3, 1>(); } 
template <spv::StorageClass C1> void ZZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 3, 1>(_var);}
void ZZWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZWY, put = ZZWY)) TExtractType<4> zzw;
__declspec(property(get = ZZWY, put = ZZWY)) TExtractType<4> bba;
TExtractType<4> ZZWZ() { return ExtractComponent<3, 2, 2, 3, 2>(); } 
template <spv::StorageClass C1> void ZZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 3, 2>(_var);}
void ZZWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZWZ, put = ZZWZ)) TExtractType<4> zzw;
__declspec(property(get = ZZWZ, put = ZZWZ)) TExtractType<4> bba;
TExtractType<4> ZZWW() { return ExtractComponent<3, 2, 2, 3, 3>(); } 
template <spv::StorageClass C1> void ZZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 3, 3>(_var);}
void ZZWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZWW, put = ZZWW)) TExtractType<4> zzw;
__declspec(property(get = ZZWW, put = ZZWW)) TExtractType<4> bba;
TExtractType<2> ZW() { return ExtractComponent<2, 2, 3>(); } 
template <spv::StorageClass C1> void ZW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 2, 3>(_var);}
void ZW(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZW, put = ZW)) TExtractType<2> zw;
__declspec(property(get = ZW, put = ZW)) TExtractType<2> ba;
TExtractType<3> ZWX() { return ExtractComponent<3, 2, 3, 0>(); } 
template <spv::StorageClass C1> void ZWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 0>(_var);}
void ZWX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWX, put = ZWX)) TExtractType<3> zwx;
__declspec(property(get = ZWX, put = ZWX)) TExtractType<3> bar;
TExtractType<4> ZWXX() { return ExtractComponent<3, 2, 3, 0, 0>(); } 
template <spv::StorageClass C1> void ZWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 0, 0>(_var);}
void ZWXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWXX, put = ZWXX)) TExtractType<4> zwx;
__declspec(property(get = ZWXX, put = ZWXX)) TExtractType<4> bar;
TExtractType<4> ZWXY() { return ExtractComponent<3, 2, 3, 0, 1>(); } 
template <spv::StorageClass C1> void ZWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 0, 1>(_var);}
void ZWXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWXY, put = ZWXY)) TExtractType<4> zwx;
__declspec(property(get = ZWXY, put = ZWXY)) TExtractType<4> bar;
TExtractType<4> ZWXZ() { return ExtractComponent<3, 2, 3, 0, 2>(); } 
template <spv::StorageClass C1> void ZWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 0, 2>(_var);}
void ZWXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWXZ, put = ZWXZ)) TExtractType<4> zwx;
__declspec(property(get = ZWXZ, put = ZWXZ)) TExtractType<4> bar;
TExtractType<4> ZWXW() { return ExtractComponent<3, 2, 3, 0, 3>(); } 
template <spv::StorageClass C1> void ZWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 0, 3>(_var);}
void ZWXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWXW, put = ZWXW)) TExtractType<4> zwx;
__declspec(property(get = ZWXW, put = ZWXW)) TExtractType<4> bar;
TExtractType<3> ZWY() { return ExtractComponent<3, 2, 3, 1>(); } 
template <spv::StorageClass C1> void ZWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 1>(_var);}
void ZWY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWY, put = ZWY)) TExtractType<3> zwy;
__declspec(property(get = ZWY, put = ZWY)) TExtractType<3> bag;
TExtractType<4> ZWYX() { return ExtractComponent<3, 2, 3, 1, 0>(); } 
template <spv::StorageClass C1> void ZWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 1, 0>(_var);}
void ZWYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWYX, put = ZWYX)) TExtractType<4> zwy;
__declspec(property(get = ZWYX, put = ZWYX)) TExtractType<4> bag;
TExtractType<4> ZWYY() { return ExtractComponent<3, 2, 3, 1, 1>(); } 
template <spv::StorageClass C1> void ZWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 1, 1>(_var);}
void ZWYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWYY, put = ZWYY)) TExtractType<4> zwy;
__declspec(property(get = ZWYY, put = ZWYY)) TExtractType<4> bag;
TExtractType<4> ZWYZ() { return ExtractComponent<3, 2, 3, 1, 2>(); } 
template <spv::StorageClass C1> void ZWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 1, 2>(_var);}
void ZWYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWYZ, put = ZWYZ)) TExtractType<4> zwy;
__declspec(property(get = ZWYZ, put = ZWYZ)) TExtractType<4> bag;
TExtractType<4> ZWYW() { return ExtractComponent<3, 2, 3, 1, 3>(); } 
template <spv::StorageClass C1> void ZWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 1, 3>(_var);}
void ZWYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWYW, put = ZWYW)) TExtractType<4> zwy;
__declspec(property(get = ZWYW, put = ZWYW)) TExtractType<4> bag;
TExtractType<3> ZWZ() { return ExtractComponent<3, 2, 3, 2>(); } 
template <spv::StorageClass C1> void ZWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 2>(_var);}
void ZWZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZ, put = ZWZ)) TExtractType<3> zwz;
__declspec(property(get = ZWZ, put = ZWZ)) TExtractType<3> bab;
TExtractType<4> ZWZX() { return ExtractComponent<3, 2, 3, 2, 0>(); } 
template <spv::StorageClass C1> void ZWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 2, 0>(_var);}
void ZWZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZX, put = ZWZX)) TExtractType<4> zwz;
__declspec(property(get = ZWZX, put = ZWZX)) TExtractType<4> bab;
TExtractType<4> ZWZY() { return ExtractComponent<3, 2, 3, 2, 1>(); } 
template <spv::StorageClass C1> void ZWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 2, 1>(_var);}
void ZWZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZY, put = ZWZY)) TExtractType<4> zwz;
__declspec(property(get = ZWZY, put = ZWZY)) TExtractType<4> bab;
TExtractType<4> ZWZZ() { return ExtractComponent<3, 2, 3, 2, 2>(); } 
template <spv::StorageClass C1> void ZWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 2, 2>(_var);}
void ZWZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZZ, put = ZWZZ)) TExtractType<4> zwz;
__declspec(property(get = ZWZZ, put = ZWZZ)) TExtractType<4> bab;
TExtractType<4> ZWZW() { return ExtractComponent<3, 2, 3, 2, 3>(); } 
template <spv::StorageClass C1> void ZWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 2, 3>(_var);}
void ZWZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZW, put = ZWZW)) TExtractType<4> zwz;
__declspec(property(get = ZWZW, put = ZWZW)) TExtractType<4> bab;
TExtractType<3> ZWW() { return ExtractComponent<3, 2, 3, 3>(); } 
template <spv::StorageClass C1> void ZWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 3>(_var);}
void ZWW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWW, put = ZWW)) TExtractType<3> zww;
__declspec(property(get = ZWW, put = ZWW)) TExtractType<3> baa;
TExtractType<4> ZWWX() { return ExtractComponent<3, 2, 3, 3, 0>(); } 
template <spv::StorageClass C1> void ZWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 3, 0>(_var);}
void ZWWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWWX, put = ZWWX)) TExtractType<4> zww;
__declspec(property(get = ZWWX, put = ZWWX)) TExtractType<4> baa;
TExtractType<4> ZWWY() { return ExtractComponent<3, 2, 3, 3, 1>(); } 
template <spv::StorageClass C1> void ZWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 3, 1>(_var);}
void ZWWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWWY, put = ZWWY)) TExtractType<4> zww;
__declspec(property(get = ZWWY, put = ZWWY)) TExtractType<4> baa;
TExtractType<4> ZWWZ() { return ExtractComponent<3, 2, 3, 3, 2>(); } 
template <spv::StorageClass C1> void ZWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 3, 2>(_var);}
void ZWWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWWZ, put = ZWWZ)) TExtractType<4> zww;
__declspec(property(get = ZWWZ, put = ZWWZ)) TExtractType<4> baa;
TExtractType<4> ZWWW() { return ExtractComponent<3, 2, 3, 3, 3>(); } 
template <spv::StorageClass C1> void ZWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 3, 3>(_var);}
void ZWWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWWW, put = ZWWW)) TExtractType<4> zww;
__declspec(property(get = ZWWW, put = ZWWW)) TExtractType<4> baa;
TExtractType<1> W() { return ExtractComponent<1, 3>(); } 
template <spv::StorageClass C1> void W(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) { InsertComponent<1, 3>(_var);}
void W(const vec_type_t<base_type_t<T>, 1>& _var) { InsertComponent<1, 3>(var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = W, put = W)) TExtractType<1> w;
__declspec(property(get = W, put = W)) TExtractType<1> a;
TExtractType<2> WX() { return ExtractComponent<2, 3, 0>(); } 
template <spv::StorageClass C1> void WX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 3, 0>(_var);}
void WX(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WX, put = WX)) TExtractType<2> wx;
__declspec(property(get = WX, put = WX)) TExtractType<2> ar;
TExtractType<3> WXX() { return ExtractComponent<3, 3, 0, 0>(); } 
template <spv::StorageClass C1> void WXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 0>(_var);}
void WXX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXX, put = WXX)) TExtractType<3> wxx;
__declspec(property(get = WXX, put = WXX)) TExtractType<3> arr;
TExtractType<4> WXXX() { return ExtractComponent<3, 3, 0, 0, 0>(); } 
template <spv::StorageClass C1> void WXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 0, 0>(_var);}
void WXXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXXX, put = WXXX)) TExtractType<4> wxx;
__declspec(property(get = WXXX, put = WXXX)) TExtractType<4> arr;
TExtractType<4> WXXY() { return ExtractComponent<3, 3, 0, 0, 1>(); } 
template <spv::StorageClass C1> void WXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 0, 1>(_var);}
void WXXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXXY, put = WXXY)) TExtractType<4> wxx;
__declspec(property(get = WXXY, put = WXXY)) TExtractType<4> arr;
TExtractType<4> WXXZ() { return ExtractComponent<3, 3, 0, 0, 2>(); } 
template <spv::StorageClass C1> void WXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 0, 2>(_var);}
void WXXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXXZ, put = WXXZ)) TExtractType<4> wxx;
__declspec(property(get = WXXZ, put = WXXZ)) TExtractType<4> arr;
TExtractType<4> WXXW() { return ExtractComponent<3, 3, 0, 0, 3>(); } 
template <spv::StorageClass C1> void WXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 0, 3>(_var);}
void WXXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXXW, put = WXXW)) TExtractType<4> wxx;
__declspec(property(get = WXXW, put = WXXW)) TExtractType<4> arr;
TExtractType<3> WXY() { return ExtractComponent<3, 3, 0, 1>(); } 
template <spv::StorageClass C1> void WXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 1>(_var);}
void WXY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXY, put = WXY)) TExtractType<3> wxy;
__declspec(property(get = WXY, put = WXY)) TExtractType<3> arg;
TExtractType<4> WXYX() { return ExtractComponent<3, 3, 0, 1, 0>(); } 
template <spv::StorageClass C1> void WXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 1, 0>(_var);}
void WXYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXYX, put = WXYX)) TExtractType<4> wxy;
__declspec(property(get = WXYX, put = WXYX)) TExtractType<4> arg;
TExtractType<4> WXYY() { return ExtractComponent<3, 3, 0, 1, 1>(); } 
template <spv::StorageClass C1> void WXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 1, 1>(_var);}
void WXYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXYY, put = WXYY)) TExtractType<4> wxy;
__declspec(property(get = WXYY, put = WXYY)) TExtractType<4> arg;
TExtractType<4> WXYZ() { return ExtractComponent<3, 3, 0, 1, 2>(); } 
template <spv::StorageClass C1> void WXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 1, 2>(_var);}
void WXYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXYZ, put = WXYZ)) TExtractType<4> wxy;
__declspec(property(get = WXYZ, put = WXYZ)) TExtractType<4> arg;
TExtractType<4> WXYW() { return ExtractComponent<3, 3, 0, 1, 3>(); } 
template <spv::StorageClass C1> void WXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 1, 3>(_var);}
void WXYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXYW, put = WXYW)) TExtractType<4> wxy;
__declspec(property(get = WXYW, put = WXYW)) TExtractType<4> arg;
TExtractType<3> WXZ() { return ExtractComponent<3, 3, 0, 2>(); } 
template <spv::StorageClass C1> void WXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 2>(_var);}
void WXZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZ, put = WXZ)) TExtractType<3> wxz;
__declspec(property(get = WXZ, put = WXZ)) TExtractType<3> arb;
TExtractType<4> WXZX() { return ExtractComponent<3, 3, 0, 2, 0>(); } 
template <spv::StorageClass C1> void WXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 2, 0>(_var);}
void WXZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZX, put = WXZX)) TExtractType<4> wxz;
__declspec(property(get = WXZX, put = WXZX)) TExtractType<4> arb;
TExtractType<4> WXZY() { return ExtractComponent<3, 3, 0, 2, 1>(); } 
template <spv::StorageClass C1> void WXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 2, 1>(_var);}
void WXZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZY, put = WXZY)) TExtractType<4> wxz;
__declspec(property(get = WXZY, put = WXZY)) TExtractType<4> arb;
TExtractType<4> WXZZ() { return ExtractComponent<3, 3, 0, 2, 2>(); } 
template <spv::StorageClass C1> void WXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 2, 2>(_var);}
void WXZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZZ, put = WXZZ)) TExtractType<4> wxz;
__declspec(property(get = WXZZ, put = WXZZ)) TExtractType<4> arb;
TExtractType<4> WXZW() { return ExtractComponent<3, 3, 0, 2, 3>(); } 
template <spv::StorageClass C1> void WXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 2, 3>(_var);}
void WXZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZW, put = WXZW)) TExtractType<4> wxz;
__declspec(property(get = WXZW, put = WXZW)) TExtractType<4> arb;
TExtractType<3> WXW() { return ExtractComponent<3, 3, 0, 3>(); } 
template <spv::StorageClass C1> void WXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 3>(_var);}
void WXW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXW, put = WXW)) TExtractType<3> wxw;
__declspec(property(get = WXW, put = WXW)) TExtractType<3> ara;
TExtractType<4> WXWX() { return ExtractComponent<3, 3, 0, 3, 0>(); } 
template <spv::StorageClass C1> void WXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 3, 0>(_var);}
void WXWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXWX, put = WXWX)) TExtractType<4> wxw;
__declspec(property(get = WXWX, put = WXWX)) TExtractType<4> ara;
TExtractType<4> WXWY() { return ExtractComponent<3, 3, 0, 3, 1>(); } 
template <spv::StorageClass C1> void WXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 3, 1>(_var);}
void WXWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXWY, put = WXWY)) TExtractType<4> wxw;
__declspec(property(get = WXWY, put = WXWY)) TExtractType<4> ara;
TExtractType<4> WXWZ() { return ExtractComponent<3, 3, 0, 3, 2>(); } 
template <spv::StorageClass C1> void WXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 3, 2>(_var);}
void WXWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXWZ, put = WXWZ)) TExtractType<4> wxw;
__declspec(property(get = WXWZ, put = WXWZ)) TExtractType<4> ara;
TExtractType<4> WXWW() { return ExtractComponent<3, 3, 0, 3, 3>(); } 
template <spv::StorageClass C1> void WXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 3, 3>(_var);}
void WXWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXWW, put = WXWW)) TExtractType<4> wxw;
__declspec(property(get = WXWW, put = WXWW)) TExtractType<4> ara;
TExtractType<2> WY() { return ExtractComponent<2, 3, 1>(); } 
template <spv::StorageClass C1> void WY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 3, 1>(_var);}
void WY(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WY, put = WY)) TExtractType<2> wy;
__declspec(property(get = WY, put = WY)) TExtractType<2> ag;
TExtractType<3> WYX() { return ExtractComponent<3, 3, 1, 0>(); } 
template <spv::StorageClass C1> void WYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 0>(_var);}
void WYX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYX, put = WYX)) TExtractType<3> wyx;
__declspec(property(get = WYX, put = WYX)) TExtractType<3> agr;
TExtractType<4> WYXX() { return ExtractComponent<3, 3, 1, 0, 0>(); } 
template <spv::StorageClass C1> void WYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 0, 0>(_var);}
void WYXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYXX, put = WYXX)) TExtractType<4> wyx;
__declspec(property(get = WYXX, put = WYXX)) TExtractType<4> agr;
TExtractType<4> WYXY() { return ExtractComponent<3, 3, 1, 0, 1>(); } 
template <spv::StorageClass C1> void WYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 0, 1>(_var);}
void WYXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYXY, put = WYXY)) TExtractType<4> wyx;
__declspec(property(get = WYXY, put = WYXY)) TExtractType<4> agr;
TExtractType<4> WYXZ() { return ExtractComponent<3, 3, 1, 0, 2>(); } 
template <spv::StorageClass C1> void WYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 0, 2>(_var);}
void WYXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYXZ, put = WYXZ)) TExtractType<4> wyx;
__declspec(property(get = WYXZ, put = WYXZ)) TExtractType<4> agr;
TExtractType<4> WYXW() { return ExtractComponent<3, 3, 1, 0, 3>(); } 
template <spv::StorageClass C1> void WYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 0, 3>(_var);}
void WYXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYXW, put = WYXW)) TExtractType<4> wyx;
__declspec(property(get = WYXW, put = WYXW)) TExtractType<4> agr;
TExtractType<3> WYY() { return ExtractComponent<3, 3, 1, 1>(); } 
template <spv::StorageClass C1> void WYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 1>(_var);}
void WYY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYY, put = WYY)) TExtractType<3> wyy;
__declspec(property(get = WYY, put = WYY)) TExtractType<3> agg;
TExtractType<4> WYYX() { return ExtractComponent<3, 3, 1, 1, 0>(); } 
template <spv::StorageClass C1> void WYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 1, 0>(_var);}
void WYYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYYX, put = WYYX)) TExtractType<4> wyy;
__declspec(property(get = WYYX, put = WYYX)) TExtractType<4> agg;
TExtractType<4> WYYY() { return ExtractComponent<3, 3, 1, 1, 1>(); } 
template <spv::StorageClass C1> void WYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 1, 1>(_var);}
void WYYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYYY, put = WYYY)) TExtractType<4> wyy;
__declspec(property(get = WYYY, put = WYYY)) TExtractType<4> agg;
TExtractType<4> WYYZ() { return ExtractComponent<3, 3, 1, 1, 2>(); } 
template <spv::StorageClass C1> void WYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 1, 2>(_var);}
void WYYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYYZ, put = WYYZ)) TExtractType<4> wyy;
__declspec(property(get = WYYZ, put = WYYZ)) TExtractType<4> agg;
TExtractType<4> WYYW() { return ExtractComponent<3, 3, 1, 1, 3>(); } 
template <spv::StorageClass C1> void WYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 1, 3>(_var);}
void WYYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYYW, put = WYYW)) TExtractType<4> wyy;
__declspec(property(get = WYYW, put = WYYW)) TExtractType<4> agg;
TExtractType<3> WYZ() { return ExtractComponent<3, 3, 1, 2>(); } 
template <spv::StorageClass C1> void WYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 2>(_var);}
void WYZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZ, put = WYZ)) TExtractType<3> wyz;
__declspec(property(get = WYZ, put = WYZ)) TExtractType<3> agb;
TExtractType<4> WYZX() { return ExtractComponent<3, 3, 1, 2, 0>(); } 
template <spv::StorageClass C1> void WYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 2, 0>(_var);}
void WYZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZX, put = WYZX)) TExtractType<4> wyz;
__declspec(property(get = WYZX, put = WYZX)) TExtractType<4> agb;
TExtractType<4> WYZY() { return ExtractComponent<3, 3, 1, 2, 1>(); } 
template <spv::StorageClass C1> void WYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 2, 1>(_var);}
void WYZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZY, put = WYZY)) TExtractType<4> wyz;
__declspec(property(get = WYZY, put = WYZY)) TExtractType<4> agb;
TExtractType<4> WYZZ() { return ExtractComponent<3, 3, 1, 2, 2>(); } 
template <spv::StorageClass C1> void WYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 2, 2>(_var);}
void WYZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZZ, put = WYZZ)) TExtractType<4> wyz;
__declspec(property(get = WYZZ, put = WYZZ)) TExtractType<4> agb;
TExtractType<4> WYZW() { return ExtractComponent<3, 3, 1, 2, 3>(); } 
template <spv::StorageClass C1> void WYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 2, 3>(_var);}
void WYZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZW, put = WYZW)) TExtractType<4> wyz;
__declspec(property(get = WYZW, put = WYZW)) TExtractType<4> agb;
TExtractType<3> WYW() { return ExtractComponent<3, 3, 1, 3>(); } 
template <spv::StorageClass C1> void WYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 3>(_var);}
void WYW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYW, put = WYW)) TExtractType<3> wyw;
__declspec(property(get = WYW, put = WYW)) TExtractType<3> aga;
TExtractType<4> WYWX() { return ExtractComponent<3, 3, 1, 3, 0>(); } 
template <spv::StorageClass C1> void WYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 3, 0>(_var);}
void WYWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYWX, put = WYWX)) TExtractType<4> wyw;
__declspec(property(get = WYWX, put = WYWX)) TExtractType<4> aga;
TExtractType<4> WYWY() { return ExtractComponent<3, 3, 1, 3, 1>(); } 
template <spv::StorageClass C1> void WYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 3, 1>(_var);}
void WYWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYWY, put = WYWY)) TExtractType<4> wyw;
__declspec(property(get = WYWY, put = WYWY)) TExtractType<4> aga;
TExtractType<4> WYWZ() { return ExtractComponent<3, 3, 1, 3, 2>(); } 
template <spv::StorageClass C1> void WYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 3, 2>(_var);}
void WYWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYWZ, put = WYWZ)) TExtractType<4> wyw;
__declspec(property(get = WYWZ, put = WYWZ)) TExtractType<4> aga;
TExtractType<4> WYWW() { return ExtractComponent<3, 3, 1, 3, 3>(); } 
template <spv::StorageClass C1> void WYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 3, 3>(_var);}
void WYWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYWW, put = WYWW)) TExtractType<4> wyw;
__declspec(property(get = WYWW, put = WYWW)) TExtractType<4> aga;
TExtractType<2> WZ() { return ExtractComponent<2, 3, 2>(); } 
template <spv::StorageClass C1> void WZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 3, 2>(_var);}
void WZ(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZ, put = WZ)) TExtractType<2> wz;
__declspec(property(get = WZ, put = WZ)) TExtractType<2> ab;
TExtractType<3> WZX() { return ExtractComponent<3, 3, 2, 0>(); } 
template <spv::StorageClass C1> void WZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 0>(_var);}
void WZX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZX, put = WZX)) TExtractType<3> wzx;
__declspec(property(get = WZX, put = WZX)) TExtractType<3> abr;
TExtractType<4> WZXX() { return ExtractComponent<3, 3, 2, 0, 0>(); } 
template <spv::StorageClass C1> void WZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 0, 0>(_var);}
void WZXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZXX, put = WZXX)) TExtractType<4> wzx;
__declspec(property(get = WZXX, put = WZXX)) TExtractType<4> abr;
TExtractType<4> WZXY() { return ExtractComponent<3, 3, 2, 0, 1>(); } 
template <spv::StorageClass C1> void WZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 0, 1>(_var);}
void WZXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZXY, put = WZXY)) TExtractType<4> wzx;
__declspec(property(get = WZXY, put = WZXY)) TExtractType<4> abr;
TExtractType<4> WZXZ() { return ExtractComponent<3, 3, 2, 0, 2>(); } 
template <spv::StorageClass C1> void WZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 0, 2>(_var);}
void WZXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZXZ, put = WZXZ)) TExtractType<4> wzx;
__declspec(property(get = WZXZ, put = WZXZ)) TExtractType<4> abr;
TExtractType<4> WZXW() { return ExtractComponent<3, 3, 2, 0, 3>(); } 
template <spv::StorageClass C1> void WZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 0, 3>(_var);}
void WZXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZXW, put = WZXW)) TExtractType<4> wzx;
__declspec(property(get = WZXW, put = WZXW)) TExtractType<4> abr;
TExtractType<3> WZY() { return ExtractComponent<3, 3, 2, 1>(); } 
template <spv::StorageClass C1> void WZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 1>(_var);}
void WZY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZY, put = WZY)) TExtractType<3> wzy;
__declspec(property(get = WZY, put = WZY)) TExtractType<3> abg;
TExtractType<4> WZYX() { return ExtractComponent<3, 3, 2, 1, 0>(); } 
template <spv::StorageClass C1> void WZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 1, 0>(_var);}
void WZYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZYX, put = WZYX)) TExtractType<4> wzy;
__declspec(property(get = WZYX, put = WZYX)) TExtractType<4> abg;
TExtractType<4> WZYY() { return ExtractComponent<3, 3, 2, 1, 1>(); } 
template <spv::StorageClass C1> void WZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 1, 1>(_var);}
void WZYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZYY, put = WZYY)) TExtractType<4> wzy;
__declspec(property(get = WZYY, put = WZYY)) TExtractType<4> abg;
TExtractType<4> WZYZ() { return ExtractComponent<3, 3, 2, 1, 2>(); } 
template <spv::StorageClass C1> void WZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 1, 2>(_var);}
void WZYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZYZ, put = WZYZ)) TExtractType<4> wzy;
__declspec(property(get = WZYZ, put = WZYZ)) TExtractType<4> abg;
TExtractType<4> WZYW() { return ExtractComponent<3, 3, 2, 1, 3>(); } 
template <spv::StorageClass C1> void WZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 1, 3>(_var);}
void WZYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZYW, put = WZYW)) TExtractType<4> wzy;
__declspec(property(get = WZYW, put = WZYW)) TExtractType<4> abg;
TExtractType<3> WZZ() { return ExtractComponent<3, 3, 2, 2>(); } 
template <spv::StorageClass C1> void WZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 2>(_var);}
void WZZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZ, put = WZZ)) TExtractType<3> wzz;
__declspec(property(get = WZZ, put = WZZ)) TExtractType<3> abb;
TExtractType<4> WZZX() { return ExtractComponent<3, 3, 2, 2, 0>(); } 
template <spv::StorageClass C1> void WZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 2, 0>(_var);}
void WZZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZX, put = WZZX)) TExtractType<4> wzz;
__declspec(property(get = WZZX, put = WZZX)) TExtractType<4> abb;
TExtractType<4> WZZY() { return ExtractComponent<3, 3, 2, 2, 1>(); } 
template <spv::StorageClass C1> void WZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 2, 1>(_var);}
void WZZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZY, put = WZZY)) TExtractType<4> wzz;
__declspec(property(get = WZZY, put = WZZY)) TExtractType<4> abb;
TExtractType<4> WZZZ() { return ExtractComponent<3, 3, 2, 2, 2>(); } 
template <spv::StorageClass C1> void WZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 2, 2>(_var);}
void WZZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZZ, put = WZZZ)) TExtractType<4> wzz;
__declspec(property(get = WZZZ, put = WZZZ)) TExtractType<4> abb;
TExtractType<4> WZZW() { return ExtractComponent<3, 3, 2, 2, 3>(); } 
template <spv::StorageClass C1> void WZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 2, 3>(_var);}
void WZZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZW, put = WZZW)) TExtractType<4> wzz;
__declspec(property(get = WZZW, put = WZZW)) TExtractType<4> abb;
TExtractType<3> WZW() { return ExtractComponent<3, 3, 2, 3>(); } 
template <spv::StorageClass C1> void WZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 3>(_var);}
void WZW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZW, put = WZW)) TExtractType<3> wzw;
__declspec(property(get = WZW, put = WZW)) TExtractType<3> aba;
TExtractType<4> WZWX() { return ExtractComponent<3, 3, 2, 3, 0>(); } 
template <spv::StorageClass C1> void WZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 3, 0>(_var);}
void WZWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZWX, put = WZWX)) TExtractType<4> wzw;
__declspec(property(get = WZWX, put = WZWX)) TExtractType<4> aba;
TExtractType<4> WZWY() { return ExtractComponent<3, 3, 2, 3, 1>(); } 
template <spv::StorageClass C1> void WZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 3, 1>(_var);}
void WZWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZWY, put = WZWY)) TExtractType<4> wzw;
__declspec(property(get = WZWY, put = WZWY)) TExtractType<4> aba;
TExtractType<4> WZWZ() { return ExtractComponent<3, 3, 2, 3, 2>(); } 
template <spv::StorageClass C1> void WZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 3, 2>(_var);}
void WZWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZWZ, put = WZWZ)) TExtractType<4> wzw;
__declspec(property(get = WZWZ, put = WZWZ)) TExtractType<4> aba;
TExtractType<4> WZWW() { return ExtractComponent<3, 3, 2, 3, 3>(); } 
template <spv::StorageClass C1> void WZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 3, 3>(_var);}
void WZWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZWW, put = WZWW)) TExtractType<4> wzw;
__declspec(property(get = WZWW, put = WZWW)) TExtractType<4> aba;
TExtractType<2> WW() { return ExtractComponent<2, 3, 3>(); } 
template <spv::StorageClass C1> void WW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 3, 3>(_var);}
void WW(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WW, put = WW)) TExtractType<2> ww;
__declspec(property(get = WW, put = WW)) TExtractType<2> aa;
TExtractType<3> WWX() { return ExtractComponent<3, 3, 3, 0>(); } 
template <spv::StorageClass C1> void WWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 0>(_var);}
void WWX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWX, put = WWX)) TExtractType<3> wwx;
__declspec(property(get = WWX, put = WWX)) TExtractType<3> aar;
TExtractType<4> WWXX() { return ExtractComponent<3, 3, 3, 0, 0>(); } 
template <spv::StorageClass C1> void WWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 0, 0>(_var);}
void WWXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWXX, put = WWXX)) TExtractType<4> wwx;
__declspec(property(get = WWXX, put = WWXX)) TExtractType<4> aar;
TExtractType<4> WWXY() { return ExtractComponent<3, 3, 3, 0, 1>(); } 
template <spv::StorageClass C1> void WWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 0, 1>(_var);}
void WWXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWXY, put = WWXY)) TExtractType<4> wwx;
__declspec(property(get = WWXY, put = WWXY)) TExtractType<4> aar;
TExtractType<4> WWXZ() { return ExtractComponent<3, 3, 3, 0, 2>(); } 
template <spv::StorageClass C1> void WWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 0, 2>(_var);}
void WWXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWXZ, put = WWXZ)) TExtractType<4> wwx;
__declspec(property(get = WWXZ, put = WWXZ)) TExtractType<4> aar;
TExtractType<4> WWXW() { return ExtractComponent<3, 3, 3, 0, 3>(); } 
template <spv::StorageClass C1> void WWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 0, 3>(_var);}
void WWXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWXW, put = WWXW)) TExtractType<4> wwx;
__declspec(property(get = WWXW, put = WWXW)) TExtractType<4> aar;
TExtractType<3> WWY() { return ExtractComponent<3, 3, 3, 1>(); } 
template <spv::StorageClass C1> void WWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 1>(_var);}
void WWY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWY, put = WWY)) TExtractType<3> wwy;
__declspec(property(get = WWY, put = WWY)) TExtractType<3> aag;
TExtractType<4> WWYX() { return ExtractComponent<3, 3, 3, 1, 0>(); } 
template <spv::StorageClass C1> void WWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 1, 0>(_var);}
void WWYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWYX, put = WWYX)) TExtractType<4> wwy;
__declspec(property(get = WWYX, put = WWYX)) TExtractType<4> aag;
TExtractType<4> WWYY() { return ExtractComponent<3, 3, 3, 1, 1>(); } 
template <spv::StorageClass C1> void WWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 1, 1>(_var);}
void WWYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWYY, put = WWYY)) TExtractType<4> wwy;
__declspec(property(get = WWYY, put = WWYY)) TExtractType<4> aag;
TExtractType<4> WWYZ() { return ExtractComponent<3, 3, 3, 1, 2>(); } 
template <spv::StorageClass C1> void WWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 1, 2>(_var);}
void WWYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWYZ, put = WWYZ)) TExtractType<4> wwy;
__declspec(property(get = WWYZ, put = WWYZ)) TExtractType<4> aag;
TExtractType<4> WWYW() { return ExtractComponent<3, 3, 3, 1, 3>(); } 
template <spv::StorageClass C1> void WWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 1, 3>(_var);}
void WWYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWYW, put = WWYW)) TExtractType<4> wwy;
__declspec(property(get = WWYW, put = WWYW)) TExtractType<4> aag;
TExtractType<3> WWZ() { return ExtractComponent<3, 3, 3, 2>(); } 
template <spv::StorageClass C1> void WWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 2>(_var);}
void WWZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZ, put = WWZ)) TExtractType<3> wwz;
__declspec(property(get = WWZ, put = WWZ)) TExtractType<3> aab;
TExtractType<4> WWZX() { return ExtractComponent<3, 3, 3, 2, 0>(); } 
template <spv::StorageClass C1> void WWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 2, 0>(_var);}
void WWZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZX, put = WWZX)) TExtractType<4> wwz;
__declspec(property(get = WWZX, put = WWZX)) TExtractType<4> aab;
TExtractType<4> WWZY() { return ExtractComponent<3, 3, 3, 2, 1>(); } 
template <spv::StorageClass C1> void WWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 2, 1>(_var);}
void WWZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZY, put = WWZY)) TExtractType<4> wwz;
__declspec(property(get = WWZY, put = WWZY)) TExtractType<4> aab;
TExtractType<4> WWZZ() { return ExtractComponent<3, 3, 3, 2, 2>(); } 
template <spv::StorageClass C1> void WWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 2, 2>(_var);}
void WWZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZZ, put = WWZZ)) TExtractType<4> wwz;
__declspec(property(get = WWZZ, put = WWZZ)) TExtractType<4> aab;
TExtractType<4> WWZW() { return ExtractComponent<3, 3, 3, 2, 3>(); } 
template <spv::StorageClass C1> void WWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 2, 3>(_var);}
void WWZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZW, put = WWZW)) TExtractType<4> wwz;
__declspec(property(get = WWZW, put = WWZW)) TExtractType<4> aab;
TExtractType<3> WWW() { return ExtractComponent<3, 3, 3, 3>(); } 
template <spv::StorageClass C1> void WWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 3>(_var);}
void WWW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWW, put = WWW)) TExtractType<3> www;
__declspec(property(get = WWW, put = WWW)) TExtractType<3> aaa;
TExtractType<4> WWWX() { return ExtractComponent<3, 3, 3, 3, 0>(); } 
template <spv::StorageClass C1> void WWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 3, 0>(_var);}
void WWWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWWX, put = WWWX)) TExtractType<4> www;
__declspec(property(get = WWWX, put = WWWX)) TExtractType<4> aaa;
TExtractType<4> WWWY() { return ExtractComponent<3, 3, 3, 3, 1>(); } 
template <spv::StorageClass C1> void WWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 3, 1>(_var);}
void WWWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWWY, put = WWWY)) TExtractType<4> www;
__declspec(property(get = WWWY, put = WWWY)) TExtractType<4> aaa;
TExtractType<4> WWWZ() { return ExtractComponent<3, 3, 3, 3, 2>(); } 
template <spv::StorageClass C1> void WWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 3, 2>(_var);}
void WWWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWWZ, put = WWWZ)) TExtractType<4> www;
__declspec(property(get = WWWZ, put = WWWZ)) TExtractType<4> aaa;
TExtractType<4> WWWW() { return ExtractComponent<3, 3, 3, 3, 3>(); } 
template <spv::StorageClass C1> void WWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 3, 3>(_var);}
void WWWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWWW, put = WWWW)) TExtractType<4> www;
__declspec(property(get = WWWW, put = WWWW)) TExtractType<4> aaa;
#endif // !TRACY_SPIRVVECTORCOMPONENTACCESS_H
