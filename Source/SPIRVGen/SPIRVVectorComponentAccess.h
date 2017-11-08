#ifndef TRACY_SPIRVVECTORCOMPONENTACCESS_H
#define TRACY_SPIRVVECTORCOMPONENTACCESS_H
TExtractType<1, 0> X() { return ExtractComponent<1, 0>(); } 
template <spv::StorageClass C1> void X(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) { InsertComponent<1, 0>(_var);}
void X(const vec_type_t<base_type_t<T>, 1>& _var) { InsertComponent<1, 0>(var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = X, put = X)) TExtractType<1, 0> x;
__declspec(property(get = X, put = X)) TExtractType<1, 0> r;
TExtractType<2, 0, 0> XX() { return ExtractComponent<2, 0, 0>(); } 
template <spv::StorageClass C1> void XX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 0, 0>(_var);}
void XX(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XX, put = XX)) TExtractType<2, 0, 0> xx;
__declspec(property(get = XX, put = XX)) TExtractType<2, 0, 0> rr;
TExtractType<3, 0, 0, 0> XXX() { return ExtractComponent<3, 0, 0, 0>(); } 
template <spv::StorageClass C1> void XXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 0>(_var);}
void XXX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXX, put = XXX)) TExtractType<3, 0, 0, 0> xxx;
__declspec(property(get = XXX, put = XXX)) TExtractType<3, 0, 0, 0> rrr;
TExtractType<3, 0, 0, 0, 0> XXXX() { return ExtractComponent<3, 0, 0, 0, 0>(); } 
template <spv::StorageClass C1> void XXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 0, 0>(_var);}
void XXXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXXX, put = XXXX)) TExtractType<3, 0, 0, 0, 0> xxx;
__declspec(property(get = XXXX, put = XXXX)) TExtractType<3, 0, 0, 0, 0> rrr;
TExtractType<3, 0, 0, 0, 1> XXXY() { return ExtractComponent<3, 0, 0, 0, 1>(); } 
template <spv::StorageClass C1> void XXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 0, 1>(_var);}
void XXXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXXY, put = XXXY)) TExtractType<3, 0, 0, 0, 1> xxx;
__declspec(property(get = XXXY, put = XXXY)) TExtractType<3, 0, 0, 0, 1> rrr;
TExtractType<3, 0, 0, 0, 2> XXXZ() { return ExtractComponent<3, 0, 0, 0, 2>(); } 
template <spv::StorageClass C1> void XXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 0, 2>(_var);}
void XXXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXXZ, put = XXXZ)) TExtractType<3, 0, 0, 0, 2> xxx;
__declspec(property(get = XXXZ, put = XXXZ)) TExtractType<3, 0, 0, 0, 2> rrr;
TExtractType<3, 0, 0, 0, 3> XXXW() { return ExtractComponent<3, 0, 0, 0, 3>(); } 
template <spv::StorageClass C1> void XXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 0, 3>(_var);}
void XXXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXXW, put = XXXW)) TExtractType<3, 0, 0, 0, 3> xxx;
__declspec(property(get = XXXW, put = XXXW)) TExtractType<3, 0, 0, 0, 3> rrr;
TExtractType<3, 0, 0, 1> XXY() { return ExtractComponent<3, 0, 0, 1>(); } 
template <spv::StorageClass C1> void XXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 1>(_var);}
void XXY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXY, put = XXY)) TExtractType<3, 0, 0, 1> xxy;
__declspec(property(get = XXY, put = XXY)) TExtractType<3, 0, 0, 1> rrg;
TExtractType<3, 0, 0, 1, 0> XXYX() { return ExtractComponent<3, 0, 0, 1, 0>(); } 
template <spv::StorageClass C1> void XXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 1, 0>(_var);}
void XXYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXYX, put = XXYX)) TExtractType<3, 0, 0, 1, 0> xxy;
__declspec(property(get = XXYX, put = XXYX)) TExtractType<3, 0, 0, 1, 0> rrg;
TExtractType<3, 0, 0, 1, 1> XXYY() { return ExtractComponent<3, 0, 0, 1, 1>(); } 
template <spv::StorageClass C1> void XXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 1, 1>(_var);}
void XXYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXYY, put = XXYY)) TExtractType<3, 0, 0, 1, 1> xxy;
__declspec(property(get = XXYY, put = XXYY)) TExtractType<3, 0, 0, 1, 1> rrg;
TExtractType<3, 0, 0, 1, 2> XXYZ() { return ExtractComponent<3, 0, 0, 1, 2>(); } 
template <spv::StorageClass C1> void XXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 1, 2>(_var);}
void XXYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXYZ, put = XXYZ)) TExtractType<3, 0, 0, 1, 2> xxy;
__declspec(property(get = XXYZ, put = XXYZ)) TExtractType<3, 0, 0, 1, 2> rrg;
TExtractType<3, 0, 0, 1, 3> XXYW() { return ExtractComponent<3, 0, 0, 1, 3>(); } 
template <spv::StorageClass C1> void XXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 1, 3>(_var);}
void XXYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXYW, put = XXYW)) TExtractType<3, 0, 0, 1, 3> xxy;
__declspec(property(get = XXYW, put = XXYW)) TExtractType<3, 0, 0, 1, 3> rrg;
TExtractType<3, 0, 0, 2> XXZ() { return ExtractComponent<3, 0, 0, 2>(); } 
template <spv::StorageClass C1> void XXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 2>(_var);}
void XXZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZ, put = XXZ)) TExtractType<3, 0, 0, 2> xxz;
__declspec(property(get = XXZ, put = XXZ)) TExtractType<3, 0, 0, 2> rrb;
TExtractType<3, 0, 0, 2, 0> XXZX() { return ExtractComponent<3, 0, 0, 2, 0>(); } 
template <spv::StorageClass C1> void XXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 2, 0>(_var);}
void XXZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZX, put = XXZX)) TExtractType<3, 0, 0, 2, 0> xxz;
__declspec(property(get = XXZX, put = XXZX)) TExtractType<3, 0, 0, 2, 0> rrb;
TExtractType<3, 0, 0, 2, 1> XXZY() { return ExtractComponent<3, 0, 0, 2, 1>(); } 
template <spv::StorageClass C1> void XXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 2, 1>(_var);}
void XXZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZY, put = XXZY)) TExtractType<3, 0, 0, 2, 1> xxz;
__declspec(property(get = XXZY, put = XXZY)) TExtractType<3, 0, 0, 2, 1> rrb;
TExtractType<3, 0, 0, 2, 2> XXZZ() { return ExtractComponent<3, 0, 0, 2, 2>(); } 
template <spv::StorageClass C1> void XXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 2, 2>(_var);}
void XXZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZZ, put = XXZZ)) TExtractType<3, 0, 0, 2, 2> xxz;
__declspec(property(get = XXZZ, put = XXZZ)) TExtractType<3, 0, 0, 2, 2> rrb;
TExtractType<3, 0, 0, 2, 3> XXZW() { return ExtractComponent<3, 0, 0, 2, 3>(); } 
template <spv::StorageClass C1> void XXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 2, 3>(_var);}
void XXZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZW, put = XXZW)) TExtractType<3, 0, 0, 2, 3> xxz;
__declspec(property(get = XXZW, put = XXZW)) TExtractType<3, 0, 0, 2, 3> rrb;
TExtractType<3, 0, 0, 3> XXW() { return ExtractComponent<3, 0, 0, 3>(); } 
template <spv::StorageClass C1> void XXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 3>(_var);}
void XXW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXW, put = XXW)) TExtractType<3, 0, 0, 3> xxw;
__declspec(property(get = XXW, put = XXW)) TExtractType<3, 0, 0, 3> rra;
TExtractType<3, 0, 0, 3, 0> XXWX() { return ExtractComponent<3, 0, 0, 3, 0>(); } 
template <spv::StorageClass C1> void XXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 3, 0>(_var);}
void XXWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXWX, put = XXWX)) TExtractType<3, 0, 0, 3, 0> xxw;
__declspec(property(get = XXWX, put = XXWX)) TExtractType<3, 0, 0, 3, 0> rra;
TExtractType<3, 0, 0, 3, 1> XXWY() { return ExtractComponent<3, 0, 0, 3, 1>(); } 
template <spv::StorageClass C1> void XXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 3, 1>(_var);}
void XXWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXWY, put = XXWY)) TExtractType<3, 0, 0, 3, 1> xxw;
__declspec(property(get = XXWY, put = XXWY)) TExtractType<3, 0, 0, 3, 1> rra;
TExtractType<3, 0, 0, 3, 2> XXWZ() { return ExtractComponent<3, 0, 0, 3, 2>(); } 
template <spv::StorageClass C1> void XXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 3, 2>(_var);}
void XXWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXWZ, put = XXWZ)) TExtractType<3, 0, 0, 3, 2> xxw;
__declspec(property(get = XXWZ, put = XXWZ)) TExtractType<3, 0, 0, 3, 2> rra;
TExtractType<3, 0, 0, 3, 3> XXWW() { return ExtractComponent<3, 0, 0, 3, 3>(); } 
template <spv::StorageClass C1> void XXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 3, 3>(_var);}
void XXWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXWW, put = XXWW)) TExtractType<3, 0, 0, 3, 3> xxw;
__declspec(property(get = XXWW, put = XXWW)) TExtractType<3, 0, 0, 3, 3> rra;
TExtractType<2, 0, 1> XY() { return ExtractComponent<2, 0, 1>(); } 
template <spv::StorageClass C1> void XY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 0, 1>(_var);}
void XY(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XY, put = XY)) TExtractType<2, 0, 1> xy;
__declspec(property(get = XY, put = XY)) TExtractType<2, 0, 1> rg;
TExtractType<3, 0, 1, 0> XYX() { return ExtractComponent<3, 0, 1, 0>(); } 
template <spv::StorageClass C1> void XYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 0>(_var);}
void XYX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYX, put = XYX)) TExtractType<3, 0, 1, 0> xyx;
__declspec(property(get = XYX, put = XYX)) TExtractType<3, 0, 1, 0> rgr;
TExtractType<3, 0, 1, 0, 0> XYXX() { return ExtractComponent<3, 0, 1, 0, 0>(); } 
template <spv::StorageClass C1> void XYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 0, 0>(_var);}
void XYXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYXX, put = XYXX)) TExtractType<3, 0, 1, 0, 0> xyx;
__declspec(property(get = XYXX, put = XYXX)) TExtractType<3, 0, 1, 0, 0> rgr;
TExtractType<3, 0, 1, 0, 1> XYXY() { return ExtractComponent<3, 0, 1, 0, 1>(); } 
template <spv::StorageClass C1> void XYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 0, 1>(_var);}
void XYXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYXY, put = XYXY)) TExtractType<3, 0, 1, 0, 1> xyx;
__declspec(property(get = XYXY, put = XYXY)) TExtractType<3, 0, 1, 0, 1> rgr;
TExtractType<3, 0, 1, 0, 2> XYXZ() { return ExtractComponent<3, 0, 1, 0, 2>(); } 
template <spv::StorageClass C1> void XYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 0, 2>(_var);}
void XYXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYXZ, put = XYXZ)) TExtractType<3, 0, 1, 0, 2> xyx;
__declspec(property(get = XYXZ, put = XYXZ)) TExtractType<3, 0, 1, 0, 2> rgr;
TExtractType<3, 0, 1, 0, 3> XYXW() { return ExtractComponent<3, 0, 1, 0, 3>(); } 
template <spv::StorageClass C1> void XYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 0, 3>(_var);}
void XYXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYXW, put = XYXW)) TExtractType<3, 0, 1, 0, 3> xyx;
__declspec(property(get = XYXW, put = XYXW)) TExtractType<3, 0, 1, 0, 3> rgr;
TExtractType<3, 0, 1, 1> XYY() { return ExtractComponent<3, 0, 1, 1>(); } 
template <spv::StorageClass C1> void XYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 1>(_var);}
void XYY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYY, put = XYY)) TExtractType<3, 0, 1, 1> xyy;
__declspec(property(get = XYY, put = XYY)) TExtractType<3, 0, 1, 1> rgg;
TExtractType<3, 0, 1, 1, 0> XYYX() { return ExtractComponent<3, 0, 1, 1, 0>(); } 
template <spv::StorageClass C1> void XYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 1, 0>(_var);}
void XYYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYYX, put = XYYX)) TExtractType<3, 0, 1, 1, 0> xyy;
__declspec(property(get = XYYX, put = XYYX)) TExtractType<3, 0, 1, 1, 0> rgg;
TExtractType<3, 0, 1, 1, 1> XYYY() { return ExtractComponent<3, 0, 1, 1, 1>(); } 
template <spv::StorageClass C1> void XYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 1, 1>(_var);}
void XYYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYYY, put = XYYY)) TExtractType<3, 0, 1, 1, 1> xyy;
__declspec(property(get = XYYY, put = XYYY)) TExtractType<3, 0, 1, 1, 1> rgg;
TExtractType<3, 0, 1, 1, 2> XYYZ() { return ExtractComponent<3, 0, 1, 1, 2>(); } 
template <spv::StorageClass C1> void XYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 1, 2>(_var);}
void XYYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYYZ, put = XYYZ)) TExtractType<3, 0, 1, 1, 2> xyy;
__declspec(property(get = XYYZ, put = XYYZ)) TExtractType<3, 0, 1, 1, 2> rgg;
TExtractType<3, 0, 1, 1, 3> XYYW() { return ExtractComponent<3, 0, 1, 1, 3>(); } 
template <spv::StorageClass C1> void XYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 1, 3>(_var);}
void XYYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYYW, put = XYYW)) TExtractType<3, 0, 1, 1, 3> xyy;
__declspec(property(get = XYYW, put = XYYW)) TExtractType<3, 0, 1, 1, 3> rgg;
TExtractType<3, 0, 1, 2> XYZ() { return ExtractComponent<3, 0, 1, 2>(); } 
template <spv::StorageClass C1> void XYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 2>(_var);}
void XYZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZ, put = XYZ)) TExtractType<3, 0, 1, 2> xyz;
__declspec(property(get = XYZ, put = XYZ)) TExtractType<3, 0, 1, 2> rgb;
TExtractType<3, 0, 1, 2, 0> XYZX() { return ExtractComponent<3, 0, 1, 2, 0>(); } 
template <spv::StorageClass C1> void XYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 2, 0>(_var);}
void XYZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZX, put = XYZX)) TExtractType<3, 0, 1, 2, 0> xyz;
__declspec(property(get = XYZX, put = XYZX)) TExtractType<3, 0, 1, 2, 0> rgb;
TExtractType<3, 0, 1, 2, 1> XYZY() { return ExtractComponent<3, 0, 1, 2, 1>(); } 
template <spv::StorageClass C1> void XYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 2, 1>(_var);}
void XYZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZY, put = XYZY)) TExtractType<3, 0, 1, 2, 1> xyz;
__declspec(property(get = XYZY, put = XYZY)) TExtractType<3, 0, 1, 2, 1> rgb;
TExtractType<3, 0, 1, 2, 2> XYZZ() { return ExtractComponent<3, 0, 1, 2, 2>(); } 
template <spv::StorageClass C1> void XYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 2, 2>(_var);}
void XYZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZZ, put = XYZZ)) TExtractType<3, 0, 1, 2, 2> xyz;
__declspec(property(get = XYZZ, put = XYZZ)) TExtractType<3, 0, 1, 2, 2> rgb;
TExtractType<3, 0, 1, 2, 3> XYZW() { return ExtractComponent<3, 0, 1, 2, 3>(); } 
template <spv::StorageClass C1> void XYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 2, 3>(_var);}
void XYZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZW, put = XYZW)) TExtractType<3, 0, 1, 2, 3> xyz;
__declspec(property(get = XYZW, put = XYZW)) TExtractType<3, 0, 1, 2, 3> rgb;
TExtractType<3, 0, 1, 3> XYW() { return ExtractComponent<3, 0, 1, 3>(); } 
template <spv::StorageClass C1> void XYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 3>(_var);}
void XYW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYW, put = XYW)) TExtractType<3, 0, 1, 3> xyw;
__declspec(property(get = XYW, put = XYW)) TExtractType<3, 0, 1, 3> rga;
TExtractType<3, 0, 1, 3, 0> XYWX() { return ExtractComponent<3, 0, 1, 3, 0>(); } 
template <spv::StorageClass C1> void XYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 3, 0>(_var);}
void XYWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYWX, put = XYWX)) TExtractType<3, 0, 1, 3, 0> xyw;
__declspec(property(get = XYWX, put = XYWX)) TExtractType<3, 0, 1, 3, 0> rga;
TExtractType<3, 0, 1, 3, 1> XYWY() { return ExtractComponent<3, 0, 1, 3, 1>(); } 
template <spv::StorageClass C1> void XYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 3, 1>(_var);}
void XYWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYWY, put = XYWY)) TExtractType<3, 0, 1, 3, 1> xyw;
__declspec(property(get = XYWY, put = XYWY)) TExtractType<3, 0, 1, 3, 1> rga;
TExtractType<3, 0, 1, 3, 2> XYWZ() { return ExtractComponent<3, 0, 1, 3, 2>(); } 
template <spv::StorageClass C1> void XYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 3, 2>(_var);}
void XYWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYWZ, put = XYWZ)) TExtractType<3, 0, 1, 3, 2> xyw;
__declspec(property(get = XYWZ, put = XYWZ)) TExtractType<3, 0, 1, 3, 2> rga;
TExtractType<3, 0, 1, 3, 3> XYWW() { return ExtractComponent<3, 0, 1, 3, 3>(); } 
template <spv::StorageClass C1> void XYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 3, 3>(_var);}
void XYWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYWW, put = XYWW)) TExtractType<3, 0, 1, 3, 3> xyw;
__declspec(property(get = XYWW, put = XYWW)) TExtractType<3, 0, 1, 3, 3> rga;
TExtractType<2, 0, 2> XZ() { return ExtractComponent<2, 0, 2>(); } 
template <spv::StorageClass C1> void XZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 0, 2>(_var);}
void XZ(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZ, put = XZ)) TExtractType<2, 0, 2> xz;
__declspec(property(get = XZ, put = XZ)) TExtractType<2, 0, 2> rb;
TExtractType<3, 0, 2, 0> XZX() { return ExtractComponent<3, 0, 2, 0>(); } 
template <spv::StorageClass C1> void XZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 0>(_var);}
void XZX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZX, put = XZX)) TExtractType<3, 0, 2, 0> xzx;
__declspec(property(get = XZX, put = XZX)) TExtractType<3, 0, 2, 0> rbr;
TExtractType<3, 0, 2, 0, 0> XZXX() { return ExtractComponent<3, 0, 2, 0, 0>(); } 
template <spv::StorageClass C1> void XZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 0, 0>(_var);}
void XZXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZXX, put = XZXX)) TExtractType<3, 0, 2, 0, 0> xzx;
__declspec(property(get = XZXX, put = XZXX)) TExtractType<3, 0, 2, 0, 0> rbr;
TExtractType<3, 0, 2, 0, 1> XZXY() { return ExtractComponent<3, 0, 2, 0, 1>(); } 
template <spv::StorageClass C1> void XZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 0, 1>(_var);}
void XZXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZXY, put = XZXY)) TExtractType<3, 0, 2, 0, 1> xzx;
__declspec(property(get = XZXY, put = XZXY)) TExtractType<3, 0, 2, 0, 1> rbr;
TExtractType<3, 0, 2, 0, 2> XZXZ() { return ExtractComponent<3, 0, 2, 0, 2>(); } 
template <spv::StorageClass C1> void XZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 0, 2>(_var);}
void XZXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZXZ, put = XZXZ)) TExtractType<3, 0, 2, 0, 2> xzx;
__declspec(property(get = XZXZ, put = XZXZ)) TExtractType<3, 0, 2, 0, 2> rbr;
TExtractType<3, 0, 2, 0, 3> XZXW() { return ExtractComponent<3, 0, 2, 0, 3>(); } 
template <spv::StorageClass C1> void XZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 0, 3>(_var);}
void XZXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZXW, put = XZXW)) TExtractType<3, 0, 2, 0, 3> xzx;
__declspec(property(get = XZXW, put = XZXW)) TExtractType<3, 0, 2, 0, 3> rbr;
TExtractType<3, 0, 2, 1> XZY() { return ExtractComponent<3, 0, 2, 1>(); } 
template <spv::StorageClass C1> void XZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 1>(_var);}
void XZY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZY, put = XZY)) TExtractType<3, 0, 2, 1> xzy;
__declspec(property(get = XZY, put = XZY)) TExtractType<3, 0, 2, 1> rbg;
TExtractType<3, 0, 2, 1, 0> XZYX() { return ExtractComponent<3, 0, 2, 1, 0>(); } 
template <spv::StorageClass C1> void XZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 1, 0>(_var);}
void XZYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZYX, put = XZYX)) TExtractType<3, 0, 2, 1, 0> xzy;
__declspec(property(get = XZYX, put = XZYX)) TExtractType<3, 0, 2, 1, 0> rbg;
TExtractType<3, 0, 2, 1, 1> XZYY() { return ExtractComponent<3, 0, 2, 1, 1>(); } 
template <spv::StorageClass C1> void XZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 1, 1>(_var);}
void XZYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZYY, put = XZYY)) TExtractType<3, 0, 2, 1, 1> xzy;
__declspec(property(get = XZYY, put = XZYY)) TExtractType<3, 0, 2, 1, 1> rbg;
TExtractType<3, 0, 2, 1, 2> XZYZ() { return ExtractComponent<3, 0, 2, 1, 2>(); } 
template <spv::StorageClass C1> void XZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 1, 2>(_var);}
void XZYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZYZ, put = XZYZ)) TExtractType<3, 0, 2, 1, 2> xzy;
__declspec(property(get = XZYZ, put = XZYZ)) TExtractType<3, 0, 2, 1, 2> rbg;
TExtractType<3, 0, 2, 1, 3> XZYW() { return ExtractComponent<3, 0, 2, 1, 3>(); } 
template <spv::StorageClass C1> void XZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 1, 3>(_var);}
void XZYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZYW, put = XZYW)) TExtractType<3, 0, 2, 1, 3> xzy;
__declspec(property(get = XZYW, put = XZYW)) TExtractType<3, 0, 2, 1, 3> rbg;
TExtractType<3, 0, 2, 2> XZZ() { return ExtractComponent<3, 0, 2, 2>(); } 
template <spv::StorageClass C1> void XZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 2>(_var);}
void XZZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZ, put = XZZ)) TExtractType<3, 0, 2, 2> xzz;
__declspec(property(get = XZZ, put = XZZ)) TExtractType<3, 0, 2, 2> rbb;
TExtractType<3, 0, 2, 2, 0> XZZX() { return ExtractComponent<3, 0, 2, 2, 0>(); } 
template <spv::StorageClass C1> void XZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 2, 0>(_var);}
void XZZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZX, put = XZZX)) TExtractType<3, 0, 2, 2, 0> xzz;
__declspec(property(get = XZZX, put = XZZX)) TExtractType<3, 0, 2, 2, 0> rbb;
TExtractType<3, 0, 2, 2, 1> XZZY() { return ExtractComponent<3, 0, 2, 2, 1>(); } 
template <spv::StorageClass C1> void XZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 2, 1>(_var);}
void XZZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZY, put = XZZY)) TExtractType<3, 0, 2, 2, 1> xzz;
__declspec(property(get = XZZY, put = XZZY)) TExtractType<3, 0, 2, 2, 1> rbb;
TExtractType<3, 0, 2, 2, 2> XZZZ() { return ExtractComponent<3, 0, 2, 2, 2>(); } 
template <spv::StorageClass C1> void XZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 2, 2>(_var);}
void XZZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZZ, put = XZZZ)) TExtractType<3, 0, 2, 2, 2> xzz;
__declspec(property(get = XZZZ, put = XZZZ)) TExtractType<3, 0, 2, 2, 2> rbb;
TExtractType<3, 0, 2, 2, 3> XZZW() { return ExtractComponent<3, 0, 2, 2, 3>(); } 
template <spv::StorageClass C1> void XZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 2, 3>(_var);}
void XZZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZW, put = XZZW)) TExtractType<3, 0, 2, 2, 3> xzz;
__declspec(property(get = XZZW, put = XZZW)) TExtractType<3, 0, 2, 2, 3> rbb;
TExtractType<3, 0, 2, 3> XZW() { return ExtractComponent<3, 0, 2, 3>(); } 
template <spv::StorageClass C1> void XZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 3>(_var);}
void XZW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZW, put = XZW)) TExtractType<3, 0, 2, 3> xzw;
__declspec(property(get = XZW, put = XZW)) TExtractType<3, 0, 2, 3> rba;
TExtractType<3, 0, 2, 3, 0> XZWX() { return ExtractComponent<3, 0, 2, 3, 0>(); } 
template <spv::StorageClass C1> void XZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 3, 0>(_var);}
void XZWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZWX, put = XZWX)) TExtractType<3, 0, 2, 3, 0> xzw;
__declspec(property(get = XZWX, put = XZWX)) TExtractType<3, 0, 2, 3, 0> rba;
TExtractType<3, 0, 2, 3, 1> XZWY() { return ExtractComponent<3, 0, 2, 3, 1>(); } 
template <spv::StorageClass C1> void XZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 3, 1>(_var);}
void XZWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZWY, put = XZWY)) TExtractType<3, 0, 2, 3, 1> xzw;
__declspec(property(get = XZWY, put = XZWY)) TExtractType<3, 0, 2, 3, 1> rba;
TExtractType<3, 0, 2, 3, 2> XZWZ() { return ExtractComponent<3, 0, 2, 3, 2>(); } 
template <spv::StorageClass C1> void XZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 3, 2>(_var);}
void XZWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZWZ, put = XZWZ)) TExtractType<3, 0, 2, 3, 2> xzw;
__declspec(property(get = XZWZ, put = XZWZ)) TExtractType<3, 0, 2, 3, 2> rba;
TExtractType<3, 0, 2, 3, 3> XZWW() { return ExtractComponent<3, 0, 2, 3, 3>(); } 
template <spv::StorageClass C1> void XZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 3, 3>(_var);}
void XZWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZWW, put = XZWW)) TExtractType<3, 0, 2, 3, 3> xzw;
__declspec(property(get = XZWW, put = XZWW)) TExtractType<3, 0, 2, 3, 3> rba;
TExtractType<2, 0, 3> XW() { return ExtractComponent<2, 0, 3>(); } 
template <spv::StorageClass C1> void XW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 0, 3>(_var);}
void XW(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XW, put = XW)) TExtractType<2, 0, 3> xw;
__declspec(property(get = XW, put = XW)) TExtractType<2, 0, 3> ra;
TExtractType<3, 0, 3, 0> XWX() { return ExtractComponent<3, 0, 3, 0>(); } 
template <spv::StorageClass C1> void XWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 0>(_var);}
void XWX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWX, put = XWX)) TExtractType<3, 0, 3, 0> xwx;
__declspec(property(get = XWX, put = XWX)) TExtractType<3, 0, 3, 0> rar;
TExtractType<3, 0, 3, 0, 0> XWXX() { return ExtractComponent<3, 0, 3, 0, 0>(); } 
template <spv::StorageClass C1> void XWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 0, 0>(_var);}
void XWXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWXX, put = XWXX)) TExtractType<3, 0, 3, 0, 0> xwx;
__declspec(property(get = XWXX, put = XWXX)) TExtractType<3, 0, 3, 0, 0> rar;
TExtractType<3, 0, 3, 0, 1> XWXY() { return ExtractComponent<3, 0, 3, 0, 1>(); } 
template <spv::StorageClass C1> void XWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 0, 1>(_var);}
void XWXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWXY, put = XWXY)) TExtractType<3, 0, 3, 0, 1> xwx;
__declspec(property(get = XWXY, put = XWXY)) TExtractType<3, 0, 3, 0, 1> rar;
TExtractType<3, 0, 3, 0, 2> XWXZ() { return ExtractComponent<3, 0, 3, 0, 2>(); } 
template <spv::StorageClass C1> void XWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 0, 2>(_var);}
void XWXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWXZ, put = XWXZ)) TExtractType<3, 0, 3, 0, 2> xwx;
__declspec(property(get = XWXZ, put = XWXZ)) TExtractType<3, 0, 3, 0, 2> rar;
TExtractType<3, 0, 3, 0, 3> XWXW() { return ExtractComponent<3, 0, 3, 0, 3>(); } 
template <spv::StorageClass C1> void XWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 0, 3>(_var);}
void XWXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWXW, put = XWXW)) TExtractType<3, 0, 3, 0, 3> xwx;
__declspec(property(get = XWXW, put = XWXW)) TExtractType<3, 0, 3, 0, 3> rar;
TExtractType<3, 0, 3, 1> XWY() { return ExtractComponent<3, 0, 3, 1>(); } 
template <spv::StorageClass C1> void XWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 1>(_var);}
void XWY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWY, put = XWY)) TExtractType<3, 0, 3, 1> xwy;
__declspec(property(get = XWY, put = XWY)) TExtractType<3, 0, 3, 1> rag;
TExtractType<3, 0, 3, 1, 0> XWYX() { return ExtractComponent<3, 0, 3, 1, 0>(); } 
template <spv::StorageClass C1> void XWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 1, 0>(_var);}
void XWYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWYX, put = XWYX)) TExtractType<3, 0, 3, 1, 0> xwy;
__declspec(property(get = XWYX, put = XWYX)) TExtractType<3, 0, 3, 1, 0> rag;
TExtractType<3, 0, 3, 1, 1> XWYY() { return ExtractComponent<3, 0, 3, 1, 1>(); } 
template <spv::StorageClass C1> void XWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 1, 1>(_var);}
void XWYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWYY, put = XWYY)) TExtractType<3, 0, 3, 1, 1> xwy;
__declspec(property(get = XWYY, put = XWYY)) TExtractType<3, 0, 3, 1, 1> rag;
TExtractType<3, 0, 3, 1, 2> XWYZ() { return ExtractComponent<3, 0, 3, 1, 2>(); } 
template <spv::StorageClass C1> void XWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 1, 2>(_var);}
void XWYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWYZ, put = XWYZ)) TExtractType<3, 0, 3, 1, 2> xwy;
__declspec(property(get = XWYZ, put = XWYZ)) TExtractType<3, 0, 3, 1, 2> rag;
TExtractType<3, 0, 3, 1, 3> XWYW() { return ExtractComponent<3, 0, 3, 1, 3>(); } 
template <spv::StorageClass C1> void XWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 1, 3>(_var);}
void XWYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWYW, put = XWYW)) TExtractType<3, 0, 3, 1, 3> xwy;
__declspec(property(get = XWYW, put = XWYW)) TExtractType<3, 0, 3, 1, 3> rag;
TExtractType<3, 0, 3, 2> XWZ() { return ExtractComponent<3, 0, 3, 2>(); } 
template <spv::StorageClass C1> void XWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 2>(_var);}
void XWZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZ, put = XWZ)) TExtractType<3, 0, 3, 2> xwz;
__declspec(property(get = XWZ, put = XWZ)) TExtractType<3, 0, 3, 2> rab;
TExtractType<3, 0, 3, 2, 0> XWZX() { return ExtractComponent<3, 0, 3, 2, 0>(); } 
template <spv::StorageClass C1> void XWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 2, 0>(_var);}
void XWZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZX, put = XWZX)) TExtractType<3, 0, 3, 2, 0> xwz;
__declspec(property(get = XWZX, put = XWZX)) TExtractType<3, 0, 3, 2, 0> rab;
TExtractType<3, 0, 3, 2, 1> XWZY() { return ExtractComponent<3, 0, 3, 2, 1>(); } 
template <spv::StorageClass C1> void XWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 2, 1>(_var);}
void XWZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZY, put = XWZY)) TExtractType<3, 0, 3, 2, 1> xwz;
__declspec(property(get = XWZY, put = XWZY)) TExtractType<3, 0, 3, 2, 1> rab;
TExtractType<3, 0, 3, 2, 2> XWZZ() { return ExtractComponent<3, 0, 3, 2, 2>(); } 
template <spv::StorageClass C1> void XWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 2, 2>(_var);}
void XWZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZZ, put = XWZZ)) TExtractType<3, 0, 3, 2, 2> xwz;
__declspec(property(get = XWZZ, put = XWZZ)) TExtractType<3, 0, 3, 2, 2> rab;
TExtractType<3, 0, 3, 2, 3> XWZW() { return ExtractComponent<3, 0, 3, 2, 3>(); } 
template <spv::StorageClass C1> void XWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 2, 3>(_var);}
void XWZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZW, put = XWZW)) TExtractType<3, 0, 3, 2, 3> xwz;
__declspec(property(get = XWZW, put = XWZW)) TExtractType<3, 0, 3, 2, 3> rab;
TExtractType<3, 0, 3, 3> XWW() { return ExtractComponent<3, 0, 3, 3>(); } 
template <spv::StorageClass C1> void XWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 3>(_var);}
void XWW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWW, put = XWW)) TExtractType<3, 0, 3, 3> xww;
__declspec(property(get = XWW, put = XWW)) TExtractType<3, 0, 3, 3> raa;
TExtractType<3, 0, 3, 3, 0> XWWX() { return ExtractComponent<3, 0, 3, 3, 0>(); } 
template <spv::StorageClass C1> void XWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 3, 0>(_var);}
void XWWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWWX, put = XWWX)) TExtractType<3, 0, 3, 3, 0> xww;
__declspec(property(get = XWWX, put = XWWX)) TExtractType<3, 0, 3, 3, 0> raa;
TExtractType<3, 0, 3, 3, 1> XWWY() { return ExtractComponent<3, 0, 3, 3, 1>(); } 
template <spv::StorageClass C1> void XWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 3, 1>(_var);}
void XWWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWWY, put = XWWY)) TExtractType<3, 0, 3, 3, 1> xww;
__declspec(property(get = XWWY, put = XWWY)) TExtractType<3, 0, 3, 3, 1> raa;
TExtractType<3, 0, 3, 3, 2> XWWZ() { return ExtractComponent<3, 0, 3, 3, 2>(); } 
template <spv::StorageClass C1> void XWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 3, 2>(_var);}
void XWWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWWZ, put = XWWZ)) TExtractType<3, 0, 3, 3, 2> xww;
__declspec(property(get = XWWZ, put = XWWZ)) TExtractType<3, 0, 3, 3, 2> raa;
TExtractType<3, 0, 3, 3, 3> XWWW() { return ExtractComponent<3, 0, 3, 3, 3>(); } 
template <spv::StorageClass C1> void XWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 3, 3>(_var);}
void XWWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 0, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWWW, put = XWWW)) TExtractType<3, 0, 3, 3, 3> xww;
__declspec(property(get = XWWW, put = XWWW)) TExtractType<3, 0, 3, 3, 3> raa;
TExtractType<1, 1> Y() { return ExtractComponent<1, 1>(); } 
template <spv::StorageClass C1> void Y(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) { InsertComponent<1, 1>(_var);}
void Y(const vec_type_t<base_type_t<T>, 1>& _var) { InsertComponent<1, 1>(var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = Y, put = Y)) TExtractType<1, 1> y;
__declspec(property(get = Y, put = Y)) TExtractType<1, 1> g;
TExtractType<2, 1, 0> YX() { return ExtractComponent<2, 1, 0>(); } 
template <spv::StorageClass C1> void YX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 1, 0>(_var);}
void YX(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YX, put = YX)) TExtractType<2, 1, 0> yx;
__declspec(property(get = YX, put = YX)) TExtractType<2, 1, 0> gr;
TExtractType<3, 1, 0, 0> YXX() { return ExtractComponent<3, 1, 0, 0>(); } 
template <spv::StorageClass C1> void YXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 0>(_var);}
void YXX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXX, put = YXX)) TExtractType<3, 1, 0, 0> yxx;
__declspec(property(get = YXX, put = YXX)) TExtractType<3, 1, 0, 0> grr;
TExtractType<3, 1, 0, 0, 0> YXXX() { return ExtractComponent<3, 1, 0, 0, 0>(); } 
template <spv::StorageClass C1> void YXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 0, 0>(_var);}
void YXXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXXX, put = YXXX)) TExtractType<3, 1, 0, 0, 0> yxx;
__declspec(property(get = YXXX, put = YXXX)) TExtractType<3, 1, 0, 0, 0> grr;
TExtractType<3, 1, 0, 0, 1> YXXY() { return ExtractComponent<3, 1, 0, 0, 1>(); } 
template <spv::StorageClass C1> void YXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 0, 1>(_var);}
void YXXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXXY, put = YXXY)) TExtractType<3, 1, 0, 0, 1> yxx;
__declspec(property(get = YXXY, put = YXXY)) TExtractType<3, 1, 0, 0, 1> grr;
TExtractType<3, 1, 0, 0, 2> YXXZ() { return ExtractComponent<3, 1, 0, 0, 2>(); } 
template <spv::StorageClass C1> void YXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 0, 2>(_var);}
void YXXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXXZ, put = YXXZ)) TExtractType<3, 1, 0, 0, 2> yxx;
__declspec(property(get = YXXZ, put = YXXZ)) TExtractType<3, 1, 0, 0, 2> grr;
TExtractType<3, 1, 0, 0, 3> YXXW() { return ExtractComponent<3, 1, 0, 0, 3>(); } 
template <spv::StorageClass C1> void YXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 0, 3>(_var);}
void YXXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXXW, put = YXXW)) TExtractType<3, 1, 0, 0, 3> yxx;
__declspec(property(get = YXXW, put = YXXW)) TExtractType<3, 1, 0, 0, 3> grr;
TExtractType<3, 1, 0, 1> YXY() { return ExtractComponent<3, 1, 0, 1>(); } 
template <spv::StorageClass C1> void YXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 1>(_var);}
void YXY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXY, put = YXY)) TExtractType<3, 1, 0, 1> yxy;
__declspec(property(get = YXY, put = YXY)) TExtractType<3, 1, 0, 1> grg;
TExtractType<3, 1, 0, 1, 0> YXYX() { return ExtractComponent<3, 1, 0, 1, 0>(); } 
template <spv::StorageClass C1> void YXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 1, 0>(_var);}
void YXYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXYX, put = YXYX)) TExtractType<3, 1, 0, 1, 0> yxy;
__declspec(property(get = YXYX, put = YXYX)) TExtractType<3, 1, 0, 1, 0> grg;
TExtractType<3, 1, 0, 1, 1> YXYY() { return ExtractComponent<3, 1, 0, 1, 1>(); } 
template <spv::StorageClass C1> void YXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 1, 1>(_var);}
void YXYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXYY, put = YXYY)) TExtractType<3, 1, 0, 1, 1> yxy;
__declspec(property(get = YXYY, put = YXYY)) TExtractType<3, 1, 0, 1, 1> grg;
TExtractType<3, 1, 0, 1, 2> YXYZ() { return ExtractComponent<3, 1, 0, 1, 2>(); } 
template <spv::StorageClass C1> void YXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 1, 2>(_var);}
void YXYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXYZ, put = YXYZ)) TExtractType<3, 1, 0, 1, 2> yxy;
__declspec(property(get = YXYZ, put = YXYZ)) TExtractType<3, 1, 0, 1, 2> grg;
TExtractType<3, 1, 0, 1, 3> YXYW() { return ExtractComponent<3, 1, 0, 1, 3>(); } 
template <spv::StorageClass C1> void YXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 1, 3>(_var);}
void YXYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXYW, put = YXYW)) TExtractType<3, 1, 0, 1, 3> yxy;
__declspec(property(get = YXYW, put = YXYW)) TExtractType<3, 1, 0, 1, 3> grg;
TExtractType<3, 1, 0, 2> YXZ() { return ExtractComponent<3, 1, 0, 2>(); } 
template <spv::StorageClass C1> void YXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 2>(_var);}
void YXZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZ, put = YXZ)) TExtractType<3, 1, 0, 2> yxz;
__declspec(property(get = YXZ, put = YXZ)) TExtractType<3, 1, 0, 2> grb;
TExtractType<3, 1, 0, 2, 0> YXZX() { return ExtractComponent<3, 1, 0, 2, 0>(); } 
template <spv::StorageClass C1> void YXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 2, 0>(_var);}
void YXZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZX, put = YXZX)) TExtractType<3, 1, 0, 2, 0> yxz;
__declspec(property(get = YXZX, put = YXZX)) TExtractType<3, 1, 0, 2, 0> grb;
TExtractType<3, 1, 0, 2, 1> YXZY() { return ExtractComponent<3, 1, 0, 2, 1>(); } 
template <spv::StorageClass C1> void YXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 2, 1>(_var);}
void YXZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZY, put = YXZY)) TExtractType<3, 1, 0, 2, 1> yxz;
__declspec(property(get = YXZY, put = YXZY)) TExtractType<3, 1, 0, 2, 1> grb;
TExtractType<3, 1, 0, 2, 2> YXZZ() { return ExtractComponent<3, 1, 0, 2, 2>(); } 
template <spv::StorageClass C1> void YXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 2, 2>(_var);}
void YXZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZZ, put = YXZZ)) TExtractType<3, 1, 0, 2, 2> yxz;
__declspec(property(get = YXZZ, put = YXZZ)) TExtractType<3, 1, 0, 2, 2> grb;
TExtractType<3, 1, 0, 2, 3> YXZW() { return ExtractComponent<3, 1, 0, 2, 3>(); } 
template <spv::StorageClass C1> void YXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 2, 3>(_var);}
void YXZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZW, put = YXZW)) TExtractType<3, 1, 0, 2, 3> yxz;
__declspec(property(get = YXZW, put = YXZW)) TExtractType<3, 1, 0, 2, 3> grb;
TExtractType<3, 1, 0, 3> YXW() { return ExtractComponent<3, 1, 0, 3>(); } 
template <spv::StorageClass C1> void YXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 3>(_var);}
void YXW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXW, put = YXW)) TExtractType<3, 1, 0, 3> yxw;
__declspec(property(get = YXW, put = YXW)) TExtractType<3, 1, 0, 3> gra;
TExtractType<3, 1, 0, 3, 0> YXWX() { return ExtractComponent<3, 1, 0, 3, 0>(); } 
template <spv::StorageClass C1> void YXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 3, 0>(_var);}
void YXWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXWX, put = YXWX)) TExtractType<3, 1, 0, 3, 0> yxw;
__declspec(property(get = YXWX, put = YXWX)) TExtractType<3, 1, 0, 3, 0> gra;
TExtractType<3, 1, 0, 3, 1> YXWY() { return ExtractComponent<3, 1, 0, 3, 1>(); } 
template <spv::StorageClass C1> void YXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 3, 1>(_var);}
void YXWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXWY, put = YXWY)) TExtractType<3, 1, 0, 3, 1> yxw;
__declspec(property(get = YXWY, put = YXWY)) TExtractType<3, 1, 0, 3, 1> gra;
TExtractType<3, 1, 0, 3, 2> YXWZ() { return ExtractComponent<3, 1, 0, 3, 2>(); } 
template <spv::StorageClass C1> void YXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 3, 2>(_var);}
void YXWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXWZ, put = YXWZ)) TExtractType<3, 1, 0, 3, 2> yxw;
__declspec(property(get = YXWZ, put = YXWZ)) TExtractType<3, 1, 0, 3, 2> gra;
TExtractType<3, 1, 0, 3, 3> YXWW() { return ExtractComponent<3, 1, 0, 3, 3>(); } 
template <spv::StorageClass C1> void YXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 3, 3>(_var);}
void YXWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXWW, put = YXWW)) TExtractType<3, 1, 0, 3, 3> yxw;
__declspec(property(get = YXWW, put = YXWW)) TExtractType<3, 1, 0, 3, 3> gra;
TExtractType<2, 1, 1> YY() { return ExtractComponent<2, 1, 1>(); } 
template <spv::StorageClass C1> void YY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 1, 1>(_var);}
void YY(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YY, put = YY)) TExtractType<2, 1, 1> yy;
__declspec(property(get = YY, put = YY)) TExtractType<2, 1, 1> gg;
TExtractType<3, 1, 1, 0> YYX() { return ExtractComponent<3, 1, 1, 0>(); } 
template <spv::StorageClass C1> void YYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 0>(_var);}
void YYX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYX, put = YYX)) TExtractType<3, 1, 1, 0> yyx;
__declspec(property(get = YYX, put = YYX)) TExtractType<3, 1, 1, 0> ggr;
TExtractType<3, 1, 1, 0, 0> YYXX() { return ExtractComponent<3, 1, 1, 0, 0>(); } 
template <spv::StorageClass C1> void YYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 0, 0>(_var);}
void YYXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYXX, put = YYXX)) TExtractType<3, 1, 1, 0, 0> yyx;
__declspec(property(get = YYXX, put = YYXX)) TExtractType<3, 1, 1, 0, 0> ggr;
TExtractType<3, 1, 1, 0, 1> YYXY() { return ExtractComponent<3, 1, 1, 0, 1>(); } 
template <spv::StorageClass C1> void YYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 0, 1>(_var);}
void YYXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYXY, put = YYXY)) TExtractType<3, 1, 1, 0, 1> yyx;
__declspec(property(get = YYXY, put = YYXY)) TExtractType<3, 1, 1, 0, 1> ggr;
TExtractType<3, 1, 1, 0, 2> YYXZ() { return ExtractComponent<3, 1, 1, 0, 2>(); } 
template <spv::StorageClass C1> void YYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 0, 2>(_var);}
void YYXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYXZ, put = YYXZ)) TExtractType<3, 1, 1, 0, 2> yyx;
__declspec(property(get = YYXZ, put = YYXZ)) TExtractType<3, 1, 1, 0, 2> ggr;
TExtractType<3, 1, 1, 0, 3> YYXW() { return ExtractComponent<3, 1, 1, 0, 3>(); } 
template <spv::StorageClass C1> void YYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 0, 3>(_var);}
void YYXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYXW, put = YYXW)) TExtractType<3, 1, 1, 0, 3> yyx;
__declspec(property(get = YYXW, put = YYXW)) TExtractType<3, 1, 1, 0, 3> ggr;
TExtractType<3, 1, 1, 1> YYY() { return ExtractComponent<3, 1, 1, 1>(); } 
template <spv::StorageClass C1> void YYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 1>(_var);}
void YYY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYY, put = YYY)) TExtractType<3, 1, 1, 1> yyy;
__declspec(property(get = YYY, put = YYY)) TExtractType<3, 1, 1, 1> ggg;
TExtractType<3, 1, 1, 1, 0> YYYX() { return ExtractComponent<3, 1, 1, 1, 0>(); } 
template <spv::StorageClass C1> void YYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 1, 0>(_var);}
void YYYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYYX, put = YYYX)) TExtractType<3, 1, 1, 1, 0> yyy;
__declspec(property(get = YYYX, put = YYYX)) TExtractType<3, 1, 1, 1, 0> ggg;
TExtractType<3, 1, 1, 1, 1> YYYY() { return ExtractComponent<3, 1, 1, 1, 1>(); } 
template <spv::StorageClass C1> void YYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 1, 1>(_var);}
void YYYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYYY, put = YYYY)) TExtractType<3, 1, 1, 1, 1> yyy;
__declspec(property(get = YYYY, put = YYYY)) TExtractType<3, 1, 1, 1, 1> ggg;
TExtractType<3, 1, 1, 1, 2> YYYZ() { return ExtractComponent<3, 1, 1, 1, 2>(); } 
template <spv::StorageClass C1> void YYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 1, 2>(_var);}
void YYYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYYZ, put = YYYZ)) TExtractType<3, 1, 1, 1, 2> yyy;
__declspec(property(get = YYYZ, put = YYYZ)) TExtractType<3, 1, 1, 1, 2> ggg;
TExtractType<3, 1, 1, 1, 3> YYYW() { return ExtractComponent<3, 1, 1, 1, 3>(); } 
template <spv::StorageClass C1> void YYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 1, 3>(_var);}
void YYYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYYW, put = YYYW)) TExtractType<3, 1, 1, 1, 3> yyy;
__declspec(property(get = YYYW, put = YYYW)) TExtractType<3, 1, 1, 1, 3> ggg;
TExtractType<3, 1, 1, 2> YYZ() { return ExtractComponent<3, 1, 1, 2>(); } 
template <spv::StorageClass C1> void YYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 2>(_var);}
void YYZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZ, put = YYZ)) TExtractType<3, 1, 1, 2> yyz;
__declspec(property(get = YYZ, put = YYZ)) TExtractType<3, 1, 1, 2> ggb;
TExtractType<3, 1, 1, 2, 0> YYZX() { return ExtractComponent<3, 1, 1, 2, 0>(); } 
template <spv::StorageClass C1> void YYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 2, 0>(_var);}
void YYZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZX, put = YYZX)) TExtractType<3, 1, 1, 2, 0> yyz;
__declspec(property(get = YYZX, put = YYZX)) TExtractType<3, 1, 1, 2, 0> ggb;
TExtractType<3, 1, 1, 2, 1> YYZY() { return ExtractComponent<3, 1, 1, 2, 1>(); } 
template <spv::StorageClass C1> void YYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 2, 1>(_var);}
void YYZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZY, put = YYZY)) TExtractType<3, 1, 1, 2, 1> yyz;
__declspec(property(get = YYZY, put = YYZY)) TExtractType<3, 1, 1, 2, 1> ggb;
TExtractType<3, 1, 1, 2, 2> YYZZ() { return ExtractComponent<3, 1, 1, 2, 2>(); } 
template <spv::StorageClass C1> void YYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 2, 2>(_var);}
void YYZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZZ, put = YYZZ)) TExtractType<3, 1, 1, 2, 2> yyz;
__declspec(property(get = YYZZ, put = YYZZ)) TExtractType<3, 1, 1, 2, 2> ggb;
TExtractType<3, 1, 1, 2, 3> YYZW() { return ExtractComponent<3, 1, 1, 2, 3>(); } 
template <spv::StorageClass C1> void YYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 2, 3>(_var);}
void YYZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZW, put = YYZW)) TExtractType<3, 1, 1, 2, 3> yyz;
__declspec(property(get = YYZW, put = YYZW)) TExtractType<3, 1, 1, 2, 3> ggb;
TExtractType<3, 1, 1, 3> YYW() { return ExtractComponent<3, 1, 1, 3>(); } 
template <spv::StorageClass C1> void YYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 3>(_var);}
void YYW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYW, put = YYW)) TExtractType<3, 1, 1, 3> yyw;
__declspec(property(get = YYW, put = YYW)) TExtractType<3, 1, 1, 3> gga;
TExtractType<3, 1, 1, 3, 0> YYWX() { return ExtractComponent<3, 1, 1, 3, 0>(); } 
template <spv::StorageClass C1> void YYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 3, 0>(_var);}
void YYWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYWX, put = YYWX)) TExtractType<3, 1, 1, 3, 0> yyw;
__declspec(property(get = YYWX, put = YYWX)) TExtractType<3, 1, 1, 3, 0> gga;
TExtractType<3, 1, 1, 3, 1> YYWY() { return ExtractComponent<3, 1, 1, 3, 1>(); } 
template <spv::StorageClass C1> void YYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 3, 1>(_var);}
void YYWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYWY, put = YYWY)) TExtractType<3, 1, 1, 3, 1> yyw;
__declspec(property(get = YYWY, put = YYWY)) TExtractType<3, 1, 1, 3, 1> gga;
TExtractType<3, 1, 1, 3, 2> YYWZ() { return ExtractComponent<3, 1, 1, 3, 2>(); } 
template <spv::StorageClass C1> void YYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 3, 2>(_var);}
void YYWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYWZ, put = YYWZ)) TExtractType<3, 1, 1, 3, 2> yyw;
__declspec(property(get = YYWZ, put = YYWZ)) TExtractType<3, 1, 1, 3, 2> gga;
TExtractType<3, 1, 1, 3, 3> YYWW() { return ExtractComponent<3, 1, 1, 3, 3>(); } 
template <spv::StorageClass C1> void YYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 3, 3>(_var);}
void YYWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYWW, put = YYWW)) TExtractType<3, 1, 1, 3, 3> yyw;
__declspec(property(get = YYWW, put = YYWW)) TExtractType<3, 1, 1, 3, 3> gga;
TExtractType<2, 1, 2> YZ() { return ExtractComponent<2, 1, 2>(); } 
template <spv::StorageClass C1> void YZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 1, 2>(_var);}
void YZ(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZ, put = YZ)) TExtractType<2, 1, 2> yz;
__declspec(property(get = YZ, put = YZ)) TExtractType<2, 1, 2> gb;
TExtractType<3, 1, 2, 0> YZX() { return ExtractComponent<3, 1, 2, 0>(); } 
template <spv::StorageClass C1> void YZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 0>(_var);}
void YZX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZX, put = YZX)) TExtractType<3, 1, 2, 0> yzx;
__declspec(property(get = YZX, put = YZX)) TExtractType<3, 1, 2, 0> gbr;
TExtractType<3, 1, 2, 0, 0> YZXX() { return ExtractComponent<3, 1, 2, 0, 0>(); } 
template <spv::StorageClass C1> void YZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 0, 0>(_var);}
void YZXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZXX, put = YZXX)) TExtractType<3, 1, 2, 0, 0> yzx;
__declspec(property(get = YZXX, put = YZXX)) TExtractType<3, 1, 2, 0, 0> gbr;
TExtractType<3, 1, 2, 0, 1> YZXY() { return ExtractComponent<3, 1, 2, 0, 1>(); } 
template <spv::StorageClass C1> void YZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 0, 1>(_var);}
void YZXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZXY, put = YZXY)) TExtractType<3, 1, 2, 0, 1> yzx;
__declspec(property(get = YZXY, put = YZXY)) TExtractType<3, 1, 2, 0, 1> gbr;
TExtractType<3, 1, 2, 0, 2> YZXZ() { return ExtractComponent<3, 1, 2, 0, 2>(); } 
template <spv::StorageClass C1> void YZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 0, 2>(_var);}
void YZXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZXZ, put = YZXZ)) TExtractType<3, 1, 2, 0, 2> yzx;
__declspec(property(get = YZXZ, put = YZXZ)) TExtractType<3, 1, 2, 0, 2> gbr;
TExtractType<3, 1, 2, 0, 3> YZXW() { return ExtractComponent<3, 1, 2, 0, 3>(); } 
template <spv::StorageClass C1> void YZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 0, 3>(_var);}
void YZXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZXW, put = YZXW)) TExtractType<3, 1, 2, 0, 3> yzx;
__declspec(property(get = YZXW, put = YZXW)) TExtractType<3, 1, 2, 0, 3> gbr;
TExtractType<3, 1, 2, 1> YZY() { return ExtractComponent<3, 1, 2, 1>(); } 
template <spv::StorageClass C1> void YZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 1>(_var);}
void YZY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZY, put = YZY)) TExtractType<3, 1, 2, 1> yzy;
__declspec(property(get = YZY, put = YZY)) TExtractType<3, 1, 2, 1> gbg;
TExtractType<3, 1, 2, 1, 0> YZYX() { return ExtractComponent<3, 1, 2, 1, 0>(); } 
template <spv::StorageClass C1> void YZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 1, 0>(_var);}
void YZYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZYX, put = YZYX)) TExtractType<3, 1, 2, 1, 0> yzy;
__declspec(property(get = YZYX, put = YZYX)) TExtractType<3, 1, 2, 1, 0> gbg;
TExtractType<3, 1, 2, 1, 1> YZYY() { return ExtractComponent<3, 1, 2, 1, 1>(); } 
template <spv::StorageClass C1> void YZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 1, 1>(_var);}
void YZYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZYY, put = YZYY)) TExtractType<3, 1, 2, 1, 1> yzy;
__declspec(property(get = YZYY, put = YZYY)) TExtractType<3, 1, 2, 1, 1> gbg;
TExtractType<3, 1, 2, 1, 2> YZYZ() { return ExtractComponent<3, 1, 2, 1, 2>(); } 
template <spv::StorageClass C1> void YZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 1, 2>(_var);}
void YZYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZYZ, put = YZYZ)) TExtractType<3, 1, 2, 1, 2> yzy;
__declspec(property(get = YZYZ, put = YZYZ)) TExtractType<3, 1, 2, 1, 2> gbg;
TExtractType<3, 1, 2, 1, 3> YZYW() { return ExtractComponent<3, 1, 2, 1, 3>(); } 
template <spv::StorageClass C1> void YZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 1, 3>(_var);}
void YZYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZYW, put = YZYW)) TExtractType<3, 1, 2, 1, 3> yzy;
__declspec(property(get = YZYW, put = YZYW)) TExtractType<3, 1, 2, 1, 3> gbg;
TExtractType<3, 1, 2, 2> YZZ() { return ExtractComponent<3, 1, 2, 2>(); } 
template <spv::StorageClass C1> void YZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 2>(_var);}
void YZZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZ, put = YZZ)) TExtractType<3, 1, 2, 2> yzz;
__declspec(property(get = YZZ, put = YZZ)) TExtractType<3, 1, 2, 2> gbb;
TExtractType<3, 1, 2, 2, 0> YZZX() { return ExtractComponent<3, 1, 2, 2, 0>(); } 
template <spv::StorageClass C1> void YZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 2, 0>(_var);}
void YZZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZX, put = YZZX)) TExtractType<3, 1, 2, 2, 0> yzz;
__declspec(property(get = YZZX, put = YZZX)) TExtractType<3, 1, 2, 2, 0> gbb;
TExtractType<3, 1, 2, 2, 1> YZZY() { return ExtractComponent<3, 1, 2, 2, 1>(); } 
template <spv::StorageClass C1> void YZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 2, 1>(_var);}
void YZZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZY, put = YZZY)) TExtractType<3, 1, 2, 2, 1> yzz;
__declspec(property(get = YZZY, put = YZZY)) TExtractType<3, 1, 2, 2, 1> gbb;
TExtractType<3, 1, 2, 2, 2> YZZZ() { return ExtractComponent<3, 1, 2, 2, 2>(); } 
template <spv::StorageClass C1> void YZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 2, 2>(_var);}
void YZZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZZ, put = YZZZ)) TExtractType<3, 1, 2, 2, 2> yzz;
__declspec(property(get = YZZZ, put = YZZZ)) TExtractType<3, 1, 2, 2, 2> gbb;
TExtractType<3, 1, 2, 2, 3> YZZW() { return ExtractComponent<3, 1, 2, 2, 3>(); } 
template <spv::StorageClass C1> void YZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 2, 3>(_var);}
void YZZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZW, put = YZZW)) TExtractType<3, 1, 2, 2, 3> yzz;
__declspec(property(get = YZZW, put = YZZW)) TExtractType<3, 1, 2, 2, 3> gbb;
TExtractType<3, 1, 2, 3> YZW() { return ExtractComponent<3, 1, 2, 3>(); } 
template <spv::StorageClass C1> void YZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 3>(_var);}
void YZW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZW, put = YZW)) TExtractType<3, 1, 2, 3> yzw;
__declspec(property(get = YZW, put = YZW)) TExtractType<3, 1, 2, 3> gba;
TExtractType<3, 1, 2, 3, 0> YZWX() { return ExtractComponent<3, 1, 2, 3, 0>(); } 
template <spv::StorageClass C1> void YZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 3, 0>(_var);}
void YZWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZWX, put = YZWX)) TExtractType<3, 1, 2, 3, 0> yzw;
__declspec(property(get = YZWX, put = YZWX)) TExtractType<3, 1, 2, 3, 0> gba;
TExtractType<3, 1, 2, 3, 1> YZWY() { return ExtractComponent<3, 1, 2, 3, 1>(); } 
template <spv::StorageClass C1> void YZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 3, 1>(_var);}
void YZWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZWY, put = YZWY)) TExtractType<3, 1, 2, 3, 1> yzw;
__declspec(property(get = YZWY, put = YZWY)) TExtractType<3, 1, 2, 3, 1> gba;
TExtractType<3, 1, 2, 3, 2> YZWZ() { return ExtractComponent<3, 1, 2, 3, 2>(); } 
template <spv::StorageClass C1> void YZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 3, 2>(_var);}
void YZWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZWZ, put = YZWZ)) TExtractType<3, 1, 2, 3, 2> yzw;
__declspec(property(get = YZWZ, put = YZWZ)) TExtractType<3, 1, 2, 3, 2> gba;
TExtractType<3, 1, 2, 3, 3> YZWW() { return ExtractComponent<3, 1, 2, 3, 3>(); } 
template <spv::StorageClass C1> void YZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 3, 3>(_var);}
void YZWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZWW, put = YZWW)) TExtractType<3, 1, 2, 3, 3> yzw;
__declspec(property(get = YZWW, put = YZWW)) TExtractType<3, 1, 2, 3, 3> gba;
TExtractType<2, 1, 3> YW() { return ExtractComponent<2, 1, 3>(); } 
template <spv::StorageClass C1> void YW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 1, 3>(_var);}
void YW(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YW, put = YW)) TExtractType<2, 1, 3> yw;
__declspec(property(get = YW, put = YW)) TExtractType<2, 1, 3> ga;
TExtractType<3, 1, 3, 0> YWX() { return ExtractComponent<3, 1, 3, 0>(); } 
template <spv::StorageClass C1> void YWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 0>(_var);}
void YWX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWX, put = YWX)) TExtractType<3, 1, 3, 0> ywx;
__declspec(property(get = YWX, put = YWX)) TExtractType<3, 1, 3, 0> gar;
TExtractType<3, 1, 3, 0, 0> YWXX() { return ExtractComponent<3, 1, 3, 0, 0>(); } 
template <spv::StorageClass C1> void YWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 0, 0>(_var);}
void YWXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWXX, put = YWXX)) TExtractType<3, 1, 3, 0, 0> ywx;
__declspec(property(get = YWXX, put = YWXX)) TExtractType<3, 1, 3, 0, 0> gar;
TExtractType<3, 1, 3, 0, 1> YWXY() { return ExtractComponent<3, 1, 3, 0, 1>(); } 
template <spv::StorageClass C1> void YWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 0, 1>(_var);}
void YWXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWXY, put = YWXY)) TExtractType<3, 1, 3, 0, 1> ywx;
__declspec(property(get = YWXY, put = YWXY)) TExtractType<3, 1, 3, 0, 1> gar;
TExtractType<3, 1, 3, 0, 2> YWXZ() { return ExtractComponent<3, 1, 3, 0, 2>(); } 
template <spv::StorageClass C1> void YWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 0, 2>(_var);}
void YWXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWXZ, put = YWXZ)) TExtractType<3, 1, 3, 0, 2> ywx;
__declspec(property(get = YWXZ, put = YWXZ)) TExtractType<3, 1, 3, 0, 2> gar;
TExtractType<3, 1, 3, 0, 3> YWXW() { return ExtractComponent<3, 1, 3, 0, 3>(); } 
template <spv::StorageClass C1> void YWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 0, 3>(_var);}
void YWXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWXW, put = YWXW)) TExtractType<3, 1, 3, 0, 3> ywx;
__declspec(property(get = YWXW, put = YWXW)) TExtractType<3, 1, 3, 0, 3> gar;
TExtractType<3, 1, 3, 1> YWY() { return ExtractComponent<3, 1, 3, 1>(); } 
template <spv::StorageClass C1> void YWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 1>(_var);}
void YWY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWY, put = YWY)) TExtractType<3, 1, 3, 1> ywy;
__declspec(property(get = YWY, put = YWY)) TExtractType<3, 1, 3, 1> gag;
TExtractType<3, 1, 3, 1, 0> YWYX() { return ExtractComponent<3, 1, 3, 1, 0>(); } 
template <spv::StorageClass C1> void YWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 1, 0>(_var);}
void YWYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWYX, put = YWYX)) TExtractType<3, 1, 3, 1, 0> ywy;
__declspec(property(get = YWYX, put = YWYX)) TExtractType<3, 1, 3, 1, 0> gag;
TExtractType<3, 1, 3, 1, 1> YWYY() { return ExtractComponent<3, 1, 3, 1, 1>(); } 
template <spv::StorageClass C1> void YWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 1, 1>(_var);}
void YWYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWYY, put = YWYY)) TExtractType<3, 1, 3, 1, 1> ywy;
__declspec(property(get = YWYY, put = YWYY)) TExtractType<3, 1, 3, 1, 1> gag;
TExtractType<3, 1, 3, 1, 2> YWYZ() { return ExtractComponent<3, 1, 3, 1, 2>(); } 
template <spv::StorageClass C1> void YWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 1, 2>(_var);}
void YWYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWYZ, put = YWYZ)) TExtractType<3, 1, 3, 1, 2> ywy;
__declspec(property(get = YWYZ, put = YWYZ)) TExtractType<3, 1, 3, 1, 2> gag;
TExtractType<3, 1, 3, 1, 3> YWYW() { return ExtractComponent<3, 1, 3, 1, 3>(); } 
template <spv::StorageClass C1> void YWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 1, 3>(_var);}
void YWYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWYW, put = YWYW)) TExtractType<3, 1, 3, 1, 3> ywy;
__declspec(property(get = YWYW, put = YWYW)) TExtractType<3, 1, 3, 1, 3> gag;
TExtractType<3, 1, 3, 2> YWZ() { return ExtractComponent<3, 1, 3, 2>(); } 
template <spv::StorageClass C1> void YWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 2>(_var);}
void YWZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZ, put = YWZ)) TExtractType<3, 1, 3, 2> ywz;
__declspec(property(get = YWZ, put = YWZ)) TExtractType<3, 1, 3, 2> gab;
TExtractType<3, 1, 3, 2, 0> YWZX() { return ExtractComponent<3, 1, 3, 2, 0>(); } 
template <spv::StorageClass C1> void YWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 2, 0>(_var);}
void YWZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZX, put = YWZX)) TExtractType<3, 1, 3, 2, 0> ywz;
__declspec(property(get = YWZX, put = YWZX)) TExtractType<3, 1, 3, 2, 0> gab;
TExtractType<3, 1, 3, 2, 1> YWZY() { return ExtractComponent<3, 1, 3, 2, 1>(); } 
template <spv::StorageClass C1> void YWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 2, 1>(_var);}
void YWZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZY, put = YWZY)) TExtractType<3, 1, 3, 2, 1> ywz;
__declspec(property(get = YWZY, put = YWZY)) TExtractType<3, 1, 3, 2, 1> gab;
TExtractType<3, 1, 3, 2, 2> YWZZ() { return ExtractComponent<3, 1, 3, 2, 2>(); } 
template <spv::StorageClass C1> void YWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 2, 2>(_var);}
void YWZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZZ, put = YWZZ)) TExtractType<3, 1, 3, 2, 2> ywz;
__declspec(property(get = YWZZ, put = YWZZ)) TExtractType<3, 1, 3, 2, 2> gab;
TExtractType<3, 1, 3, 2, 3> YWZW() { return ExtractComponent<3, 1, 3, 2, 3>(); } 
template <spv::StorageClass C1> void YWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 2, 3>(_var);}
void YWZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZW, put = YWZW)) TExtractType<3, 1, 3, 2, 3> ywz;
__declspec(property(get = YWZW, put = YWZW)) TExtractType<3, 1, 3, 2, 3> gab;
TExtractType<3, 1, 3, 3> YWW() { return ExtractComponent<3, 1, 3, 3>(); } 
template <spv::StorageClass C1> void YWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 3>(_var);}
void YWW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWW, put = YWW)) TExtractType<3, 1, 3, 3> yww;
__declspec(property(get = YWW, put = YWW)) TExtractType<3, 1, 3, 3> gaa;
TExtractType<3, 1, 3, 3, 0> YWWX() { return ExtractComponent<3, 1, 3, 3, 0>(); } 
template <spv::StorageClass C1> void YWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 3, 0>(_var);}
void YWWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWWX, put = YWWX)) TExtractType<3, 1, 3, 3, 0> yww;
__declspec(property(get = YWWX, put = YWWX)) TExtractType<3, 1, 3, 3, 0> gaa;
TExtractType<3, 1, 3, 3, 1> YWWY() { return ExtractComponent<3, 1, 3, 3, 1>(); } 
template <spv::StorageClass C1> void YWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 3, 1>(_var);}
void YWWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWWY, put = YWWY)) TExtractType<3, 1, 3, 3, 1> yww;
__declspec(property(get = YWWY, put = YWWY)) TExtractType<3, 1, 3, 3, 1> gaa;
TExtractType<3, 1, 3, 3, 2> YWWZ() { return ExtractComponent<3, 1, 3, 3, 2>(); } 
template <spv::StorageClass C1> void YWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 3, 2>(_var);}
void YWWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWWZ, put = YWWZ)) TExtractType<3, 1, 3, 3, 2> yww;
__declspec(property(get = YWWZ, put = YWWZ)) TExtractType<3, 1, 3, 3, 2> gaa;
TExtractType<3, 1, 3, 3, 3> YWWW() { return ExtractComponent<3, 1, 3, 3, 3>(); } 
template <spv::StorageClass C1> void YWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 3, 3>(_var);}
void YWWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 1, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWWW, put = YWWW)) TExtractType<3, 1, 3, 3, 3> yww;
__declspec(property(get = YWWW, put = YWWW)) TExtractType<3, 1, 3, 3, 3> gaa;
TExtractType<1, 2> Z() { return ExtractComponent<1, 2>(); } 
template <spv::StorageClass C1> void Z(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) { InsertComponent<1, 2>(_var);}
void Z(const vec_type_t<base_type_t<T>, 1>& _var) { InsertComponent<1, 2>(var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = Z, put = Z)) TExtractType<1, 2> z;
__declspec(property(get = Z, put = Z)) TExtractType<1, 2> b;
TExtractType<2, 2, 0> ZX() { return ExtractComponent<2, 2, 0>(); } 
template <spv::StorageClass C1> void ZX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 2, 0>(_var);}
void ZX(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZX, put = ZX)) TExtractType<2, 2, 0> zx;
__declspec(property(get = ZX, put = ZX)) TExtractType<2, 2, 0> br;
TExtractType<3, 2, 0, 0> ZXX() { return ExtractComponent<3, 2, 0, 0>(); } 
template <spv::StorageClass C1> void ZXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 0>(_var);}
void ZXX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXX, put = ZXX)) TExtractType<3, 2, 0, 0> zxx;
__declspec(property(get = ZXX, put = ZXX)) TExtractType<3, 2, 0, 0> brr;
TExtractType<3, 2, 0, 0, 0> ZXXX() { return ExtractComponent<3, 2, 0, 0, 0>(); } 
template <spv::StorageClass C1> void ZXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 0, 0>(_var);}
void ZXXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXXX, put = ZXXX)) TExtractType<3, 2, 0, 0, 0> zxx;
__declspec(property(get = ZXXX, put = ZXXX)) TExtractType<3, 2, 0, 0, 0> brr;
TExtractType<3, 2, 0, 0, 1> ZXXY() { return ExtractComponent<3, 2, 0, 0, 1>(); } 
template <spv::StorageClass C1> void ZXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 0, 1>(_var);}
void ZXXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXXY, put = ZXXY)) TExtractType<3, 2, 0, 0, 1> zxx;
__declspec(property(get = ZXXY, put = ZXXY)) TExtractType<3, 2, 0, 0, 1> brr;
TExtractType<3, 2, 0, 0, 2> ZXXZ() { return ExtractComponent<3, 2, 0, 0, 2>(); } 
template <spv::StorageClass C1> void ZXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 0, 2>(_var);}
void ZXXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXXZ, put = ZXXZ)) TExtractType<3, 2, 0, 0, 2> zxx;
__declspec(property(get = ZXXZ, put = ZXXZ)) TExtractType<3, 2, 0, 0, 2> brr;
TExtractType<3, 2, 0, 0, 3> ZXXW() { return ExtractComponent<3, 2, 0, 0, 3>(); } 
template <spv::StorageClass C1> void ZXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 0, 3>(_var);}
void ZXXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXXW, put = ZXXW)) TExtractType<3, 2, 0, 0, 3> zxx;
__declspec(property(get = ZXXW, put = ZXXW)) TExtractType<3, 2, 0, 0, 3> brr;
TExtractType<3, 2, 0, 1> ZXY() { return ExtractComponent<3, 2, 0, 1>(); } 
template <spv::StorageClass C1> void ZXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 1>(_var);}
void ZXY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXY, put = ZXY)) TExtractType<3, 2, 0, 1> zxy;
__declspec(property(get = ZXY, put = ZXY)) TExtractType<3, 2, 0, 1> brg;
TExtractType<3, 2, 0, 1, 0> ZXYX() { return ExtractComponent<3, 2, 0, 1, 0>(); } 
template <spv::StorageClass C1> void ZXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 1, 0>(_var);}
void ZXYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXYX, put = ZXYX)) TExtractType<3, 2, 0, 1, 0> zxy;
__declspec(property(get = ZXYX, put = ZXYX)) TExtractType<3, 2, 0, 1, 0> brg;
TExtractType<3, 2, 0, 1, 1> ZXYY() { return ExtractComponent<3, 2, 0, 1, 1>(); } 
template <spv::StorageClass C1> void ZXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 1, 1>(_var);}
void ZXYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXYY, put = ZXYY)) TExtractType<3, 2, 0, 1, 1> zxy;
__declspec(property(get = ZXYY, put = ZXYY)) TExtractType<3, 2, 0, 1, 1> brg;
TExtractType<3, 2, 0, 1, 2> ZXYZ() { return ExtractComponent<3, 2, 0, 1, 2>(); } 
template <spv::StorageClass C1> void ZXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 1, 2>(_var);}
void ZXYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXYZ, put = ZXYZ)) TExtractType<3, 2, 0, 1, 2> zxy;
__declspec(property(get = ZXYZ, put = ZXYZ)) TExtractType<3, 2, 0, 1, 2> brg;
TExtractType<3, 2, 0, 1, 3> ZXYW() { return ExtractComponent<3, 2, 0, 1, 3>(); } 
template <spv::StorageClass C1> void ZXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 1, 3>(_var);}
void ZXYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXYW, put = ZXYW)) TExtractType<3, 2, 0, 1, 3> zxy;
__declspec(property(get = ZXYW, put = ZXYW)) TExtractType<3, 2, 0, 1, 3> brg;
TExtractType<3, 2, 0, 2> ZXZ() { return ExtractComponent<3, 2, 0, 2>(); } 
template <spv::StorageClass C1> void ZXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 2>(_var);}
void ZXZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZ, put = ZXZ)) TExtractType<3, 2, 0, 2> zxz;
__declspec(property(get = ZXZ, put = ZXZ)) TExtractType<3, 2, 0, 2> brb;
TExtractType<3, 2, 0, 2, 0> ZXZX() { return ExtractComponent<3, 2, 0, 2, 0>(); } 
template <spv::StorageClass C1> void ZXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 2, 0>(_var);}
void ZXZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZX, put = ZXZX)) TExtractType<3, 2, 0, 2, 0> zxz;
__declspec(property(get = ZXZX, put = ZXZX)) TExtractType<3, 2, 0, 2, 0> brb;
TExtractType<3, 2, 0, 2, 1> ZXZY() { return ExtractComponent<3, 2, 0, 2, 1>(); } 
template <spv::StorageClass C1> void ZXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 2, 1>(_var);}
void ZXZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZY, put = ZXZY)) TExtractType<3, 2, 0, 2, 1> zxz;
__declspec(property(get = ZXZY, put = ZXZY)) TExtractType<3, 2, 0, 2, 1> brb;
TExtractType<3, 2, 0, 2, 2> ZXZZ() { return ExtractComponent<3, 2, 0, 2, 2>(); } 
template <spv::StorageClass C1> void ZXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 2, 2>(_var);}
void ZXZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZZ, put = ZXZZ)) TExtractType<3, 2, 0, 2, 2> zxz;
__declspec(property(get = ZXZZ, put = ZXZZ)) TExtractType<3, 2, 0, 2, 2> brb;
TExtractType<3, 2, 0, 2, 3> ZXZW() { return ExtractComponent<3, 2, 0, 2, 3>(); } 
template <spv::StorageClass C1> void ZXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 2, 3>(_var);}
void ZXZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZW, put = ZXZW)) TExtractType<3, 2, 0, 2, 3> zxz;
__declspec(property(get = ZXZW, put = ZXZW)) TExtractType<3, 2, 0, 2, 3> brb;
TExtractType<3, 2, 0, 3> ZXW() { return ExtractComponent<3, 2, 0, 3>(); } 
template <spv::StorageClass C1> void ZXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 3>(_var);}
void ZXW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXW, put = ZXW)) TExtractType<3, 2, 0, 3> zxw;
__declspec(property(get = ZXW, put = ZXW)) TExtractType<3, 2, 0, 3> bra;
TExtractType<3, 2, 0, 3, 0> ZXWX() { return ExtractComponent<3, 2, 0, 3, 0>(); } 
template <spv::StorageClass C1> void ZXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 3, 0>(_var);}
void ZXWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXWX, put = ZXWX)) TExtractType<3, 2, 0, 3, 0> zxw;
__declspec(property(get = ZXWX, put = ZXWX)) TExtractType<3, 2, 0, 3, 0> bra;
TExtractType<3, 2, 0, 3, 1> ZXWY() { return ExtractComponent<3, 2, 0, 3, 1>(); } 
template <spv::StorageClass C1> void ZXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 3, 1>(_var);}
void ZXWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXWY, put = ZXWY)) TExtractType<3, 2, 0, 3, 1> zxw;
__declspec(property(get = ZXWY, put = ZXWY)) TExtractType<3, 2, 0, 3, 1> bra;
TExtractType<3, 2, 0, 3, 2> ZXWZ() { return ExtractComponent<3, 2, 0, 3, 2>(); } 
template <spv::StorageClass C1> void ZXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 3, 2>(_var);}
void ZXWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXWZ, put = ZXWZ)) TExtractType<3, 2, 0, 3, 2> zxw;
__declspec(property(get = ZXWZ, put = ZXWZ)) TExtractType<3, 2, 0, 3, 2> bra;
TExtractType<3, 2, 0, 3, 3> ZXWW() { return ExtractComponent<3, 2, 0, 3, 3>(); } 
template <spv::StorageClass C1> void ZXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 3, 3>(_var);}
void ZXWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXWW, put = ZXWW)) TExtractType<3, 2, 0, 3, 3> zxw;
__declspec(property(get = ZXWW, put = ZXWW)) TExtractType<3, 2, 0, 3, 3> bra;
TExtractType<2, 2, 1> ZY() { return ExtractComponent<2, 2, 1>(); } 
template <spv::StorageClass C1> void ZY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 2, 1>(_var);}
void ZY(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZY, put = ZY)) TExtractType<2, 2, 1> zy;
__declspec(property(get = ZY, put = ZY)) TExtractType<2, 2, 1> bg;
TExtractType<3, 2, 1, 0> ZYX() { return ExtractComponent<3, 2, 1, 0>(); } 
template <spv::StorageClass C1> void ZYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 0>(_var);}
void ZYX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYX, put = ZYX)) TExtractType<3, 2, 1, 0> zyx;
__declspec(property(get = ZYX, put = ZYX)) TExtractType<3, 2, 1, 0> bgr;
TExtractType<3, 2, 1, 0, 0> ZYXX() { return ExtractComponent<3, 2, 1, 0, 0>(); } 
template <spv::StorageClass C1> void ZYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 0, 0>(_var);}
void ZYXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYXX, put = ZYXX)) TExtractType<3, 2, 1, 0, 0> zyx;
__declspec(property(get = ZYXX, put = ZYXX)) TExtractType<3, 2, 1, 0, 0> bgr;
TExtractType<3, 2, 1, 0, 1> ZYXY() { return ExtractComponent<3, 2, 1, 0, 1>(); } 
template <spv::StorageClass C1> void ZYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 0, 1>(_var);}
void ZYXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYXY, put = ZYXY)) TExtractType<3, 2, 1, 0, 1> zyx;
__declspec(property(get = ZYXY, put = ZYXY)) TExtractType<3, 2, 1, 0, 1> bgr;
TExtractType<3, 2, 1, 0, 2> ZYXZ() { return ExtractComponent<3, 2, 1, 0, 2>(); } 
template <spv::StorageClass C1> void ZYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 0, 2>(_var);}
void ZYXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYXZ, put = ZYXZ)) TExtractType<3, 2, 1, 0, 2> zyx;
__declspec(property(get = ZYXZ, put = ZYXZ)) TExtractType<3, 2, 1, 0, 2> bgr;
TExtractType<3, 2, 1, 0, 3> ZYXW() { return ExtractComponent<3, 2, 1, 0, 3>(); } 
template <spv::StorageClass C1> void ZYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 0, 3>(_var);}
void ZYXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYXW, put = ZYXW)) TExtractType<3, 2, 1, 0, 3> zyx;
__declspec(property(get = ZYXW, put = ZYXW)) TExtractType<3, 2, 1, 0, 3> bgr;
TExtractType<3, 2, 1, 1> ZYY() { return ExtractComponent<3, 2, 1, 1>(); } 
template <spv::StorageClass C1> void ZYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 1>(_var);}
void ZYY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYY, put = ZYY)) TExtractType<3, 2, 1, 1> zyy;
__declspec(property(get = ZYY, put = ZYY)) TExtractType<3, 2, 1, 1> bgg;
TExtractType<3, 2, 1, 1, 0> ZYYX() { return ExtractComponent<3, 2, 1, 1, 0>(); } 
template <spv::StorageClass C1> void ZYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 1, 0>(_var);}
void ZYYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYYX, put = ZYYX)) TExtractType<3, 2, 1, 1, 0> zyy;
__declspec(property(get = ZYYX, put = ZYYX)) TExtractType<3, 2, 1, 1, 0> bgg;
TExtractType<3, 2, 1, 1, 1> ZYYY() { return ExtractComponent<3, 2, 1, 1, 1>(); } 
template <spv::StorageClass C1> void ZYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 1, 1>(_var);}
void ZYYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYYY, put = ZYYY)) TExtractType<3, 2, 1, 1, 1> zyy;
__declspec(property(get = ZYYY, put = ZYYY)) TExtractType<3, 2, 1, 1, 1> bgg;
TExtractType<3, 2, 1, 1, 2> ZYYZ() { return ExtractComponent<3, 2, 1, 1, 2>(); } 
template <spv::StorageClass C1> void ZYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 1, 2>(_var);}
void ZYYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYYZ, put = ZYYZ)) TExtractType<3, 2, 1, 1, 2> zyy;
__declspec(property(get = ZYYZ, put = ZYYZ)) TExtractType<3, 2, 1, 1, 2> bgg;
TExtractType<3, 2, 1, 1, 3> ZYYW() { return ExtractComponent<3, 2, 1, 1, 3>(); } 
template <spv::StorageClass C1> void ZYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 1, 3>(_var);}
void ZYYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYYW, put = ZYYW)) TExtractType<3, 2, 1, 1, 3> zyy;
__declspec(property(get = ZYYW, put = ZYYW)) TExtractType<3, 2, 1, 1, 3> bgg;
TExtractType<3, 2, 1, 2> ZYZ() { return ExtractComponent<3, 2, 1, 2>(); } 
template <spv::StorageClass C1> void ZYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 2>(_var);}
void ZYZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZ, put = ZYZ)) TExtractType<3, 2, 1, 2> zyz;
__declspec(property(get = ZYZ, put = ZYZ)) TExtractType<3, 2, 1, 2> bgb;
TExtractType<3, 2, 1, 2, 0> ZYZX() { return ExtractComponent<3, 2, 1, 2, 0>(); } 
template <spv::StorageClass C1> void ZYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 2, 0>(_var);}
void ZYZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZX, put = ZYZX)) TExtractType<3, 2, 1, 2, 0> zyz;
__declspec(property(get = ZYZX, put = ZYZX)) TExtractType<3, 2, 1, 2, 0> bgb;
TExtractType<3, 2, 1, 2, 1> ZYZY() { return ExtractComponent<3, 2, 1, 2, 1>(); } 
template <spv::StorageClass C1> void ZYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 2, 1>(_var);}
void ZYZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZY, put = ZYZY)) TExtractType<3, 2, 1, 2, 1> zyz;
__declspec(property(get = ZYZY, put = ZYZY)) TExtractType<3, 2, 1, 2, 1> bgb;
TExtractType<3, 2, 1, 2, 2> ZYZZ() { return ExtractComponent<3, 2, 1, 2, 2>(); } 
template <spv::StorageClass C1> void ZYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 2, 2>(_var);}
void ZYZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZZ, put = ZYZZ)) TExtractType<3, 2, 1, 2, 2> zyz;
__declspec(property(get = ZYZZ, put = ZYZZ)) TExtractType<3, 2, 1, 2, 2> bgb;
TExtractType<3, 2, 1, 2, 3> ZYZW() { return ExtractComponent<3, 2, 1, 2, 3>(); } 
template <spv::StorageClass C1> void ZYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 2, 3>(_var);}
void ZYZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZW, put = ZYZW)) TExtractType<3, 2, 1, 2, 3> zyz;
__declspec(property(get = ZYZW, put = ZYZW)) TExtractType<3, 2, 1, 2, 3> bgb;
TExtractType<3, 2, 1, 3> ZYW() { return ExtractComponent<3, 2, 1, 3>(); } 
template <spv::StorageClass C1> void ZYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 3>(_var);}
void ZYW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYW, put = ZYW)) TExtractType<3, 2, 1, 3> zyw;
__declspec(property(get = ZYW, put = ZYW)) TExtractType<3, 2, 1, 3> bga;
TExtractType<3, 2, 1, 3, 0> ZYWX() { return ExtractComponent<3, 2, 1, 3, 0>(); } 
template <spv::StorageClass C1> void ZYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 3, 0>(_var);}
void ZYWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYWX, put = ZYWX)) TExtractType<3, 2, 1, 3, 0> zyw;
__declspec(property(get = ZYWX, put = ZYWX)) TExtractType<3, 2, 1, 3, 0> bga;
TExtractType<3, 2, 1, 3, 1> ZYWY() { return ExtractComponent<3, 2, 1, 3, 1>(); } 
template <spv::StorageClass C1> void ZYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 3, 1>(_var);}
void ZYWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYWY, put = ZYWY)) TExtractType<3, 2, 1, 3, 1> zyw;
__declspec(property(get = ZYWY, put = ZYWY)) TExtractType<3, 2, 1, 3, 1> bga;
TExtractType<3, 2, 1, 3, 2> ZYWZ() { return ExtractComponent<3, 2, 1, 3, 2>(); } 
template <spv::StorageClass C1> void ZYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 3, 2>(_var);}
void ZYWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYWZ, put = ZYWZ)) TExtractType<3, 2, 1, 3, 2> zyw;
__declspec(property(get = ZYWZ, put = ZYWZ)) TExtractType<3, 2, 1, 3, 2> bga;
TExtractType<3, 2, 1, 3, 3> ZYWW() { return ExtractComponent<3, 2, 1, 3, 3>(); } 
template <spv::StorageClass C1> void ZYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 3, 3>(_var);}
void ZYWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYWW, put = ZYWW)) TExtractType<3, 2, 1, 3, 3> zyw;
__declspec(property(get = ZYWW, put = ZYWW)) TExtractType<3, 2, 1, 3, 3> bga;
TExtractType<2, 2, 2> ZZ() { return ExtractComponent<2, 2, 2>(); } 
template <spv::StorageClass C1> void ZZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 2, 2>(_var);}
void ZZ(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZ, put = ZZ)) TExtractType<2, 2, 2> zz;
__declspec(property(get = ZZ, put = ZZ)) TExtractType<2, 2, 2> bb;
TExtractType<3, 2, 2, 0> ZZX() { return ExtractComponent<3, 2, 2, 0>(); } 
template <spv::StorageClass C1> void ZZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 0>(_var);}
void ZZX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZX, put = ZZX)) TExtractType<3, 2, 2, 0> zzx;
__declspec(property(get = ZZX, put = ZZX)) TExtractType<3, 2, 2, 0> bbr;
TExtractType<3, 2, 2, 0, 0> ZZXX() { return ExtractComponent<3, 2, 2, 0, 0>(); } 
template <spv::StorageClass C1> void ZZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 0, 0>(_var);}
void ZZXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZXX, put = ZZXX)) TExtractType<3, 2, 2, 0, 0> zzx;
__declspec(property(get = ZZXX, put = ZZXX)) TExtractType<3, 2, 2, 0, 0> bbr;
TExtractType<3, 2, 2, 0, 1> ZZXY() { return ExtractComponent<3, 2, 2, 0, 1>(); } 
template <spv::StorageClass C1> void ZZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 0, 1>(_var);}
void ZZXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZXY, put = ZZXY)) TExtractType<3, 2, 2, 0, 1> zzx;
__declspec(property(get = ZZXY, put = ZZXY)) TExtractType<3, 2, 2, 0, 1> bbr;
TExtractType<3, 2, 2, 0, 2> ZZXZ() { return ExtractComponent<3, 2, 2, 0, 2>(); } 
template <spv::StorageClass C1> void ZZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 0, 2>(_var);}
void ZZXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZXZ, put = ZZXZ)) TExtractType<3, 2, 2, 0, 2> zzx;
__declspec(property(get = ZZXZ, put = ZZXZ)) TExtractType<3, 2, 2, 0, 2> bbr;
TExtractType<3, 2, 2, 0, 3> ZZXW() { return ExtractComponent<3, 2, 2, 0, 3>(); } 
template <spv::StorageClass C1> void ZZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 0, 3>(_var);}
void ZZXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZXW, put = ZZXW)) TExtractType<3, 2, 2, 0, 3> zzx;
__declspec(property(get = ZZXW, put = ZZXW)) TExtractType<3, 2, 2, 0, 3> bbr;
TExtractType<3, 2, 2, 1> ZZY() { return ExtractComponent<3, 2, 2, 1>(); } 
template <spv::StorageClass C1> void ZZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 1>(_var);}
void ZZY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZY, put = ZZY)) TExtractType<3, 2, 2, 1> zzy;
__declspec(property(get = ZZY, put = ZZY)) TExtractType<3, 2, 2, 1> bbg;
TExtractType<3, 2, 2, 1, 0> ZZYX() { return ExtractComponent<3, 2, 2, 1, 0>(); } 
template <spv::StorageClass C1> void ZZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 1, 0>(_var);}
void ZZYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZYX, put = ZZYX)) TExtractType<3, 2, 2, 1, 0> zzy;
__declspec(property(get = ZZYX, put = ZZYX)) TExtractType<3, 2, 2, 1, 0> bbg;
TExtractType<3, 2, 2, 1, 1> ZZYY() { return ExtractComponent<3, 2, 2, 1, 1>(); } 
template <spv::StorageClass C1> void ZZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 1, 1>(_var);}
void ZZYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZYY, put = ZZYY)) TExtractType<3, 2, 2, 1, 1> zzy;
__declspec(property(get = ZZYY, put = ZZYY)) TExtractType<3, 2, 2, 1, 1> bbg;
TExtractType<3, 2, 2, 1, 2> ZZYZ() { return ExtractComponent<3, 2, 2, 1, 2>(); } 
template <spv::StorageClass C1> void ZZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 1, 2>(_var);}
void ZZYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZYZ, put = ZZYZ)) TExtractType<3, 2, 2, 1, 2> zzy;
__declspec(property(get = ZZYZ, put = ZZYZ)) TExtractType<3, 2, 2, 1, 2> bbg;
TExtractType<3, 2, 2, 1, 3> ZZYW() { return ExtractComponent<3, 2, 2, 1, 3>(); } 
template <spv::StorageClass C1> void ZZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 1, 3>(_var);}
void ZZYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZYW, put = ZZYW)) TExtractType<3, 2, 2, 1, 3> zzy;
__declspec(property(get = ZZYW, put = ZZYW)) TExtractType<3, 2, 2, 1, 3> bbg;
TExtractType<3, 2, 2, 2> ZZZ() { return ExtractComponent<3, 2, 2, 2>(); } 
template <spv::StorageClass C1> void ZZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 2>(_var);}
void ZZZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZ, put = ZZZ)) TExtractType<3, 2, 2, 2> zzz;
__declspec(property(get = ZZZ, put = ZZZ)) TExtractType<3, 2, 2, 2> bbb;
TExtractType<3, 2, 2, 2, 0> ZZZX() { return ExtractComponent<3, 2, 2, 2, 0>(); } 
template <spv::StorageClass C1> void ZZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 2, 0>(_var);}
void ZZZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZX, put = ZZZX)) TExtractType<3, 2, 2, 2, 0> zzz;
__declspec(property(get = ZZZX, put = ZZZX)) TExtractType<3, 2, 2, 2, 0> bbb;
TExtractType<3, 2, 2, 2, 1> ZZZY() { return ExtractComponent<3, 2, 2, 2, 1>(); } 
template <spv::StorageClass C1> void ZZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 2, 1>(_var);}
void ZZZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZY, put = ZZZY)) TExtractType<3, 2, 2, 2, 1> zzz;
__declspec(property(get = ZZZY, put = ZZZY)) TExtractType<3, 2, 2, 2, 1> bbb;
TExtractType<3, 2, 2, 2, 2> ZZZZ() { return ExtractComponent<3, 2, 2, 2, 2>(); } 
template <spv::StorageClass C1> void ZZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 2, 2>(_var);}
void ZZZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZZ, put = ZZZZ)) TExtractType<3, 2, 2, 2, 2> zzz;
__declspec(property(get = ZZZZ, put = ZZZZ)) TExtractType<3, 2, 2, 2, 2> bbb;
TExtractType<3, 2, 2, 2, 3> ZZZW() { return ExtractComponent<3, 2, 2, 2, 3>(); } 
template <spv::StorageClass C1> void ZZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 2, 3>(_var);}
void ZZZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZW, put = ZZZW)) TExtractType<3, 2, 2, 2, 3> zzz;
__declspec(property(get = ZZZW, put = ZZZW)) TExtractType<3, 2, 2, 2, 3> bbb;
TExtractType<3, 2, 2, 3> ZZW() { return ExtractComponent<3, 2, 2, 3>(); } 
template <spv::StorageClass C1> void ZZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 3>(_var);}
void ZZW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZW, put = ZZW)) TExtractType<3, 2, 2, 3> zzw;
__declspec(property(get = ZZW, put = ZZW)) TExtractType<3, 2, 2, 3> bba;
TExtractType<3, 2, 2, 3, 0> ZZWX() { return ExtractComponent<3, 2, 2, 3, 0>(); } 
template <spv::StorageClass C1> void ZZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 3, 0>(_var);}
void ZZWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZWX, put = ZZWX)) TExtractType<3, 2, 2, 3, 0> zzw;
__declspec(property(get = ZZWX, put = ZZWX)) TExtractType<3, 2, 2, 3, 0> bba;
TExtractType<3, 2, 2, 3, 1> ZZWY() { return ExtractComponent<3, 2, 2, 3, 1>(); } 
template <spv::StorageClass C1> void ZZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 3, 1>(_var);}
void ZZWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZWY, put = ZZWY)) TExtractType<3, 2, 2, 3, 1> zzw;
__declspec(property(get = ZZWY, put = ZZWY)) TExtractType<3, 2, 2, 3, 1> bba;
TExtractType<3, 2, 2, 3, 2> ZZWZ() { return ExtractComponent<3, 2, 2, 3, 2>(); } 
template <spv::StorageClass C1> void ZZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 3, 2>(_var);}
void ZZWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZWZ, put = ZZWZ)) TExtractType<3, 2, 2, 3, 2> zzw;
__declspec(property(get = ZZWZ, put = ZZWZ)) TExtractType<3, 2, 2, 3, 2> bba;
TExtractType<3, 2, 2, 3, 3> ZZWW() { return ExtractComponent<3, 2, 2, 3, 3>(); } 
template <spv::StorageClass C1> void ZZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 3, 3>(_var);}
void ZZWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZWW, put = ZZWW)) TExtractType<3, 2, 2, 3, 3> zzw;
__declspec(property(get = ZZWW, put = ZZWW)) TExtractType<3, 2, 2, 3, 3> bba;
TExtractType<2, 2, 3> ZW() { return ExtractComponent<2, 2, 3>(); } 
template <spv::StorageClass C1> void ZW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 2, 3>(_var);}
void ZW(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZW, put = ZW)) TExtractType<2, 2, 3> zw;
__declspec(property(get = ZW, put = ZW)) TExtractType<2, 2, 3> ba;
TExtractType<3, 2, 3, 0> ZWX() { return ExtractComponent<3, 2, 3, 0>(); } 
template <spv::StorageClass C1> void ZWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 0>(_var);}
void ZWX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWX, put = ZWX)) TExtractType<3, 2, 3, 0> zwx;
__declspec(property(get = ZWX, put = ZWX)) TExtractType<3, 2, 3, 0> bar;
TExtractType<3, 2, 3, 0, 0> ZWXX() { return ExtractComponent<3, 2, 3, 0, 0>(); } 
template <spv::StorageClass C1> void ZWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 0, 0>(_var);}
void ZWXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWXX, put = ZWXX)) TExtractType<3, 2, 3, 0, 0> zwx;
__declspec(property(get = ZWXX, put = ZWXX)) TExtractType<3, 2, 3, 0, 0> bar;
TExtractType<3, 2, 3, 0, 1> ZWXY() { return ExtractComponent<3, 2, 3, 0, 1>(); } 
template <spv::StorageClass C1> void ZWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 0, 1>(_var);}
void ZWXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWXY, put = ZWXY)) TExtractType<3, 2, 3, 0, 1> zwx;
__declspec(property(get = ZWXY, put = ZWXY)) TExtractType<3, 2, 3, 0, 1> bar;
TExtractType<3, 2, 3, 0, 2> ZWXZ() { return ExtractComponent<3, 2, 3, 0, 2>(); } 
template <spv::StorageClass C1> void ZWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 0, 2>(_var);}
void ZWXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWXZ, put = ZWXZ)) TExtractType<3, 2, 3, 0, 2> zwx;
__declspec(property(get = ZWXZ, put = ZWXZ)) TExtractType<3, 2, 3, 0, 2> bar;
TExtractType<3, 2, 3, 0, 3> ZWXW() { return ExtractComponent<3, 2, 3, 0, 3>(); } 
template <spv::StorageClass C1> void ZWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 0, 3>(_var);}
void ZWXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWXW, put = ZWXW)) TExtractType<3, 2, 3, 0, 3> zwx;
__declspec(property(get = ZWXW, put = ZWXW)) TExtractType<3, 2, 3, 0, 3> bar;
TExtractType<3, 2, 3, 1> ZWY() { return ExtractComponent<3, 2, 3, 1>(); } 
template <spv::StorageClass C1> void ZWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 1>(_var);}
void ZWY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWY, put = ZWY)) TExtractType<3, 2, 3, 1> zwy;
__declspec(property(get = ZWY, put = ZWY)) TExtractType<3, 2, 3, 1> bag;
TExtractType<3, 2, 3, 1, 0> ZWYX() { return ExtractComponent<3, 2, 3, 1, 0>(); } 
template <spv::StorageClass C1> void ZWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 1, 0>(_var);}
void ZWYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWYX, put = ZWYX)) TExtractType<3, 2, 3, 1, 0> zwy;
__declspec(property(get = ZWYX, put = ZWYX)) TExtractType<3, 2, 3, 1, 0> bag;
TExtractType<3, 2, 3, 1, 1> ZWYY() { return ExtractComponent<3, 2, 3, 1, 1>(); } 
template <spv::StorageClass C1> void ZWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 1, 1>(_var);}
void ZWYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWYY, put = ZWYY)) TExtractType<3, 2, 3, 1, 1> zwy;
__declspec(property(get = ZWYY, put = ZWYY)) TExtractType<3, 2, 3, 1, 1> bag;
TExtractType<3, 2, 3, 1, 2> ZWYZ() { return ExtractComponent<3, 2, 3, 1, 2>(); } 
template <spv::StorageClass C1> void ZWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 1, 2>(_var);}
void ZWYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWYZ, put = ZWYZ)) TExtractType<3, 2, 3, 1, 2> zwy;
__declspec(property(get = ZWYZ, put = ZWYZ)) TExtractType<3, 2, 3, 1, 2> bag;
TExtractType<3, 2, 3, 1, 3> ZWYW() { return ExtractComponent<3, 2, 3, 1, 3>(); } 
template <spv::StorageClass C1> void ZWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 1, 3>(_var);}
void ZWYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWYW, put = ZWYW)) TExtractType<3, 2, 3, 1, 3> zwy;
__declspec(property(get = ZWYW, put = ZWYW)) TExtractType<3, 2, 3, 1, 3> bag;
TExtractType<3, 2, 3, 2> ZWZ() { return ExtractComponent<3, 2, 3, 2>(); } 
template <spv::StorageClass C1> void ZWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 2>(_var);}
void ZWZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZ, put = ZWZ)) TExtractType<3, 2, 3, 2> zwz;
__declspec(property(get = ZWZ, put = ZWZ)) TExtractType<3, 2, 3, 2> bab;
TExtractType<3, 2, 3, 2, 0> ZWZX() { return ExtractComponent<3, 2, 3, 2, 0>(); } 
template <spv::StorageClass C1> void ZWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 2, 0>(_var);}
void ZWZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZX, put = ZWZX)) TExtractType<3, 2, 3, 2, 0> zwz;
__declspec(property(get = ZWZX, put = ZWZX)) TExtractType<3, 2, 3, 2, 0> bab;
TExtractType<3, 2, 3, 2, 1> ZWZY() { return ExtractComponent<3, 2, 3, 2, 1>(); } 
template <spv::StorageClass C1> void ZWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 2, 1>(_var);}
void ZWZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZY, put = ZWZY)) TExtractType<3, 2, 3, 2, 1> zwz;
__declspec(property(get = ZWZY, put = ZWZY)) TExtractType<3, 2, 3, 2, 1> bab;
TExtractType<3, 2, 3, 2, 2> ZWZZ() { return ExtractComponent<3, 2, 3, 2, 2>(); } 
template <spv::StorageClass C1> void ZWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 2, 2>(_var);}
void ZWZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZZ, put = ZWZZ)) TExtractType<3, 2, 3, 2, 2> zwz;
__declspec(property(get = ZWZZ, put = ZWZZ)) TExtractType<3, 2, 3, 2, 2> bab;
TExtractType<3, 2, 3, 2, 3> ZWZW() { return ExtractComponent<3, 2, 3, 2, 3>(); } 
template <spv::StorageClass C1> void ZWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 2, 3>(_var);}
void ZWZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZW, put = ZWZW)) TExtractType<3, 2, 3, 2, 3> zwz;
__declspec(property(get = ZWZW, put = ZWZW)) TExtractType<3, 2, 3, 2, 3> bab;
TExtractType<3, 2, 3, 3> ZWW() { return ExtractComponent<3, 2, 3, 3>(); } 
template <spv::StorageClass C1> void ZWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 3>(_var);}
void ZWW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWW, put = ZWW)) TExtractType<3, 2, 3, 3> zww;
__declspec(property(get = ZWW, put = ZWW)) TExtractType<3, 2, 3, 3> baa;
TExtractType<3, 2, 3, 3, 0> ZWWX() { return ExtractComponent<3, 2, 3, 3, 0>(); } 
template <spv::StorageClass C1> void ZWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 3, 0>(_var);}
void ZWWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWWX, put = ZWWX)) TExtractType<3, 2, 3, 3, 0> zww;
__declspec(property(get = ZWWX, put = ZWWX)) TExtractType<3, 2, 3, 3, 0> baa;
TExtractType<3, 2, 3, 3, 1> ZWWY() { return ExtractComponent<3, 2, 3, 3, 1>(); } 
template <spv::StorageClass C1> void ZWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 3, 1>(_var);}
void ZWWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWWY, put = ZWWY)) TExtractType<3, 2, 3, 3, 1> zww;
__declspec(property(get = ZWWY, put = ZWWY)) TExtractType<3, 2, 3, 3, 1> baa;
TExtractType<3, 2, 3, 3, 2> ZWWZ() { return ExtractComponent<3, 2, 3, 3, 2>(); } 
template <spv::StorageClass C1> void ZWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 3, 2>(_var);}
void ZWWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWWZ, put = ZWWZ)) TExtractType<3, 2, 3, 3, 2> zww;
__declspec(property(get = ZWWZ, put = ZWWZ)) TExtractType<3, 2, 3, 3, 2> baa;
TExtractType<3, 2, 3, 3, 3> ZWWW() { return ExtractComponent<3, 2, 3, 3, 3>(); } 
template <spv::StorageClass C1> void ZWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 3, 3>(_var);}
void ZWWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 2, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWWW, put = ZWWW)) TExtractType<3, 2, 3, 3, 3> zww;
__declspec(property(get = ZWWW, put = ZWWW)) TExtractType<3, 2, 3, 3, 3> baa;
TExtractType<1, 3> W() { return ExtractComponent<1, 3>(); } 
template <spv::StorageClass C1> void W(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) { InsertComponent<1, 3>(_var);}
void W(const vec_type_t<base_type_t<T>, 1>& _var) { InsertComponent<1, 3>(var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = W, put = W)) TExtractType<1, 3> w;
__declspec(property(get = W, put = W)) TExtractType<1, 3> a;
TExtractType<2, 3, 0> WX() { return ExtractComponent<2, 3, 0>(); } 
template <spv::StorageClass C1> void WX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 3, 0>(_var);}
void WX(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WX, put = WX)) TExtractType<2, 3, 0> wx;
__declspec(property(get = WX, put = WX)) TExtractType<2, 3, 0> ar;
TExtractType<3, 3, 0, 0> WXX() { return ExtractComponent<3, 3, 0, 0>(); } 
template <spv::StorageClass C1> void WXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 0>(_var);}
void WXX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXX, put = WXX)) TExtractType<3, 3, 0, 0> wxx;
__declspec(property(get = WXX, put = WXX)) TExtractType<3, 3, 0, 0> arr;
TExtractType<3, 3, 0, 0, 0> WXXX() { return ExtractComponent<3, 3, 0, 0, 0>(); } 
template <spv::StorageClass C1> void WXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 0, 0>(_var);}
void WXXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXXX, put = WXXX)) TExtractType<3, 3, 0, 0, 0> wxx;
__declspec(property(get = WXXX, put = WXXX)) TExtractType<3, 3, 0, 0, 0> arr;
TExtractType<3, 3, 0, 0, 1> WXXY() { return ExtractComponent<3, 3, 0, 0, 1>(); } 
template <spv::StorageClass C1> void WXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 0, 1>(_var);}
void WXXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXXY, put = WXXY)) TExtractType<3, 3, 0, 0, 1> wxx;
__declspec(property(get = WXXY, put = WXXY)) TExtractType<3, 3, 0, 0, 1> arr;
TExtractType<3, 3, 0, 0, 2> WXXZ() { return ExtractComponent<3, 3, 0, 0, 2>(); } 
template <spv::StorageClass C1> void WXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 0, 2>(_var);}
void WXXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXXZ, put = WXXZ)) TExtractType<3, 3, 0, 0, 2> wxx;
__declspec(property(get = WXXZ, put = WXXZ)) TExtractType<3, 3, 0, 0, 2> arr;
TExtractType<3, 3, 0, 0, 3> WXXW() { return ExtractComponent<3, 3, 0, 0, 3>(); } 
template <spv::StorageClass C1> void WXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 0, 3>(_var);}
void WXXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXXW, put = WXXW)) TExtractType<3, 3, 0, 0, 3> wxx;
__declspec(property(get = WXXW, put = WXXW)) TExtractType<3, 3, 0, 0, 3> arr;
TExtractType<3, 3, 0, 1> WXY() { return ExtractComponent<3, 3, 0, 1>(); } 
template <spv::StorageClass C1> void WXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 1>(_var);}
void WXY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXY, put = WXY)) TExtractType<3, 3, 0, 1> wxy;
__declspec(property(get = WXY, put = WXY)) TExtractType<3, 3, 0, 1> arg;
TExtractType<3, 3, 0, 1, 0> WXYX() { return ExtractComponent<3, 3, 0, 1, 0>(); } 
template <spv::StorageClass C1> void WXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 1, 0>(_var);}
void WXYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXYX, put = WXYX)) TExtractType<3, 3, 0, 1, 0> wxy;
__declspec(property(get = WXYX, put = WXYX)) TExtractType<3, 3, 0, 1, 0> arg;
TExtractType<3, 3, 0, 1, 1> WXYY() { return ExtractComponent<3, 3, 0, 1, 1>(); } 
template <spv::StorageClass C1> void WXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 1, 1>(_var);}
void WXYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXYY, put = WXYY)) TExtractType<3, 3, 0, 1, 1> wxy;
__declspec(property(get = WXYY, put = WXYY)) TExtractType<3, 3, 0, 1, 1> arg;
TExtractType<3, 3, 0, 1, 2> WXYZ() { return ExtractComponent<3, 3, 0, 1, 2>(); } 
template <spv::StorageClass C1> void WXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 1, 2>(_var);}
void WXYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXYZ, put = WXYZ)) TExtractType<3, 3, 0, 1, 2> wxy;
__declspec(property(get = WXYZ, put = WXYZ)) TExtractType<3, 3, 0, 1, 2> arg;
TExtractType<3, 3, 0, 1, 3> WXYW() { return ExtractComponent<3, 3, 0, 1, 3>(); } 
template <spv::StorageClass C1> void WXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 1, 3>(_var);}
void WXYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXYW, put = WXYW)) TExtractType<3, 3, 0, 1, 3> wxy;
__declspec(property(get = WXYW, put = WXYW)) TExtractType<3, 3, 0, 1, 3> arg;
TExtractType<3, 3, 0, 2> WXZ() { return ExtractComponent<3, 3, 0, 2>(); } 
template <spv::StorageClass C1> void WXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 2>(_var);}
void WXZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZ, put = WXZ)) TExtractType<3, 3, 0, 2> wxz;
__declspec(property(get = WXZ, put = WXZ)) TExtractType<3, 3, 0, 2> arb;
TExtractType<3, 3, 0, 2, 0> WXZX() { return ExtractComponent<3, 3, 0, 2, 0>(); } 
template <spv::StorageClass C1> void WXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 2, 0>(_var);}
void WXZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZX, put = WXZX)) TExtractType<3, 3, 0, 2, 0> wxz;
__declspec(property(get = WXZX, put = WXZX)) TExtractType<3, 3, 0, 2, 0> arb;
TExtractType<3, 3, 0, 2, 1> WXZY() { return ExtractComponent<3, 3, 0, 2, 1>(); } 
template <spv::StorageClass C1> void WXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 2, 1>(_var);}
void WXZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZY, put = WXZY)) TExtractType<3, 3, 0, 2, 1> wxz;
__declspec(property(get = WXZY, put = WXZY)) TExtractType<3, 3, 0, 2, 1> arb;
TExtractType<3, 3, 0, 2, 2> WXZZ() { return ExtractComponent<3, 3, 0, 2, 2>(); } 
template <spv::StorageClass C1> void WXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 2, 2>(_var);}
void WXZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZZ, put = WXZZ)) TExtractType<3, 3, 0, 2, 2> wxz;
__declspec(property(get = WXZZ, put = WXZZ)) TExtractType<3, 3, 0, 2, 2> arb;
TExtractType<3, 3, 0, 2, 3> WXZW() { return ExtractComponent<3, 3, 0, 2, 3>(); } 
template <spv::StorageClass C1> void WXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 2, 3>(_var);}
void WXZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZW, put = WXZW)) TExtractType<3, 3, 0, 2, 3> wxz;
__declspec(property(get = WXZW, put = WXZW)) TExtractType<3, 3, 0, 2, 3> arb;
TExtractType<3, 3, 0, 3> WXW() { return ExtractComponent<3, 3, 0, 3>(); } 
template <spv::StorageClass C1> void WXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 3>(_var);}
void WXW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXW, put = WXW)) TExtractType<3, 3, 0, 3> wxw;
__declspec(property(get = WXW, put = WXW)) TExtractType<3, 3, 0, 3> ara;
TExtractType<3, 3, 0, 3, 0> WXWX() { return ExtractComponent<3, 3, 0, 3, 0>(); } 
template <spv::StorageClass C1> void WXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 3, 0>(_var);}
void WXWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXWX, put = WXWX)) TExtractType<3, 3, 0, 3, 0> wxw;
__declspec(property(get = WXWX, put = WXWX)) TExtractType<3, 3, 0, 3, 0> ara;
TExtractType<3, 3, 0, 3, 1> WXWY() { return ExtractComponent<3, 3, 0, 3, 1>(); } 
template <spv::StorageClass C1> void WXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 3, 1>(_var);}
void WXWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXWY, put = WXWY)) TExtractType<3, 3, 0, 3, 1> wxw;
__declspec(property(get = WXWY, put = WXWY)) TExtractType<3, 3, 0, 3, 1> ara;
TExtractType<3, 3, 0, 3, 2> WXWZ() { return ExtractComponent<3, 3, 0, 3, 2>(); } 
template <spv::StorageClass C1> void WXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 3, 2>(_var);}
void WXWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXWZ, put = WXWZ)) TExtractType<3, 3, 0, 3, 2> wxw;
__declspec(property(get = WXWZ, put = WXWZ)) TExtractType<3, 3, 0, 3, 2> ara;
TExtractType<3, 3, 0, 3, 3> WXWW() { return ExtractComponent<3, 3, 0, 3, 3>(); } 
template <spv::StorageClass C1> void WXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 3, 3>(_var);}
void WXWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXWW, put = WXWW)) TExtractType<3, 3, 0, 3, 3> wxw;
__declspec(property(get = WXWW, put = WXWW)) TExtractType<3, 3, 0, 3, 3> ara;
TExtractType<2, 3, 1> WY() { return ExtractComponent<2, 3, 1>(); } 
template <spv::StorageClass C1> void WY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 3, 1>(_var);}
void WY(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WY, put = WY)) TExtractType<2, 3, 1> wy;
__declspec(property(get = WY, put = WY)) TExtractType<2, 3, 1> ag;
TExtractType<3, 3, 1, 0> WYX() { return ExtractComponent<3, 3, 1, 0>(); } 
template <spv::StorageClass C1> void WYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 0>(_var);}
void WYX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYX, put = WYX)) TExtractType<3, 3, 1, 0> wyx;
__declspec(property(get = WYX, put = WYX)) TExtractType<3, 3, 1, 0> agr;
TExtractType<3, 3, 1, 0, 0> WYXX() { return ExtractComponent<3, 3, 1, 0, 0>(); } 
template <spv::StorageClass C1> void WYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 0, 0>(_var);}
void WYXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYXX, put = WYXX)) TExtractType<3, 3, 1, 0, 0> wyx;
__declspec(property(get = WYXX, put = WYXX)) TExtractType<3, 3, 1, 0, 0> agr;
TExtractType<3, 3, 1, 0, 1> WYXY() { return ExtractComponent<3, 3, 1, 0, 1>(); } 
template <spv::StorageClass C1> void WYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 0, 1>(_var);}
void WYXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYXY, put = WYXY)) TExtractType<3, 3, 1, 0, 1> wyx;
__declspec(property(get = WYXY, put = WYXY)) TExtractType<3, 3, 1, 0, 1> agr;
TExtractType<3, 3, 1, 0, 2> WYXZ() { return ExtractComponent<3, 3, 1, 0, 2>(); } 
template <spv::StorageClass C1> void WYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 0, 2>(_var);}
void WYXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYXZ, put = WYXZ)) TExtractType<3, 3, 1, 0, 2> wyx;
__declspec(property(get = WYXZ, put = WYXZ)) TExtractType<3, 3, 1, 0, 2> agr;
TExtractType<3, 3, 1, 0, 3> WYXW() { return ExtractComponent<3, 3, 1, 0, 3>(); } 
template <spv::StorageClass C1> void WYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 0, 3>(_var);}
void WYXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYXW, put = WYXW)) TExtractType<3, 3, 1, 0, 3> wyx;
__declspec(property(get = WYXW, put = WYXW)) TExtractType<3, 3, 1, 0, 3> agr;
TExtractType<3, 3, 1, 1> WYY() { return ExtractComponent<3, 3, 1, 1>(); } 
template <spv::StorageClass C1> void WYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 1>(_var);}
void WYY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYY, put = WYY)) TExtractType<3, 3, 1, 1> wyy;
__declspec(property(get = WYY, put = WYY)) TExtractType<3, 3, 1, 1> agg;
TExtractType<3, 3, 1, 1, 0> WYYX() { return ExtractComponent<3, 3, 1, 1, 0>(); } 
template <spv::StorageClass C1> void WYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 1, 0>(_var);}
void WYYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYYX, put = WYYX)) TExtractType<3, 3, 1, 1, 0> wyy;
__declspec(property(get = WYYX, put = WYYX)) TExtractType<3, 3, 1, 1, 0> agg;
TExtractType<3, 3, 1, 1, 1> WYYY() { return ExtractComponent<3, 3, 1, 1, 1>(); } 
template <spv::StorageClass C1> void WYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 1, 1>(_var);}
void WYYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYYY, put = WYYY)) TExtractType<3, 3, 1, 1, 1> wyy;
__declspec(property(get = WYYY, put = WYYY)) TExtractType<3, 3, 1, 1, 1> agg;
TExtractType<3, 3, 1, 1, 2> WYYZ() { return ExtractComponent<3, 3, 1, 1, 2>(); } 
template <spv::StorageClass C1> void WYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 1, 2>(_var);}
void WYYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYYZ, put = WYYZ)) TExtractType<3, 3, 1, 1, 2> wyy;
__declspec(property(get = WYYZ, put = WYYZ)) TExtractType<3, 3, 1, 1, 2> agg;
TExtractType<3, 3, 1, 1, 3> WYYW() { return ExtractComponent<3, 3, 1, 1, 3>(); } 
template <spv::StorageClass C1> void WYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 1, 3>(_var);}
void WYYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYYW, put = WYYW)) TExtractType<3, 3, 1, 1, 3> wyy;
__declspec(property(get = WYYW, put = WYYW)) TExtractType<3, 3, 1, 1, 3> agg;
TExtractType<3, 3, 1, 2> WYZ() { return ExtractComponent<3, 3, 1, 2>(); } 
template <spv::StorageClass C1> void WYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 2>(_var);}
void WYZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZ, put = WYZ)) TExtractType<3, 3, 1, 2> wyz;
__declspec(property(get = WYZ, put = WYZ)) TExtractType<3, 3, 1, 2> agb;
TExtractType<3, 3, 1, 2, 0> WYZX() { return ExtractComponent<3, 3, 1, 2, 0>(); } 
template <spv::StorageClass C1> void WYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 2, 0>(_var);}
void WYZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZX, put = WYZX)) TExtractType<3, 3, 1, 2, 0> wyz;
__declspec(property(get = WYZX, put = WYZX)) TExtractType<3, 3, 1, 2, 0> agb;
TExtractType<3, 3, 1, 2, 1> WYZY() { return ExtractComponent<3, 3, 1, 2, 1>(); } 
template <spv::StorageClass C1> void WYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 2, 1>(_var);}
void WYZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZY, put = WYZY)) TExtractType<3, 3, 1, 2, 1> wyz;
__declspec(property(get = WYZY, put = WYZY)) TExtractType<3, 3, 1, 2, 1> agb;
TExtractType<3, 3, 1, 2, 2> WYZZ() { return ExtractComponent<3, 3, 1, 2, 2>(); } 
template <spv::StorageClass C1> void WYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 2, 2>(_var);}
void WYZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZZ, put = WYZZ)) TExtractType<3, 3, 1, 2, 2> wyz;
__declspec(property(get = WYZZ, put = WYZZ)) TExtractType<3, 3, 1, 2, 2> agb;
TExtractType<3, 3, 1, 2, 3> WYZW() { return ExtractComponent<3, 3, 1, 2, 3>(); } 
template <spv::StorageClass C1> void WYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 2, 3>(_var);}
void WYZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZW, put = WYZW)) TExtractType<3, 3, 1, 2, 3> wyz;
__declspec(property(get = WYZW, put = WYZW)) TExtractType<3, 3, 1, 2, 3> agb;
TExtractType<3, 3, 1, 3> WYW() { return ExtractComponent<3, 3, 1, 3>(); } 
template <spv::StorageClass C1> void WYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 3>(_var);}
void WYW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYW, put = WYW)) TExtractType<3, 3, 1, 3> wyw;
__declspec(property(get = WYW, put = WYW)) TExtractType<3, 3, 1, 3> aga;
TExtractType<3, 3, 1, 3, 0> WYWX() { return ExtractComponent<3, 3, 1, 3, 0>(); } 
template <spv::StorageClass C1> void WYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 3, 0>(_var);}
void WYWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYWX, put = WYWX)) TExtractType<3, 3, 1, 3, 0> wyw;
__declspec(property(get = WYWX, put = WYWX)) TExtractType<3, 3, 1, 3, 0> aga;
TExtractType<3, 3, 1, 3, 1> WYWY() { return ExtractComponent<3, 3, 1, 3, 1>(); } 
template <spv::StorageClass C1> void WYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 3, 1>(_var);}
void WYWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYWY, put = WYWY)) TExtractType<3, 3, 1, 3, 1> wyw;
__declspec(property(get = WYWY, put = WYWY)) TExtractType<3, 3, 1, 3, 1> aga;
TExtractType<3, 3, 1, 3, 2> WYWZ() { return ExtractComponent<3, 3, 1, 3, 2>(); } 
template <spv::StorageClass C1> void WYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 3, 2>(_var);}
void WYWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYWZ, put = WYWZ)) TExtractType<3, 3, 1, 3, 2> wyw;
__declspec(property(get = WYWZ, put = WYWZ)) TExtractType<3, 3, 1, 3, 2> aga;
TExtractType<3, 3, 1, 3, 3> WYWW() { return ExtractComponent<3, 3, 1, 3, 3>(); } 
template <spv::StorageClass C1> void WYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 3, 3>(_var);}
void WYWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYWW, put = WYWW)) TExtractType<3, 3, 1, 3, 3> wyw;
__declspec(property(get = WYWW, put = WYWW)) TExtractType<3, 3, 1, 3, 3> aga;
TExtractType<2, 3, 2> WZ() { return ExtractComponent<2, 3, 2>(); } 
template <spv::StorageClass C1> void WZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 3, 2>(_var);}
void WZ(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZ, put = WZ)) TExtractType<2, 3, 2> wz;
__declspec(property(get = WZ, put = WZ)) TExtractType<2, 3, 2> ab;
TExtractType<3, 3, 2, 0> WZX() { return ExtractComponent<3, 3, 2, 0>(); } 
template <spv::StorageClass C1> void WZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 0>(_var);}
void WZX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZX, put = WZX)) TExtractType<3, 3, 2, 0> wzx;
__declspec(property(get = WZX, put = WZX)) TExtractType<3, 3, 2, 0> abr;
TExtractType<3, 3, 2, 0, 0> WZXX() { return ExtractComponent<3, 3, 2, 0, 0>(); } 
template <spv::StorageClass C1> void WZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 0, 0>(_var);}
void WZXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZXX, put = WZXX)) TExtractType<3, 3, 2, 0, 0> wzx;
__declspec(property(get = WZXX, put = WZXX)) TExtractType<3, 3, 2, 0, 0> abr;
TExtractType<3, 3, 2, 0, 1> WZXY() { return ExtractComponent<3, 3, 2, 0, 1>(); } 
template <spv::StorageClass C1> void WZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 0, 1>(_var);}
void WZXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZXY, put = WZXY)) TExtractType<3, 3, 2, 0, 1> wzx;
__declspec(property(get = WZXY, put = WZXY)) TExtractType<3, 3, 2, 0, 1> abr;
TExtractType<3, 3, 2, 0, 2> WZXZ() { return ExtractComponent<3, 3, 2, 0, 2>(); } 
template <spv::StorageClass C1> void WZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 0, 2>(_var);}
void WZXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZXZ, put = WZXZ)) TExtractType<3, 3, 2, 0, 2> wzx;
__declspec(property(get = WZXZ, put = WZXZ)) TExtractType<3, 3, 2, 0, 2> abr;
TExtractType<3, 3, 2, 0, 3> WZXW() { return ExtractComponent<3, 3, 2, 0, 3>(); } 
template <spv::StorageClass C1> void WZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 0, 3>(_var);}
void WZXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZXW, put = WZXW)) TExtractType<3, 3, 2, 0, 3> wzx;
__declspec(property(get = WZXW, put = WZXW)) TExtractType<3, 3, 2, 0, 3> abr;
TExtractType<3, 3, 2, 1> WZY() { return ExtractComponent<3, 3, 2, 1>(); } 
template <spv::StorageClass C1> void WZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 1>(_var);}
void WZY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZY, put = WZY)) TExtractType<3, 3, 2, 1> wzy;
__declspec(property(get = WZY, put = WZY)) TExtractType<3, 3, 2, 1> abg;
TExtractType<3, 3, 2, 1, 0> WZYX() { return ExtractComponent<3, 3, 2, 1, 0>(); } 
template <spv::StorageClass C1> void WZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 1, 0>(_var);}
void WZYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZYX, put = WZYX)) TExtractType<3, 3, 2, 1, 0> wzy;
__declspec(property(get = WZYX, put = WZYX)) TExtractType<3, 3, 2, 1, 0> abg;
TExtractType<3, 3, 2, 1, 1> WZYY() { return ExtractComponent<3, 3, 2, 1, 1>(); } 
template <spv::StorageClass C1> void WZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 1, 1>(_var);}
void WZYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZYY, put = WZYY)) TExtractType<3, 3, 2, 1, 1> wzy;
__declspec(property(get = WZYY, put = WZYY)) TExtractType<3, 3, 2, 1, 1> abg;
TExtractType<3, 3, 2, 1, 2> WZYZ() { return ExtractComponent<3, 3, 2, 1, 2>(); } 
template <spv::StorageClass C1> void WZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 1, 2>(_var);}
void WZYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZYZ, put = WZYZ)) TExtractType<3, 3, 2, 1, 2> wzy;
__declspec(property(get = WZYZ, put = WZYZ)) TExtractType<3, 3, 2, 1, 2> abg;
TExtractType<3, 3, 2, 1, 3> WZYW() { return ExtractComponent<3, 3, 2, 1, 3>(); } 
template <spv::StorageClass C1> void WZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 1, 3>(_var);}
void WZYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZYW, put = WZYW)) TExtractType<3, 3, 2, 1, 3> wzy;
__declspec(property(get = WZYW, put = WZYW)) TExtractType<3, 3, 2, 1, 3> abg;
TExtractType<3, 3, 2, 2> WZZ() { return ExtractComponent<3, 3, 2, 2>(); } 
template <spv::StorageClass C1> void WZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 2>(_var);}
void WZZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZ, put = WZZ)) TExtractType<3, 3, 2, 2> wzz;
__declspec(property(get = WZZ, put = WZZ)) TExtractType<3, 3, 2, 2> abb;
TExtractType<3, 3, 2, 2, 0> WZZX() { return ExtractComponent<3, 3, 2, 2, 0>(); } 
template <spv::StorageClass C1> void WZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 2, 0>(_var);}
void WZZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZX, put = WZZX)) TExtractType<3, 3, 2, 2, 0> wzz;
__declspec(property(get = WZZX, put = WZZX)) TExtractType<3, 3, 2, 2, 0> abb;
TExtractType<3, 3, 2, 2, 1> WZZY() { return ExtractComponent<3, 3, 2, 2, 1>(); } 
template <spv::StorageClass C1> void WZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 2, 1>(_var);}
void WZZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZY, put = WZZY)) TExtractType<3, 3, 2, 2, 1> wzz;
__declspec(property(get = WZZY, put = WZZY)) TExtractType<3, 3, 2, 2, 1> abb;
TExtractType<3, 3, 2, 2, 2> WZZZ() { return ExtractComponent<3, 3, 2, 2, 2>(); } 
template <spv::StorageClass C1> void WZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 2, 2>(_var);}
void WZZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZZ, put = WZZZ)) TExtractType<3, 3, 2, 2, 2> wzz;
__declspec(property(get = WZZZ, put = WZZZ)) TExtractType<3, 3, 2, 2, 2> abb;
TExtractType<3, 3, 2, 2, 3> WZZW() { return ExtractComponent<3, 3, 2, 2, 3>(); } 
template <spv::StorageClass C1> void WZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 2, 3>(_var);}
void WZZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZW, put = WZZW)) TExtractType<3, 3, 2, 2, 3> wzz;
__declspec(property(get = WZZW, put = WZZW)) TExtractType<3, 3, 2, 2, 3> abb;
TExtractType<3, 3, 2, 3> WZW() { return ExtractComponent<3, 3, 2, 3>(); } 
template <spv::StorageClass C1> void WZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 3>(_var);}
void WZW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZW, put = WZW)) TExtractType<3, 3, 2, 3> wzw;
__declspec(property(get = WZW, put = WZW)) TExtractType<3, 3, 2, 3> aba;
TExtractType<3, 3, 2, 3, 0> WZWX() { return ExtractComponent<3, 3, 2, 3, 0>(); } 
template <spv::StorageClass C1> void WZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 3, 0>(_var);}
void WZWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZWX, put = WZWX)) TExtractType<3, 3, 2, 3, 0> wzw;
__declspec(property(get = WZWX, put = WZWX)) TExtractType<3, 3, 2, 3, 0> aba;
TExtractType<3, 3, 2, 3, 1> WZWY() { return ExtractComponent<3, 3, 2, 3, 1>(); } 
template <spv::StorageClass C1> void WZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 3, 1>(_var);}
void WZWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZWY, put = WZWY)) TExtractType<3, 3, 2, 3, 1> wzw;
__declspec(property(get = WZWY, put = WZWY)) TExtractType<3, 3, 2, 3, 1> aba;
TExtractType<3, 3, 2, 3, 2> WZWZ() { return ExtractComponent<3, 3, 2, 3, 2>(); } 
template <spv::StorageClass C1> void WZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 3, 2>(_var);}
void WZWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZWZ, put = WZWZ)) TExtractType<3, 3, 2, 3, 2> wzw;
__declspec(property(get = WZWZ, put = WZWZ)) TExtractType<3, 3, 2, 3, 2> aba;
TExtractType<3, 3, 2, 3, 3> WZWW() { return ExtractComponent<3, 3, 2, 3, 3>(); } 
template <spv::StorageClass C1> void WZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 3, 3>(_var);}
void WZWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZWW, put = WZWW)) TExtractType<3, 3, 2, 3, 3> wzw;
__declspec(property(get = WZWW, put = WZWW)) TExtractType<3, 3, 2, 3, 3> aba;
TExtractType<2, 3, 3> WW() { return ExtractComponent<2, 3, 3>(); } 
template <spv::StorageClass C1> void WW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 3, 3>(_var);}
void WW(const vec_type_t<base_type_t<T>, 2>& _var) { InsertComponent<2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WW, put = WW)) TExtractType<2, 3, 3> ww;
__declspec(property(get = WW, put = WW)) TExtractType<2, 3, 3> aa;
TExtractType<3, 3, 3, 0> WWX() { return ExtractComponent<3, 3, 3, 0>(); } 
template <spv::StorageClass C1> void WWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 0>(_var);}
void WWX(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWX, put = WWX)) TExtractType<3, 3, 3, 0> wwx;
__declspec(property(get = WWX, put = WWX)) TExtractType<3, 3, 3, 0> aar;
TExtractType<3, 3, 3, 0, 0> WWXX() { return ExtractComponent<3, 3, 3, 0, 0>(); } 
template <spv::StorageClass C1> void WWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 0, 0>(_var);}
void WWXX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWXX, put = WWXX)) TExtractType<3, 3, 3, 0, 0> wwx;
__declspec(property(get = WWXX, put = WWXX)) TExtractType<3, 3, 3, 0, 0> aar;
TExtractType<3, 3, 3, 0, 1> WWXY() { return ExtractComponent<3, 3, 3, 0, 1>(); } 
template <spv::StorageClass C1> void WWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 0, 1>(_var);}
void WWXY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWXY, put = WWXY)) TExtractType<3, 3, 3, 0, 1> wwx;
__declspec(property(get = WWXY, put = WWXY)) TExtractType<3, 3, 3, 0, 1> aar;
TExtractType<3, 3, 3, 0, 2> WWXZ() { return ExtractComponent<3, 3, 3, 0, 2>(); } 
template <spv::StorageClass C1> void WWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 0, 2>(_var);}
void WWXZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWXZ, put = WWXZ)) TExtractType<3, 3, 3, 0, 2> wwx;
__declspec(property(get = WWXZ, put = WWXZ)) TExtractType<3, 3, 3, 0, 2> aar;
TExtractType<3, 3, 3, 0, 3> WWXW() { return ExtractComponent<3, 3, 3, 0, 3>(); } 
template <spv::StorageClass C1> void WWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 0, 3>(_var);}
void WWXW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWXW, put = WWXW)) TExtractType<3, 3, 3, 0, 3> wwx;
__declspec(property(get = WWXW, put = WWXW)) TExtractType<3, 3, 3, 0, 3> aar;
TExtractType<3, 3, 3, 1> WWY() { return ExtractComponent<3, 3, 3, 1>(); } 
template <spv::StorageClass C1> void WWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 1>(_var);}
void WWY(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWY, put = WWY)) TExtractType<3, 3, 3, 1> wwy;
__declspec(property(get = WWY, put = WWY)) TExtractType<3, 3, 3, 1> aag;
TExtractType<3, 3, 3, 1, 0> WWYX() { return ExtractComponent<3, 3, 3, 1, 0>(); } 
template <spv::StorageClass C1> void WWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 1, 0>(_var);}
void WWYX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWYX, put = WWYX)) TExtractType<3, 3, 3, 1, 0> wwy;
__declspec(property(get = WWYX, put = WWYX)) TExtractType<3, 3, 3, 1, 0> aag;
TExtractType<3, 3, 3, 1, 1> WWYY() { return ExtractComponent<3, 3, 3, 1, 1>(); } 
template <spv::StorageClass C1> void WWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 1, 1>(_var);}
void WWYY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWYY, put = WWYY)) TExtractType<3, 3, 3, 1, 1> wwy;
__declspec(property(get = WWYY, put = WWYY)) TExtractType<3, 3, 3, 1, 1> aag;
TExtractType<3, 3, 3, 1, 2> WWYZ() { return ExtractComponent<3, 3, 3, 1, 2>(); } 
template <spv::StorageClass C1> void WWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 1, 2>(_var);}
void WWYZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWYZ, put = WWYZ)) TExtractType<3, 3, 3, 1, 2> wwy;
__declspec(property(get = WWYZ, put = WWYZ)) TExtractType<3, 3, 3, 1, 2> aag;
TExtractType<3, 3, 3, 1, 3> WWYW() { return ExtractComponent<3, 3, 3, 1, 3>(); } 
template <spv::StorageClass C1> void WWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 1, 3>(_var);}
void WWYW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWYW, put = WWYW)) TExtractType<3, 3, 3, 1, 3> wwy;
__declspec(property(get = WWYW, put = WWYW)) TExtractType<3, 3, 3, 1, 3> aag;
TExtractType<3, 3, 3, 2> WWZ() { return ExtractComponent<3, 3, 3, 2>(); } 
template <spv::StorageClass C1> void WWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 2>(_var);}
void WWZ(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZ, put = WWZ)) TExtractType<3, 3, 3, 2> wwz;
__declspec(property(get = WWZ, put = WWZ)) TExtractType<3, 3, 3, 2> aab;
TExtractType<3, 3, 3, 2, 0> WWZX() { return ExtractComponent<3, 3, 3, 2, 0>(); } 
template <spv::StorageClass C1> void WWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 2, 0>(_var);}
void WWZX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZX, put = WWZX)) TExtractType<3, 3, 3, 2, 0> wwz;
__declspec(property(get = WWZX, put = WWZX)) TExtractType<3, 3, 3, 2, 0> aab;
TExtractType<3, 3, 3, 2, 1> WWZY() { return ExtractComponent<3, 3, 3, 2, 1>(); } 
template <spv::StorageClass C1> void WWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 2, 1>(_var);}
void WWZY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZY, put = WWZY)) TExtractType<3, 3, 3, 2, 1> wwz;
__declspec(property(get = WWZY, put = WWZY)) TExtractType<3, 3, 3, 2, 1> aab;
TExtractType<3, 3, 3, 2, 2> WWZZ() { return ExtractComponent<3, 3, 3, 2, 2>(); } 
template <spv::StorageClass C1> void WWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 2, 2>(_var);}
void WWZZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZZ, put = WWZZ)) TExtractType<3, 3, 3, 2, 2> wwz;
__declspec(property(get = WWZZ, put = WWZZ)) TExtractType<3, 3, 3, 2, 2> aab;
TExtractType<3, 3, 3, 2, 3> WWZW() { return ExtractComponent<3, 3, 3, 2, 3>(); } 
template <spv::StorageClass C1> void WWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 2, 3>(_var);}
void WWZW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZW, put = WWZW)) TExtractType<3, 3, 3, 2, 3> wwz;
__declspec(property(get = WWZW, put = WWZW)) TExtractType<3, 3, 3, 2, 3> aab;
TExtractType<3, 3, 3, 3> WWW() { return ExtractComponent<3, 3, 3, 3>(); } 
template <spv::StorageClass C1> void WWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 3>(_var);}
void WWW(const vec_type_t<base_type_t<T>, 3>& _var) { InsertComponent<3, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWW, put = WWW)) TExtractType<3, 3, 3, 3> www;
__declspec(property(get = WWW, put = WWW)) TExtractType<3, 3, 3, 3> aaa;
TExtractType<3, 3, 3, 3, 0> WWWX() { return ExtractComponent<3, 3, 3, 3, 0>(); } 
template <spv::StorageClass C1> void WWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 3, 0>(_var);}
void WWWX(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWWX, put = WWWX)) TExtractType<3, 3, 3, 3, 0> www;
__declspec(property(get = WWWX, put = WWWX)) TExtractType<3, 3, 3, 3, 0> aaa;
TExtractType<3, 3, 3, 3, 1> WWWY() { return ExtractComponent<3, 3, 3, 3, 1>(); } 
template <spv::StorageClass C1> void WWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 3, 1>(_var);}
void WWWY(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWWY, put = WWWY)) TExtractType<3, 3, 3, 3, 1> www;
__declspec(property(get = WWWY, put = WWWY)) TExtractType<3, 3, 3, 3, 1> aaa;
TExtractType<3, 3, 3, 3, 2> WWWZ() { return ExtractComponent<3, 3, 3, 3, 2>(); } 
template <spv::StorageClass C1> void WWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 3, 2>(_var);}
void WWWZ(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWWZ, put = WWWZ)) TExtractType<3, 3, 3, 3, 2> www;
__declspec(property(get = WWWZ, put = WWWZ)) TExtractType<3, 3, 3, 3, 2> aaa;
TExtractType<3, 3, 3, 3, 3> WWWW() { return ExtractComponent<3, 3, 3, 3, 3>(); } 
template <spv::StorageClass C1> void WWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 3, 3>(_var);}
void WWWW(const vec_type_t<base_type_t<T>, 4>& _var) { InsertComponent<3, 3, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWWW, put = WWWW)) TExtractType<3, 3, 3, 3, 3> www;
__declspec(property(get = WWWW, put = WWWW)) TExtractType<3, 3, 3, 3, 3> aaa;
#endif // !TRACY_SPIRVVECTORCOMPONENTACCESS_H
