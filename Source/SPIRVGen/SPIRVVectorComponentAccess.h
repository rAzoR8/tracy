#ifndef TRACY_SPIRVVECTORCOMPONENTACCESS_H
#define TRACY_SPIRVVECTORCOMPONENTACCESS_H
var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction> X() { return ExtractComponent<1, 0>(); } 
template <spv::StorageClass C1> void X(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) { InsertComponent<1, 0>(_var); } 
__declspec(property(get = X, put = X)) var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction> x;
__declspec(property(get = X, put = X)) var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction> r;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> XX() { return ExtractComponent<2, 0, 0>(); } 
template <spv::StorageClass C1> void XX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 0, 0>(_var); } 
__declspec(property(get = XX, put = XX)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> xx;
__declspec(property(get = XX, put = XX)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> rr;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XXX() { return ExtractComponent<3, 0, 0, 0>(); } 
template <spv::StorageClass C1> void XXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 0>(_var); } 
__declspec(property(get = XXX, put = XXX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xxx;
__declspec(property(get = XXX, put = XXX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rrr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXXX() { return ExtractComponent<4, 0, 0, 0, 0>(); } 
template <spv::StorageClass C1> void XXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 0, 0>(_var); } 
__declspec(property(get = XXXX, put = XXXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxxx;
__declspec(property(get = XXXX, put = XXXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrrr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXXY() { return ExtractComponent<4, 0, 0, 0, 1>(); } 
template <spv::StorageClass C1> void XXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 0, 1>(_var); } 
__declspec(property(get = XXXY, put = XXXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxxy;
__declspec(property(get = XXXY, put = XXXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrrg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXXZ() { return ExtractComponent<4, 0, 0, 0, 2>(); } 
template <spv::StorageClass C1> void XXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 0, 2>(_var); } 
__declspec(property(get = XXXZ, put = XXXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxxz;
__declspec(property(get = XXXZ, put = XXXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrrb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXXW() { return ExtractComponent<4, 0, 0, 0, 3>(); } 
template <spv::StorageClass C1> void XXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 0, 3>(_var); } 
__declspec(property(get = XXXW, put = XXXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxxw;
__declspec(property(get = XXXW, put = XXXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrra;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XXY() { return ExtractComponent<3, 0, 0, 1>(); } 
template <spv::StorageClass C1> void XXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 1>(_var); } 
__declspec(property(get = XXY, put = XXY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xxy;
__declspec(property(get = XXY, put = XXY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rrg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXYX() { return ExtractComponent<4, 0, 0, 1, 0>(); } 
template <spv::StorageClass C1> void XXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 1, 0>(_var); } 
__declspec(property(get = XXYX, put = XXYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxyx;
__declspec(property(get = XXYX, put = XXYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrgr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXYY() { return ExtractComponent<4, 0, 0, 1, 1>(); } 
template <spv::StorageClass C1> void XXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 1, 1>(_var); } 
__declspec(property(get = XXYY, put = XXYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxyy;
__declspec(property(get = XXYY, put = XXYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrgg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXYZ() { return ExtractComponent<4, 0, 0, 1, 2>(); } 
template <spv::StorageClass C1> void XXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 1, 2>(_var); } 
__declspec(property(get = XXYZ, put = XXYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxyz;
__declspec(property(get = XXYZ, put = XXYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrgb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXYW() { return ExtractComponent<4, 0, 0, 1, 3>(); } 
template <spv::StorageClass C1> void XXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 1, 3>(_var); } 
__declspec(property(get = XXYW, put = XXYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxyw;
__declspec(property(get = XXYW, put = XXYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XXZ() { return ExtractComponent<3, 0, 0, 2>(); } 
template <spv::StorageClass C1> void XXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 2>(_var); } 
__declspec(property(get = XXZ, put = XXZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xxz;
__declspec(property(get = XXZ, put = XXZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rrb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXZX() { return ExtractComponent<4, 0, 0, 2, 0>(); } 
template <spv::StorageClass C1> void XXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 2, 0>(_var); } 
__declspec(property(get = XXZX, put = XXZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxzx;
__declspec(property(get = XXZX, put = XXZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXZY() { return ExtractComponent<4, 0, 0, 2, 1>(); } 
template <spv::StorageClass C1> void XXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 2, 1>(_var); } 
__declspec(property(get = XXZY, put = XXZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxzy;
__declspec(property(get = XXZY, put = XXZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXZZ() { return ExtractComponent<4, 0, 0, 2, 2>(); } 
template <spv::StorageClass C1> void XXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 2, 2>(_var); } 
__declspec(property(get = XXZZ, put = XXZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxzz;
__declspec(property(get = XXZZ, put = XXZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXZW() { return ExtractComponent<4, 0, 0, 2, 3>(); } 
template <spv::StorageClass C1> void XXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 2, 3>(_var); } 
__declspec(property(get = XXZW, put = XXZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxzw;
__declspec(property(get = XXZW, put = XXZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XXW() { return ExtractComponent<3, 0, 0, 3>(); } 
template <spv::StorageClass C1> void XXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 0, 3>(_var); } 
__declspec(property(get = XXW, put = XXW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xxw;
__declspec(property(get = XXW, put = XXW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rra;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXWX() { return ExtractComponent<4, 0, 0, 3, 0>(); } 
template <spv::StorageClass C1> void XXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 3, 0>(_var); } 
__declspec(property(get = XXWX, put = XXWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxwx;
__declspec(property(get = XXWX, put = XXWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXWY() { return ExtractComponent<4, 0, 0, 3, 1>(); } 
template <spv::StorageClass C1> void XXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 3, 1>(_var); } 
__declspec(property(get = XXWY, put = XXWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxwy;
__declspec(property(get = XXWY, put = XXWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXWZ() { return ExtractComponent<4, 0, 0, 3, 2>(); } 
template <spv::StorageClass C1> void XXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 3, 2>(_var); } 
__declspec(property(get = XXWZ, put = XXWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxwz;
__declspec(property(get = XXWZ, put = XXWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rrab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XXWW() { return ExtractComponent<4, 0, 0, 3, 3>(); } 
template <spv::StorageClass C1> void XXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 0, 3, 3>(_var); } 
__declspec(property(get = XXWW, put = XXWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xxww;
__declspec(property(get = XXWW, put = XXWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rraa;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> XY() { return ExtractComponent<2, 0, 1>(); } 
template <spv::StorageClass C1> void XY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 0, 1>(_var); } 
__declspec(property(get = XY, put = XY)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> xy;
__declspec(property(get = XY, put = XY)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> rg;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XYX() { return ExtractComponent<3, 0, 1, 0>(); } 
template <spv::StorageClass C1> void XYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 0>(_var); } 
__declspec(property(get = XYX, put = XYX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xyx;
__declspec(property(get = XYX, put = XYX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rgr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYXX() { return ExtractComponent<4, 0, 1, 0, 0>(); } 
template <spv::StorageClass C1> void XYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 0, 0>(_var); } 
__declspec(property(get = XYXX, put = XYXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xyxx;
__declspec(property(get = XYXX, put = XYXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rgrr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYXY() { return ExtractComponent<4, 0, 1, 0, 1>(); } 
template <spv::StorageClass C1> void XYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 0, 1>(_var); } 
__declspec(property(get = XYXY, put = XYXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xyxy;
__declspec(property(get = XYXY, put = XYXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rgrg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYXZ() { return ExtractComponent<4, 0, 1, 0, 2>(); } 
template <spv::StorageClass C1> void XYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 0, 2>(_var); } 
__declspec(property(get = XYXZ, put = XYXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xyxz;
__declspec(property(get = XYXZ, put = XYXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rgrb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYXW() { return ExtractComponent<4, 0, 1, 0, 3>(); } 
template <spv::StorageClass C1> void XYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 0, 3>(_var); } 
__declspec(property(get = XYXW, put = XYXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xyxw;
__declspec(property(get = XYXW, put = XYXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rgra;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XYY() { return ExtractComponent<3, 0, 1, 1>(); } 
template <spv::StorageClass C1> void XYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 1>(_var); } 
__declspec(property(get = XYY, put = XYY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xyy;
__declspec(property(get = XYY, put = XYY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rgg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYYX() { return ExtractComponent<4, 0, 1, 1, 0>(); } 
template <spv::StorageClass C1> void XYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 1, 0>(_var); } 
__declspec(property(get = XYYX, put = XYYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xyyx;
__declspec(property(get = XYYX, put = XYYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rggr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYYY() { return ExtractComponent<4, 0, 1, 1, 1>(); } 
template <spv::StorageClass C1> void XYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 1, 1>(_var); } 
__declspec(property(get = XYYY, put = XYYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xyyy;
__declspec(property(get = XYYY, put = XYYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rggg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYYZ() { return ExtractComponent<4, 0, 1, 1, 2>(); } 
template <spv::StorageClass C1> void XYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 1, 2>(_var); } 
__declspec(property(get = XYYZ, put = XYYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xyyz;
__declspec(property(get = XYYZ, put = XYYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rggb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYYW() { return ExtractComponent<4, 0, 1, 1, 3>(); } 
template <spv::StorageClass C1> void XYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 1, 3>(_var); } 
__declspec(property(get = XYYW, put = XYYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xyyw;
__declspec(property(get = XYYW, put = XYYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rgga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XYZ() { return ExtractComponent<3, 0, 1, 2>(); } 
template <spv::StorageClass C1> void XYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 2>(_var); } 
__declspec(property(get = XYZ, put = XYZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xyz;
__declspec(property(get = XYZ, put = XYZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rgb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYZX() { return ExtractComponent<4, 0, 1, 2, 0>(); } 
template <spv::StorageClass C1> void XYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 2, 0>(_var); } 
__declspec(property(get = XYZX, put = XYZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xyzx;
__declspec(property(get = XYZX, put = XYZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rgbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYZY() { return ExtractComponent<4, 0, 1, 2, 1>(); } 
template <spv::StorageClass C1> void XYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 2, 1>(_var); } 
__declspec(property(get = XYZY, put = XYZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xyzy;
__declspec(property(get = XYZY, put = XYZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rgbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYZZ() { return ExtractComponent<4, 0, 1, 2, 2>(); } 
template <spv::StorageClass C1> void XYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 2, 2>(_var); } 
__declspec(property(get = XYZZ, put = XYZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xyzz;
__declspec(property(get = XYZZ, put = XYZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rgbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYZW() { return ExtractComponent<4, 0, 1, 2, 3>(); } 
template <spv::StorageClass C1> void XYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 2, 3>(_var); } 
__declspec(property(get = XYZW, put = XYZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xyzw;
__declspec(property(get = XYZW, put = XYZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rgba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XYW() { return ExtractComponent<3, 0, 1, 3>(); } 
template <spv::StorageClass C1> void XYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 1, 3>(_var); } 
__declspec(property(get = XYW, put = XYW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xyw;
__declspec(property(get = XYW, put = XYW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rga;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYWX() { return ExtractComponent<4, 0, 1, 3, 0>(); } 
template <spv::StorageClass C1> void XYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 3, 0>(_var); } 
__declspec(property(get = XYWX, put = XYWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xywx;
__declspec(property(get = XYWX, put = XYWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rgar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYWY() { return ExtractComponent<4, 0, 1, 3, 1>(); } 
template <spv::StorageClass C1> void XYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 3, 1>(_var); } 
__declspec(property(get = XYWY, put = XYWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xywy;
__declspec(property(get = XYWY, put = XYWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rgag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYWZ() { return ExtractComponent<4, 0, 1, 3, 2>(); } 
template <spv::StorageClass C1> void XYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 3, 2>(_var); } 
__declspec(property(get = XYWZ, put = XYWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xywz;
__declspec(property(get = XYWZ, put = XYWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rgab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XYWW() { return ExtractComponent<4, 0, 1, 3, 3>(); } 
template <spv::StorageClass C1> void XYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 1, 3, 3>(_var); } 
__declspec(property(get = XYWW, put = XYWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xyww;
__declspec(property(get = XYWW, put = XYWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rgaa;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> XZ() { return ExtractComponent<2, 0, 2>(); } 
template <spv::StorageClass C1> void XZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 0, 2>(_var); } 
__declspec(property(get = XZ, put = XZ)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> xz;
__declspec(property(get = XZ, put = XZ)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> rb;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XZX() { return ExtractComponent<3, 0, 2, 0>(); } 
template <spv::StorageClass C1> void XZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 0>(_var); } 
__declspec(property(get = XZX, put = XZX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xzx;
__declspec(property(get = XZX, put = XZX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZXX() { return ExtractComponent<4, 0, 2, 0, 0>(); } 
template <spv::StorageClass C1> void XZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 0, 0>(_var); } 
__declspec(property(get = XZXX, put = XZXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzxx;
__declspec(property(get = XZXX, put = XZXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbrr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZXY() { return ExtractComponent<4, 0, 2, 0, 1>(); } 
template <spv::StorageClass C1> void XZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 0, 1>(_var); } 
__declspec(property(get = XZXY, put = XZXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzxy;
__declspec(property(get = XZXY, put = XZXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbrg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZXZ() { return ExtractComponent<4, 0, 2, 0, 2>(); } 
template <spv::StorageClass C1> void XZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 0, 2>(_var); } 
__declspec(property(get = XZXZ, put = XZXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzxz;
__declspec(property(get = XZXZ, put = XZXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbrb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZXW() { return ExtractComponent<4, 0, 2, 0, 3>(); } 
template <spv::StorageClass C1> void XZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 0, 3>(_var); } 
__declspec(property(get = XZXW, put = XZXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzxw;
__declspec(property(get = XZXW, put = XZXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbra;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XZY() { return ExtractComponent<3, 0, 2, 1>(); } 
template <spv::StorageClass C1> void XZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 1>(_var); } 
__declspec(property(get = XZY, put = XZY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xzy;
__declspec(property(get = XZY, put = XZY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZYX() { return ExtractComponent<4, 0, 2, 1, 0>(); } 
template <spv::StorageClass C1> void XZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 1, 0>(_var); } 
__declspec(property(get = XZYX, put = XZYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzyx;
__declspec(property(get = XZYX, put = XZYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbgr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZYY() { return ExtractComponent<4, 0, 2, 1, 1>(); } 
template <spv::StorageClass C1> void XZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 1, 1>(_var); } 
__declspec(property(get = XZYY, put = XZYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzyy;
__declspec(property(get = XZYY, put = XZYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbgg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZYZ() { return ExtractComponent<4, 0, 2, 1, 2>(); } 
template <spv::StorageClass C1> void XZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 1, 2>(_var); } 
__declspec(property(get = XZYZ, put = XZYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzyz;
__declspec(property(get = XZYZ, put = XZYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbgb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZYW() { return ExtractComponent<4, 0, 2, 1, 3>(); } 
template <spv::StorageClass C1> void XZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 1, 3>(_var); } 
__declspec(property(get = XZYW, put = XZYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzyw;
__declspec(property(get = XZYW, put = XZYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XZZ() { return ExtractComponent<3, 0, 2, 2>(); } 
template <spv::StorageClass C1> void XZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 2>(_var); } 
__declspec(property(get = XZZ, put = XZZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xzz;
__declspec(property(get = XZZ, put = XZZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZZX() { return ExtractComponent<4, 0, 2, 2, 0>(); } 
template <spv::StorageClass C1> void XZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 2, 0>(_var); } 
__declspec(property(get = XZZX, put = XZZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzzx;
__declspec(property(get = XZZX, put = XZZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZZY() { return ExtractComponent<4, 0, 2, 2, 1>(); } 
template <spv::StorageClass C1> void XZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 2, 1>(_var); } 
__declspec(property(get = XZZY, put = XZZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzzy;
__declspec(property(get = XZZY, put = XZZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZZZ() { return ExtractComponent<4, 0, 2, 2, 2>(); } 
template <spv::StorageClass C1> void XZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 2, 2>(_var); } 
__declspec(property(get = XZZZ, put = XZZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzzz;
__declspec(property(get = XZZZ, put = XZZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZZW() { return ExtractComponent<4, 0, 2, 2, 3>(); } 
template <spv::StorageClass C1> void XZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 2, 3>(_var); } 
__declspec(property(get = XZZW, put = XZZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzzw;
__declspec(property(get = XZZW, put = XZZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XZW() { return ExtractComponent<3, 0, 2, 3>(); } 
template <spv::StorageClass C1> void XZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 2, 3>(_var); } 
__declspec(property(get = XZW, put = XZW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xzw;
__declspec(property(get = XZW, put = XZW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rba;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZWX() { return ExtractComponent<4, 0, 2, 3, 0>(); } 
template <spv::StorageClass C1> void XZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 3, 0>(_var); } 
__declspec(property(get = XZWX, put = XZWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzwx;
__declspec(property(get = XZWX, put = XZWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZWY() { return ExtractComponent<4, 0, 2, 3, 1>(); } 
template <spv::StorageClass C1> void XZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 3, 1>(_var); } 
__declspec(property(get = XZWY, put = XZWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzwy;
__declspec(property(get = XZWY, put = XZWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZWZ() { return ExtractComponent<4, 0, 2, 3, 2>(); } 
template <spv::StorageClass C1> void XZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 3, 2>(_var); } 
__declspec(property(get = XZWZ, put = XZWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzwz;
__declspec(property(get = XZWZ, put = XZWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XZWW() { return ExtractComponent<4, 0, 2, 3, 3>(); } 
template <spv::StorageClass C1> void XZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 2, 3, 3>(_var); } 
__declspec(property(get = XZWW, put = XZWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xzww;
__declspec(property(get = XZWW, put = XZWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rbaa;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> XW() { return ExtractComponent<2, 0, 3>(); } 
template <spv::StorageClass C1> void XW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 0, 3>(_var); } 
__declspec(property(get = XW, put = XW)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> xw;
__declspec(property(get = XW, put = XW)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> ra;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XWX() { return ExtractComponent<3, 0, 3, 0>(); } 
template <spv::StorageClass C1> void XWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 0>(_var); } 
__declspec(property(get = XWX, put = XWX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xwx;
__declspec(property(get = XWX, put = XWX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWXX() { return ExtractComponent<4, 0, 3, 0, 0>(); } 
template <spv::StorageClass C1> void XWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 0, 0>(_var); } 
__declspec(property(get = XWXX, put = XWXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwxx;
__declspec(property(get = XWXX, put = XWXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rarr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWXY() { return ExtractComponent<4, 0, 3, 0, 1>(); } 
template <spv::StorageClass C1> void XWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 0, 1>(_var); } 
__declspec(property(get = XWXY, put = XWXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwxy;
__declspec(property(get = XWXY, put = XWXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rarg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWXZ() { return ExtractComponent<4, 0, 3, 0, 2>(); } 
template <spv::StorageClass C1> void XWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 0, 2>(_var); } 
__declspec(property(get = XWXZ, put = XWXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwxz;
__declspec(property(get = XWXZ, put = XWXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rarb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWXW() { return ExtractComponent<4, 0, 3, 0, 3>(); } 
template <spv::StorageClass C1> void XWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 0, 3>(_var); } 
__declspec(property(get = XWXW, put = XWXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwxw;
__declspec(property(get = XWXW, put = XWXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rara;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XWY() { return ExtractComponent<3, 0, 3, 1>(); } 
template <spv::StorageClass C1> void XWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 1>(_var); } 
__declspec(property(get = XWY, put = XWY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xwy;
__declspec(property(get = XWY, put = XWY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWYX() { return ExtractComponent<4, 0, 3, 1, 0>(); } 
template <spv::StorageClass C1> void XWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 1, 0>(_var); } 
__declspec(property(get = XWYX, put = XWYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwyx;
__declspec(property(get = XWYX, put = XWYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ragr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWYY() { return ExtractComponent<4, 0, 3, 1, 1>(); } 
template <spv::StorageClass C1> void XWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 1, 1>(_var); } 
__declspec(property(get = XWYY, put = XWYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwyy;
__declspec(property(get = XWYY, put = XWYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ragg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWYZ() { return ExtractComponent<4, 0, 3, 1, 2>(); } 
template <spv::StorageClass C1> void XWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 1, 2>(_var); } 
__declspec(property(get = XWYZ, put = XWYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwyz;
__declspec(property(get = XWYZ, put = XWYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ragb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWYW() { return ExtractComponent<4, 0, 3, 1, 3>(); } 
template <spv::StorageClass C1> void XWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 1, 3>(_var); } 
__declspec(property(get = XWYW, put = XWYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwyw;
__declspec(property(get = XWYW, put = XWYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> raga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XWZ() { return ExtractComponent<3, 0, 3, 2>(); } 
template <spv::StorageClass C1> void XWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 2>(_var); } 
__declspec(property(get = XWZ, put = XWZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xwz;
__declspec(property(get = XWZ, put = XWZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> rab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWZX() { return ExtractComponent<4, 0, 3, 2, 0>(); } 
template <spv::StorageClass C1> void XWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 2, 0>(_var); } 
__declspec(property(get = XWZX, put = XWZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwzx;
__declspec(property(get = XWZX, put = XWZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rabr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWZY() { return ExtractComponent<4, 0, 3, 2, 1>(); } 
template <spv::StorageClass C1> void XWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 2, 1>(_var); } 
__declspec(property(get = XWZY, put = XWZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwzy;
__declspec(property(get = XWZY, put = XWZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rabg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWZZ() { return ExtractComponent<4, 0, 3, 2, 2>(); } 
template <spv::StorageClass C1> void XWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 2, 2>(_var); } 
__declspec(property(get = XWZZ, put = XWZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwzz;
__declspec(property(get = XWZZ, put = XWZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> rabb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWZW() { return ExtractComponent<4, 0, 3, 2, 3>(); } 
template <spv::StorageClass C1> void XWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 2, 3>(_var); } 
__declspec(property(get = XWZW, put = XWZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwzw;
__declspec(property(get = XWZW, put = XWZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> raba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> XWW() { return ExtractComponent<3, 0, 3, 3>(); } 
template <spv::StorageClass C1> void XWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 0, 3, 3>(_var); } 
__declspec(property(get = XWW, put = XWW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> xww;
__declspec(property(get = XWW, put = XWW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> raa;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWWX() { return ExtractComponent<4, 0, 3, 3, 0>(); } 
template <spv::StorageClass C1> void XWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 3, 0>(_var); } 
__declspec(property(get = XWWX, put = XWWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwwx;
__declspec(property(get = XWWX, put = XWWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> raar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWWY() { return ExtractComponent<4, 0, 3, 3, 1>(); } 
template <spv::StorageClass C1> void XWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 3, 1>(_var); } 
__declspec(property(get = XWWY, put = XWWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwwy;
__declspec(property(get = XWWY, put = XWWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> raag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWWZ() { return ExtractComponent<4, 0, 3, 3, 2>(); } 
template <spv::StorageClass C1> void XWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 3, 2>(_var); } 
__declspec(property(get = XWWZ, put = XWWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwwz;
__declspec(property(get = XWWZ, put = XWWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> raab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> XWWW() { return ExtractComponent<4, 0, 3, 3, 3>(); } 
template <spv::StorageClass C1> void XWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 0, 3, 3, 3>(_var); } 
__declspec(property(get = XWWW, put = XWWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> xwww;
__declspec(property(get = XWWW, put = XWWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> raaa;
var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction> Y() { return ExtractComponent<1, 1>(); } 
template <spv::StorageClass C1> void Y(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) { InsertComponent<1, 1>(_var); } 
__declspec(property(get = Y, put = Y)) var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction> y;
__declspec(property(get = Y, put = Y)) var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction> g;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> YX() { return ExtractComponent<2, 1, 0>(); } 
template <spv::StorageClass C1> void YX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 1, 0>(_var); } 
__declspec(property(get = YX, put = YX)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> yx;
__declspec(property(get = YX, put = YX)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> gr;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YXX() { return ExtractComponent<3, 1, 0, 0>(); } 
template <spv::StorageClass C1> void YXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 0>(_var); } 
__declspec(property(get = YXX, put = YXX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> yxx;
__declspec(property(get = YXX, put = YXX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> grr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXXX() { return ExtractComponent<4, 1, 0, 0, 0>(); } 
template <spv::StorageClass C1> void YXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 0, 0>(_var); } 
__declspec(property(get = YXXX, put = YXXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxxx;
__declspec(property(get = YXXX, put = YXXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grrr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXXY() { return ExtractComponent<4, 1, 0, 0, 1>(); } 
template <spv::StorageClass C1> void YXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 0, 1>(_var); } 
__declspec(property(get = YXXY, put = YXXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxxy;
__declspec(property(get = YXXY, put = YXXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grrg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXXZ() { return ExtractComponent<4, 1, 0, 0, 2>(); } 
template <spv::StorageClass C1> void YXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 0, 2>(_var); } 
__declspec(property(get = YXXZ, put = YXXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxxz;
__declspec(property(get = YXXZ, put = YXXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grrb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXXW() { return ExtractComponent<4, 1, 0, 0, 3>(); } 
template <spv::StorageClass C1> void YXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 0, 3>(_var); } 
__declspec(property(get = YXXW, put = YXXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxxw;
__declspec(property(get = YXXW, put = YXXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grra;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YXY() { return ExtractComponent<3, 1, 0, 1>(); } 
template <spv::StorageClass C1> void YXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 1>(_var); } 
__declspec(property(get = YXY, put = YXY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> yxy;
__declspec(property(get = YXY, put = YXY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> grg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXYX() { return ExtractComponent<4, 1, 0, 1, 0>(); } 
template <spv::StorageClass C1> void YXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 1, 0>(_var); } 
__declspec(property(get = YXYX, put = YXYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxyx;
__declspec(property(get = YXYX, put = YXYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grgr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXYY() { return ExtractComponent<4, 1, 0, 1, 1>(); } 
template <spv::StorageClass C1> void YXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 1, 1>(_var); } 
__declspec(property(get = YXYY, put = YXYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxyy;
__declspec(property(get = YXYY, put = YXYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grgg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXYZ() { return ExtractComponent<4, 1, 0, 1, 2>(); } 
template <spv::StorageClass C1> void YXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 1, 2>(_var); } 
__declspec(property(get = YXYZ, put = YXYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxyz;
__declspec(property(get = YXYZ, put = YXYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grgb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXYW() { return ExtractComponent<4, 1, 0, 1, 3>(); } 
template <spv::StorageClass C1> void YXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 1, 3>(_var); } 
__declspec(property(get = YXYW, put = YXYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxyw;
__declspec(property(get = YXYW, put = YXYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YXZ() { return ExtractComponent<3, 1, 0, 2>(); } 
template <spv::StorageClass C1> void YXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 2>(_var); } 
__declspec(property(get = YXZ, put = YXZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> yxz;
__declspec(property(get = YXZ, put = YXZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> grb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXZX() { return ExtractComponent<4, 1, 0, 2, 0>(); } 
template <spv::StorageClass C1> void YXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 2, 0>(_var); } 
__declspec(property(get = YXZX, put = YXZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxzx;
__declspec(property(get = YXZX, put = YXZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXZY() { return ExtractComponent<4, 1, 0, 2, 1>(); } 
template <spv::StorageClass C1> void YXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 2, 1>(_var); } 
__declspec(property(get = YXZY, put = YXZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxzy;
__declspec(property(get = YXZY, put = YXZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXZZ() { return ExtractComponent<4, 1, 0, 2, 2>(); } 
template <spv::StorageClass C1> void YXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 2, 2>(_var); } 
__declspec(property(get = YXZZ, put = YXZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxzz;
__declspec(property(get = YXZZ, put = YXZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXZW() { return ExtractComponent<4, 1, 0, 2, 3>(); } 
template <spv::StorageClass C1> void YXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 2, 3>(_var); } 
__declspec(property(get = YXZW, put = YXZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxzw;
__declspec(property(get = YXZW, put = YXZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YXW() { return ExtractComponent<3, 1, 0, 3>(); } 
template <spv::StorageClass C1> void YXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 0, 3>(_var); } 
__declspec(property(get = YXW, put = YXW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> yxw;
__declspec(property(get = YXW, put = YXW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> gra;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXWX() { return ExtractComponent<4, 1, 0, 3, 0>(); } 
template <spv::StorageClass C1> void YXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 3, 0>(_var); } 
__declspec(property(get = YXWX, put = YXWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxwx;
__declspec(property(get = YXWX, put = YXWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXWY() { return ExtractComponent<4, 1, 0, 3, 1>(); } 
template <spv::StorageClass C1> void YXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 3, 1>(_var); } 
__declspec(property(get = YXWY, put = YXWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxwy;
__declspec(property(get = YXWY, put = YXWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXWZ() { return ExtractComponent<4, 1, 0, 3, 2>(); } 
template <spv::StorageClass C1> void YXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 3, 2>(_var); } 
__declspec(property(get = YXWZ, put = YXWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxwz;
__declspec(property(get = YXWZ, put = YXWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> grab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YXWW() { return ExtractComponent<4, 1, 0, 3, 3>(); } 
template <spv::StorageClass C1> void YXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 0, 3, 3>(_var); } 
__declspec(property(get = YXWW, put = YXWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yxww;
__declspec(property(get = YXWW, put = YXWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> graa;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> YY() { return ExtractComponent<2, 1, 1>(); } 
template <spv::StorageClass C1> void YY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 1, 1>(_var); } 
__declspec(property(get = YY, put = YY)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> yy;
__declspec(property(get = YY, put = YY)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> gg;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YYX() { return ExtractComponent<3, 1, 1, 0>(); } 
template <spv::StorageClass C1> void YYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 0>(_var); } 
__declspec(property(get = YYX, put = YYX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> yyx;
__declspec(property(get = YYX, put = YYX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ggr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYXX() { return ExtractComponent<4, 1, 1, 0, 0>(); } 
template <spv::StorageClass C1> void YYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 0, 0>(_var); } 
__declspec(property(get = YYXX, put = YYXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yyxx;
__declspec(property(get = YYXX, put = YYXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ggrr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYXY() { return ExtractComponent<4, 1, 1, 0, 1>(); } 
template <spv::StorageClass C1> void YYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 0, 1>(_var); } 
__declspec(property(get = YYXY, put = YYXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yyxy;
__declspec(property(get = YYXY, put = YYXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ggrg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYXZ() { return ExtractComponent<4, 1, 1, 0, 2>(); } 
template <spv::StorageClass C1> void YYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 0, 2>(_var); } 
__declspec(property(get = YYXZ, put = YYXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yyxz;
__declspec(property(get = YYXZ, put = YYXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ggrb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYXW() { return ExtractComponent<4, 1, 1, 0, 3>(); } 
template <spv::StorageClass C1> void YYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 0, 3>(_var); } 
__declspec(property(get = YYXW, put = YYXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yyxw;
__declspec(property(get = YYXW, put = YYXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ggra;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YYY() { return ExtractComponent<3, 1, 1, 1>(); } 
template <spv::StorageClass C1> void YYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 1>(_var); } 
__declspec(property(get = YYY, put = YYY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> yyy;
__declspec(property(get = YYY, put = YYY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ggg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYYX() { return ExtractComponent<4, 1, 1, 1, 0>(); } 
template <spv::StorageClass C1> void YYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 1, 0>(_var); } 
__declspec(property(get = YYYX, put = YYYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yyyx;
__declspec(property(get = YYYX, put = YYYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gggr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYYY() { return ExtractComponent<4, 1, 1, 1, 1>(); } 
template <spv::StorageClass C1> void YYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 1, 1>(_var); } 
__declspec(property(get = YYYY, put = YYYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yyyy;
__declspec(property(get = YYYY, put = YYYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gggg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYYZ() { return ExtractComponent<4, 1, 1, 1, 2>(); } 
template <spv::StorageClass C1> void YYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 1, 2>(_var); } 
__declspec(property(get = YYYZ, put = YYYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yyyz;
__declspec(property(get = YYYZ, put = YYYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gggb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYYW() { return ExtractComponent<4, 1, 1, 1, 3>(); } 
template <spv::StorageClass C1> void YYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 1, 3>(_var); } 
__declspec(property(get = YYYW, put = YYYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yyyw;
__declspec(property(get = YYYW, put = YYYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ggga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YYZ() { return ExtractComponent<3, 1, 1, 2>(); } 
template <spv::StorageClass C1> void YYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 2>(_var); } 
__declspec(property(get = YYZ, put = YYZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> yyz;
__declspec(property(get = YYZ, put = YYZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ggb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYZX() { return ExtractComponent<4, 1, 1, 2, 0>(); } 
template <spv::StorageClass C1> void YYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 2, 0>(_var); } 
__declspec(property(get = YYZX, put = YYZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yyzx;
__declspec(property(get = YYZX, put = YYZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ggbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYZY() { return ExtractComponent<4, 1, 1, 2, 1>(); } 
template <spv::StorageClass C1> void YYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 2, 1>(_var); } 
__declspec(property(get = YYZY, put = YYZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yyzy;
__declspec(property(get = YYZY, put = YYZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ggbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYZZ() { return ExtractComponent<4, 1, 1, 2, 2>(); } 
template <spv::StorageClass C1> void YYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 2, 2>(_var); } 
__declspec(property(get = YYZZ, put = YYZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yyzz;
__declspec(property(get = YYZZ, put = YYZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ggbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYZW() { return ExtractComponent<4, 1, 1, 2, 3>(); } 
template <spv::StorageClass C1> void YYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 2, 3>(_var); } 
__declspec(property(get = YYZW, put = YYZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yyzw;
__declspec(property(get = YYZW, put = YYZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ggba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YYW() { return ExtractComponent<3, 1, 1, 3>(); } 
template <spv::StorageClass C1> void YYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 1, 3>(_var); } 
__declspec(property(get = YYW, put = YYW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> yyw;
__declspec(property(get = YYW, put = YYW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> gga;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYWX() { return ExtractComponent<4, 1, 1, 3, 0>(); } 
template <spv::StorageClass C1> void YYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 3, 0>(_var); } 
__declspec(property(get = YYWX, put = YYWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yywx;
__declspec(property(get = YYWX, put = YYWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ggar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYWY() { return ExtractComponent<4, 1, 1, 3, 1>(); } 
template <spv::StorageClass C1> void YYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 3, 1>(_var); } 
__declspec(property(get = YYWY, put = YYWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yywy;
__declspec(property(get = YYWY, put = YYWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ggag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYWZ() { return ExtractComponent<4, 1, 1, 3, 2>(); } 
template <spv::StorageClass C1> void YYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 3, 2>(_var); } 
__declspec(property(get = YYWZ, put = YYWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yywz;
__declspec(property(get = YYWZ, put = YYWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ggab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YYWW() { return ExtractComponent<4, 1, 1, 3, 3>(); } 
template <spv::StorageClass C1> void YYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 1, 3, 3>(_var); } 
__declspec(property(get = YYWW, put = YYWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yyww;
__declspec(property(get = YYWW, put = YYWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ggaa;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> YZ() { return ExtractComponent<2, 1, 2>(); } 
template <spv::StorageClass C1> void YZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 1, 2>(_var); } 
__declspec(property(get = YZ, put = YZ)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> yz;
__declspec(property(get = YZ, put = YZ)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> gb;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YZX() { return ExtractComponent<3, 1, 2, 0>(); } 
template <spv::StorageClass C1> void YZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 0>(_var); } 
__declspec(property(get = YZX, put = YZX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> yzx;
__declspec(property(get = YZX, put = YZX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> gbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZXX() { return ExtractComponent<4, 1, 2, 0, 0>(); } 
template <spv::StorageClass C1> void YZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 0, 0>(_var); } 
__declspec(property(get = YZXX, put = YZXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzxx;
__declspec(property(get = YZXX, put = YZXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbrr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZXY() { return ExtractComponent<4, 1, 2, 0, 1>(); } 
template <spv::StorageClass C1> void YZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 0, 1>(_var); } 
__declspec(property(get = YZXY, put = YZXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzxy;
__declspec(property(get = YZXY, put = YZXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbrg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZXZ() { return ExtractComponent<4, 1, 2, 0, 2>(); } 
template <spv::StorageClass C1> void YZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 0, 2>(_var); } 
__declspec(property(get = YZXZ, put = YZXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzxz;
__declspec(property(get = YZXZ, put = YZXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbrb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZXW() { return ExtractComponent<4, 1, 2, 0, 3>(); } 
template <spv::StorageClass C1> void YZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 0, 3>(_var); } 
__declspec(property(get = YZXW, put = YZXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzxw;
__declspec(property(get = YZXW, put = YZXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbra;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YZY() { return ExtractComponent<3, 1, 2, 1>(); } 
template <spv::StorageClass C1> void YZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 1>(_var); } 
__declspec(property(get = YZY, put = YZY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> yzy;
__declspec(property(get = YZY, put = YZY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> gbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZYX() { return ExtractComponent<4, 1, 2, 1, 0>(); } 
template <spv::StorageClass C1> void YZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 1, 0>(_var); } 
__declspec(property(get = YZYX, put = YZYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzyx;
__declspec(property(get = YZYX, put = YZYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbgr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZYY() { return ExtractComponent<4, 1, 2, 1, 1>(); } 
template <spv::StorageClass C1> void YZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 1, 1>(_var); } 
__declspec(property(get = YZYY, put = YZYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzyy;
__declspec(property(get = YZYY, put = YZYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbgg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZYZ() { return ExtractComponent<4, 1, 2, 1, 2>(); } 
template <spv::StorageClass C1> void YZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 1, 2>(_var); } 
__declspec(property(get = YZYZ, put = YZYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzyz;
__declspec(property(get = YZYZ, put = YZYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbgb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZYW() { return ExtractComponent<4, 1, 2, 1, 3>(); } 
template <spv::StorageClass C1> void YZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 1, 3>(_var); } 
__declspec(property(get = YZYW, put = YZYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzyw;
__declspec(property(get = YZYW, put = YZYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YZZ() { return ExtractComponent<3, 1, 2, 2>(); } 
template <spv::StorageClass C1> void YZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 2>(_var); } 
__declspec(property(get = YZZ, put = YZZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> yzz;
__declspec(property(get = YZZ, put = YZZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> gbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZZX() { return ExtractComponent<4, 1, 2, 2, 0>(); } 
template <spv::StorageClass C1> void YZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 2, 0>(_var); } 
__declspec(property(get = YZZX, put = YZZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzzx;
__declspec(property(get = YZZX, put = YZZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZZY() { return ExtractComponent<4, 1, 2, 2, 1>(); } 
template <spv::StorageClass C1> void YZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 2, 1>(_var); } 
__declspec(property(get = YZZY, put = YZZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzzy;
__declspec(property(get = YZZY, put = YZZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZZZ() { return ExtractComponent<4, 1, 2, 2, 2>(); } 
template <spv::StorageClass C1> void YZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 2, 2>(_var); } 
__declspec(property(get = YZZZ, put = YZZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzzz;
__declspec(property(get = YZZZ, put = YZZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZZW() { return ExtractComponent<4, 1, 2, 2, 3>(); } 
template <spv::StorageClass C1> void YZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 2, 3>(_var); } 
__declspec(property(get = YZZW, put = YZZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzzw;
__declspec(property(get = YZZW, put = YZZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YZW() { return ExtractComponent<3, 1, 2, 3>(); } 
template <spv::StorageClass C1> void YZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 2, 3>(_var); } 
__declspec(property(get = YZW, put = YZW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> yzw;
__declspec(property(get = YZW, put = YZW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> gba;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZWX() { return ExtractComponent<4, 1, 2, 3, 0>(); } 
template <spv::StorageClass C1> void YZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 3, 0>(_var); } 
__declspec(property(get = YZWX, put = YZWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzwx;
__declspec(property(get = YZWX, put = YZWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZWY() { return ExtractComponent<4, 1, 2, 3, 1>(); } 
template <spv::StorageClass C1> void YZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 3, 1>(_var); } 
__declspec(property(get = YZWY, put = YZWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzwy;
__declspec(property(get = YZWY, put = YZWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZWZ() { return ExtractComponent<4, 1, 2, 3, 2>(); } 
template <spv::StorageClass C1> void YZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 3, 2>(_var); } 
__declspec(property(get = YZWZ, put = YZWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzwz;
__declspec(property(get = YZWZ, put = YZWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YZWW() { return ExtractComponent<4, 1, 2, 3, 3>(); } 
template <spv::StorageClass C1> void YZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 2, 3, 3>(_var); } 
__declspec(property(get = YZWW, put = YZWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> yzww;
__declspec(property(get = YZWW, put = YZWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gbaa;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> YW() { return ExtractComponent<2, 1, 3>(); } 
template <spv::StorageClass C1> void YW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 1, 3>(_var); } 
__declspec(property(get = YW, put = YW)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> yw;
__declspec(property(get = YW, put = YW)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> ga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YWX() { return ExtractComponent<3, 1, 3, 0>(); } 
template <spv::StorageClass C1> void YWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 0>(_var); } 
__declspec(property(get = YWX, put = YWX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ywx;
__declspec(property(get = YWX, put = YWX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> gar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWXX() { return ExtractComponent<4, 1, 3, 0, 0>(); } 
template <spv::StorageClass C1> void YWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 0, 0>(_var); } 
__declspec(property(get = YWXX, put = YWXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywxx;
__declspec(property(get = YWXX, put = YWXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> garr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWXY() { return ExtractComponent<4, 1, 3, 0, 1>(); } 
template <spv::StorageClass C1> void YWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 0, 1>(_var); } 
__declspec(property(get = YWXY, put = YWXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywxy;
__declspec(property(get = YWXY, put = YWXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> garg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWXZ() { return ExtractComponent<4, 1, 3, 0, 2>(); } 
template <spv::StorageClass C1> void YWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 0, 2>(_var); } 
__declspec(property(get = YWXZ, put = YWXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywxz;
__declspec(property(get = YWXZ, put = YWXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> garb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWXW() { return ExtractComponent<4, 1, 3, 0, 3>(); } 
template <spv::StorageClass C1> void YWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 0, 3>(_var); } 
__declspec(property(get = YWXW, put = YWXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywxw;
__declspec(property(get = YWXW, put = YWXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gara;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YWY() { return ExtractComponent<3, 1, 3, 1>(); } 
template <spv::StorageClass C1> void YWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 1>(_var); } 
__declspec(property(get = YWY, put = YWY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ywy;
__declspec(property(get = YWY, put = YWY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> gag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWYX() { return ExtractComponent<4, 1, 3, 1, 0>(); } 
template <spv::StorageClass C1> void YWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 1, 0>(_var); } 
__declspec(property(get = YWYX, put = YWYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywyx;
__declspec(property(get = YWYX, put = YWYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gagr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWYY() { return ExtractComponent<4, 1, 3, 1, 1>(); } 
template <spv::StorageClass C1> void YWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 1, 1>(_var); } 
__declspec(property(get = YWYY, put = YWYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywyy;
__declspec(property(get = YWYY, put = YWYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gagg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWYZ() { return ExtractComponent<4, 1, 3, 1, 2>(); } 
template <spv::StorageClass C1> void YWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 1, 2>(_var); } 
__declspec(property(get = YWYZ, put = YWYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywyz;
__declspec(property(get = YWYZ, put = YWYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gagb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWYW() { return ExtractComponent<4, 1, 3, 1, 3>(); } 
template <spv::StorageClass C1> void YWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 1, 3>(_var); } 
__declspec(property(get = YWYW, put = YWYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywyw;
__declspec(property(get = YWYW, put = YWYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gaga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YWZ() { return ExtractComponent<3, 1, 3, 2>(); } 
template <spv::StorageClass C1> void YWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 2>(_var); } 
__declspec(property(get = YWZ, put = YWZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ywz;
__declspec(property(get = YWZ, put = YWZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> gab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWZX() { return ExtractComponent<4, 1, 3, 2, 0>(); } 
template <spv::StorageClass C1> void YWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 2, 0>(_var); } 
__declspec(property(get = YWZX, put = YWZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywzx;
__declspec(property(get = YWZX, put = YWZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gabr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWZY() { return ExtractComponent<4, 1, 3, 2, 1>(); } 
template <spv::StorageClass C1> void YWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 2, 1>(_var); } 
__declspec(property(get = YWZY, put = YWZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywzy;
__declspec(property(get = YWZY, put = YWZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gabg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWZZ() { return ExtractComponent<4, 1, 3, 2, 2>(); } 
template <spv::StorageClass C1> void YWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 2, 2>(_var); } 
__declspec(property(get = YWZZ, put = YWZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywzz;
__declspec(property(get = YWZZ, put = YWZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gabb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWZW() { return ExtractComponent<4, 1, 3, 2, 3>(); } 
template <spv::StorageClass C1> void YWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 2, 3>(_var); } 
__declspec(property(get = YWZW, put = YWZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywzw;
__declspec(property(get = YWZW, put = YWZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gaba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> YWW() { return ExtractComponent<3, 1, 3, 3>(); } 
template <spv::StorageClass C1> void YWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 1, 3, 3>(_var); } 
__declspec(property(get = YWW, put = YWW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> yww;
__declspec(property(get = YWW, put = YWW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> gaa;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWWX() { return ExtractComponent<4, 1, 3, 3, 0>(); } 
template <spv::StorageClass C1> void YWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 3, 0>(_var); } 
__declspec(property(get = YWWX, put = YWWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywwx;
__declspec(property(get = YWWX, put = YWWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gaar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWWY() { return ExtractComponent<4, 1, 3, 3, 1>(); } 
template <spv::StorageClass C1> void YWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 3, 1>(_var); } 
__declspec(property(get = YWWY, put = YWWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywwy;
__declspec(property(get = YWWY, put = YWWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gaag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWWZ() { return ExtractComponent<4, 1, 3, 3, 2>(); } 
template <spv::StorageClass C1> void YWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 3, 2>(_var); } 
__declspec(property(get = YWWZ, put = YWWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywwz;
__declspec(property(get = YWWZ, put = YWWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gaab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> YWWW() { return ExtractComponent<4, 1, 3, 3, 3>(); } 
template <spv::StorageClass C1> void YWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 1, 3, 3, 3>(_var); } 
__declspec(property(get = YWWW, put = YWWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ywww;
__declspec(property(get = YWWW, put = YWWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> gaaa;
var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction> Z() { return ExtractComponent<1, 2>(); } 
template <spv::StorageClass C1> void Z(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) { InsertComponent<1, 2>(_var); } 
__declspec(property(get = Z, put = Z)) var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction> z;
__declspec(property(get = Z, put = Z)) var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction> b;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> ZX() { return ExtractComponent<2, 2, 0>(); } 
template <spv::StorageClass C1> void ZX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 2, 0>(_var); } 
__declspec(property(get = ZX, put = ZX)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> zx;
__declspec(property(get = ZX, put = ZX)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> br;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZXX() { return ExtractComponent<3, 2, 0, 0>(); } 
template <spv::StorageClass C1> void ZXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 0>(_var); } 
__declspec(property(get = ZXX, put = ZXX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zxx;
__declspec(property(get = ZXX, put = ZXX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> brr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXXX() { return ExtractComponent<4, 2, 0, 0, 0>(); } 
template <spv::StorageClass C1> void ZXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 0, 0>(_var); } 
__declspec(property(get = ZXXX, put = ZXXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxxx;
__declspec(property(get = ZXXX, put = ZXXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brrr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXXY() { return ExtractComponent<4, 2, 0, 0, 1>(); } 
template <spv::StorageClass C1> void ZXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 0, 1>(_var); } 
__declspec(property(get = ZXXY, put = ZXXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxxy;
__declspec(property(get = ZXXY, put = ZXXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brrg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXXZ() { return ExtractComponent<4, 2, 0, 0, 2>(); } 
template <spv::StorageClass C1> void ZXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 0, 2>(_var); } 
__declspec(property(get = ZXXZ, put = ZXXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxxz;
__declspec(property(get = ZXXZ, put = ZXXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brrb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXXW() { return ExtractComponent<4, 2, 0, 0, 3>(); } 
template <spv::StorageClass C1> void ZXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 0, 3>(_var); } 
__declspec(property(get = ZXXW, put = ZXXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxxw;
__declspec(property(get = ZXXW, put = ZXXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brra;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZXY() { return ExtractComponent<3, 2, 0, 1>(); } 
template <spv::StorageClass C1> void ZXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 1>(_var); } 
__declspec(property(get = ZXY, put = ZXY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zxy;
__declspec(property(get = ZXY, put = ZXY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> brg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXYX() { return ExtractComponent<4, 2, 0, 1, 0>(); } 
template <spv::StorageClass C1> void ZXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 1, 0>(_var); } 
__declspec(property(get = ZXYX, put = ZXYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxyx;
__declspec(property(get = ZXYX, put = ZXYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brgr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXYY() { return ExtractComponent<4, 2, 0, 1, 1>(); } 
template <spv::StorageClass C1> void ZXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 1, 1>(_var); } 
__declspec(property(get = ZXYY, put = ZXYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxyy;
__declspec(property(get = ZXYY, put = ZXYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brgg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXYZ() { return ExtractComponent<4, 2, 0, 1, 2>(); } 
template <spv::StorageClass C1> void ZXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 1, 2>(_var); } 
__declspec(property(get = ZXYZ, put = ZXYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxyz;
__declspec(property(get = ZXYZ, put = ZXYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brgb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXYW() { return ExtractComponent<4, 2, 0, 1, 3>(); } 
template <spv::StorageClass C1> void ZXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 1, 3>(_var); } 
__declspec(property(get = ZXYW, put = ZXYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxyw;
__declspec(property(get = ZXYW, put = ZXYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZXZ() { return ExtractComponent<3, 2, 0, 2>(); } 
template <spv::StorageClass C1> void ZXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 2>(_var); } 
__declspec(property(get = ZXZ, put = ZXZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zxz;
__declspec(property(get = ZXZ, put = ZXZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> brb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXZX() { return ExtractComponent<4, 2, 0, 2, 0>(); } 
template <spv::StorageClass C1> void ZXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 2, 0>(_var); } 
__declspec(property(get = ZXZX, put = ZXZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxzx;
__declspec(property(get = ZXZX, put = ZXZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXZY() { return ExtractComponent<4, 2, 0, 2, 1>(); } 
template <spv::StorageClass C1> void ZXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 2, 1>(_var); } 
__declspec(property(get = ZXZY, put = ZXZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxzy;
__declspec(property(get = ZXZY, put = ZXZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXZZ() { return ExtractComponent<4, 2, 0, 2, 2>(); } 
template <spv::StorageClass C1> void ZXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 2, 2>(_var); } 
__declspec(property(get = ZXZZ, put = ZXZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxzz;
__declspec(property(get = ZXZZ, put = ZXZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXZW() { return ExtractComponent<4, 2, 0, 2, 3>(); } 
template <spv::StorageClass C1> void ZXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 2, 3>(_var); } 
__declspec(property(get = ZXZW, put = ZXZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxzw;
__declspec(property(get = ZXZW, put = ZXZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZXW() { return ExtractComponent<3, 2, 0, 3>(); } 
template <spv::StorageClass C1> void ZXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 0, 3>(_var); } 
__declspec(property(get = ZXW, put = ZXW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zxw;
__declspec(property(get = ZXW, put = ZXW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> bra;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXWX() { return ExtractComponent<4, 2, 0, 3, 0>(); } 
template <spv::StorageClass C1> void ZXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 3, 0>(_var); } 
__declspec(property(get = ZXWX, put = ZXWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxwx;
__declspec(property(get = ZXWX, put = ZXWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXWY() { return ExtractComponent<4, 2, 0, 3, 1>(); } 
template <spv::StorageClass C1> void ZXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 3, 1>(_var); } 
__declspec(property(get = ZXWY, put = ZXWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxwy;
__declspec(property(get = ZXWY, put = ZXWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXWZ() { return ExtractComponent<4, 2, 0, 3, 2>(); } 
template <spv::StorageClass C1> void ZXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 3, 2>(_var); } 
__declspec(property(get = ZXWZ, put = ZXWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxwz;
__declspec(property(get = ZXWZ, put = ZXWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> brab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZXWW() { return ExtractComponent<4, 2, 0, 3, 3>(); } 
template <spv::StorageClass C1> void ZXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 0, 3, 3>(_var); } 
__declspec(property(get = ZXWW, put = ZXWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zxww;
__declspec(property(get = ZXWW, put = ZXWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> braa;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> ZY() { return ExtractComponent<2, 2, 1>(); } 
template <spv::StorageClass C1> void ZY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 2, 1>(_var); } 
__declspec(property(get = ZY, put = ZY)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> zy;
__declspec(property(get = ZY, put = ZY)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> bg;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZYX() { return ExtractComponent<3, 2, 1, 0>(); } 
template <spv::StorageClass C1> void ZYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 0>(_var); } 
__declspec(property(get = ZYX, put = ZYX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zyx;
__declspec(property(get = ZYX, put = ZYX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> bgr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYXX() { return ExtractComponent<4, 2, 1, 0, 0>(); } 
template <spv::StorageClass C1> void ZYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 0, 0>(_var); } 
__declspec(property(get = ZYXX, put = ZYXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zyxx;
__declspec(property(get = ZYXX, put = ZYXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bgrr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYXY() { return ExtractComponent<4, 2, 1, 0, 1>(); } 
template <spv::StorageClass C1> void ZYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 0, 1>(_var); } 
__declspec(property(get = ZYXY, put = ZYXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zyxy;
__declspec(property(get = ZYXY, put = ZYXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bgrg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYXZ() { return ExtractComponent<4, 2, 1, 0, 2>(); } 
template <spv::StorageClass C1> void ZYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 0, 2>(_var); } 
__declspec(property(get = ZYXZ, put = ZYXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zyxz;
__declspec(property(get = ZYXZ, put = ZYXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bgrb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYXW() { return ExtractComponent<4, 2, 1, 0, 3>(); } 
template <spv::StorageClass C1> void ZYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 0, 3>(_var); } 
__declspec(property(get = ZYXW, put = ZYXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zyxw;
__declspec(property(get = ZYXW, put = ZYXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bgra;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZYY() { return ExtractComponent<3, 2, 1, 1>(); } 
template <spv::StorageClass C1> void ZYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 1>(_var); } 
__declspec(property(get = ZYY, put = ZYY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zyy;
__declspec(property(get = ZYY, put = ZYY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> bgg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYYX() { return ExtractComponent<4, 2, 1, 1, 0>(); } 
template <spv::StorageClass C1> void ZYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 1, 0>(_var); } 
__declspec(property(get = ZYYX, put = ZYYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zyyx;
__declspec(property(get = ZYYX, put = ZYYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bggr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYYY() { return ExtractComponent<4, 2, 1, 1, 1>(); } 
template <spv::StorageClass C1> void ZYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 1, 1>(_var); } 
__declspec(property(get = ZYYY, put = ZYYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zyyy;
__declspec(property(get = ZYYY, put = ZYYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bggg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYYZ() { return ExtractComponent<4, 2, 1, 1, 2>(); } 
template <spv::StorageClass C1> void ZYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 1, 2>(_var); } 
__declspec(property(get = ZYYZ, put = ZYYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zyyz;
__declspec(property(get = ZYYZ, put = ZYYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bggb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYYW() { return ExtractComponent<4, 2, 1, 1, 3>(); } 
template <spv::StorageClass C1> void ZYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 1, 3>(_var); } 
__declspec(property(get = ZYYW, put = ZYYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zyyw;
__declspec(property(get = ZYYW, put = ZYYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bgga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZYZ() { return ExtractComponent<3, 2, 1, 2>(); } 
template <spv::StorageClass C1> void ZYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 2>(_var); } 
__declspec(property(get = ZYZ, put = ZYZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zyz;
__declspec(property(get = ZYZ, put = ZYZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> bgb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYZX() { return ExtractComponent<4, 2, 1, 2, 0>(); } 
template <spv::StorageClass C1> void ZYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 2, 0>(_var); } 
__declspec(property(get = ZYZX, put = ZYZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zyzx;
__declspec(property(get = ZYZX, put = ZYZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bgbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYZY() { return ExtractComponent<4, 2, 1, 2, 1>(); } 
template <spv::StorageClass C1> void ZYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 2, 1>(_var); } 
__declspec(property(get = ZYZY, put = ZYZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zyzy;
__declspec(property(get = ZYZY, put = ZYZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bgbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYZZ() { return ExtractComponent<4, 2, 1, 2, 2>(); } 
template <spv::StorageClass C1> void ZYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 2, 2>(_var); } 
__declspec(property(get = ZYZZ, put = ZYZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zyzz;
__declspec(property(get = ZYZZ, put = ZYZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bgbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYZW() { return ExtractComponent<4, 2, 1, 2, 3>(); } 
template <spv::StorageClass C1> void ZYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 2, 3>(_var); } 
__declspec(property(get = ZYZW, put = ZYZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zyzw;
__declspec(property(get = ZYZW, put = ZYZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bgba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZYW() { return ExtractComponent<3, 2, 1, 3>(); } 
template <spv::StorageClass C1> void ZYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 1, 3>(_var); } 
__declspec(property(get = ZYW, put = ZYW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zyw;
__declspec(property(get = ZYW, put = ZYW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> bga;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYWX() { return ExtractComponent<4, 2, 1, 3, 0>(); } 
template <spv::StorageClass C1> void ZYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 3, 0>(_var); } 
__declspec(property(get = ZYWX, put = ZYWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zywx;
__declspec(property(get = ZYWX, put = ZYWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bgar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYWY() { return ExtractComponent<4, 2, 1, 3, 1>(); } 
template <spv::StorageClass C1> void ZYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 3, 1>(_var); } 
__declspec(property(get = ZYWY, put = ZYWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zywy;
__declspec(property(get = ZYWY, put = ZYWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bgag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYWZ() { return ExtractComponent<4, 2, 1, 3, 2>(); } 
template <spv::StorageClass C1> void ZYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 3, 2>(_var); } 
__declspec(property(get = ZYWZ, put = ZYWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zywz;
__declspec(property(get = ZYWZ, put = ZYWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bgab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZYWW() { return ExtractComponent<4, 2, 1, 3, 3>(); } 
template <spv::StorageClass C1> void ZYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 1, 3, 3>(_var); } 
__declspec(property(get = ZYWW, put = ZYWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zyww;
__declspec(property(get = ZYWW, put = ZYWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bgaa;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> ZZ() { return ExtractComponent<2, 2, 2>(); } 
template <spv::StorageClass C1> void ZZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 2, 2>(_var); } 
__declspec(property(get = ZZ, put = ZZ)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> zz;
__declspec(property(get = ZZ, put = ZZ)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> bb;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZZX() { return ExtractComponent<3, 2, 2, 0>(); } 
template <spv::StorageClass C1> void ZZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 0>(_var); } 
__declspec(property(get = ZZX, put = ZZX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zzx;
__declspec(property(get = ZZX, put = ZZX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> bbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZXX() { return ExtractComponent<4, 2, 2, 0, 0>(); } 
template <spv::StorageClass C1> void ZZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 0, 0>(_var); } 
__declspec(property(get = ZZXX, put = ZZXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzxx;
__declspec(property(get = ZZXX, put = ZZXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbrr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZXY() { return ExtractComponent<4, 2, 2, 0, 1>(); } 
template <spv::StorageClass C1> void ZZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 0, 1>(_var); } 
__declspec(property(get = ZZXY, put = ZZXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzxy;
__declspec(property(get = ZZXY, put = ZZXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbrg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZXZ() { return ExtractComponent<4, 2, 2, 0, 2>(); } 
template <spv::StorageClass C1> void ZZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 0, 2>(_var); } 
__declspec(property(get = ZZXZ, put = ZZXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzxz;
__declspec(property(get = ZZXZ, put = ZZXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbrb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZXW() { return ExtractComponent<4, 2, 2, 0, 3>(); } 
template <spv::StorageClass C1> void ZZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 0, 3>(_var); } 
__declspec(property(get = ZZXW, put = ZZXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzxw;
__declspec(property(get = ZZXW, put = ZZXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbra;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZZY() { return ExtractComponent<3, 2, 2, 1>(); } 
template <spv::StorageClass C1> void ZZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 1>(_var); } 
__declspec(property(get = ZZY, put = ZZY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zzy;
__declspec(property(get = ZZY, put = ZZY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> bbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZYX() { return ExtractComponent<4, 2, 2, 1, 0>(); } 
template <spv::StorageClass C1> void ZZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 1, 0>(_var); } 
__declspec(property(get = ZZYX, put = ZZYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzyx;
__declspec(property(get = ZZYX, put = ZZYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbgr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZYY() { return ExtractComponent<4, 2, 2, 1, 1>(); } 
template <spv::StorageClass C1> void ZZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 1, 1>(_var); } 
__declspec(property(get = ZZYY, put = ZZYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzyy;
__declspec(property(get = ZZYY, put = ZZYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbgg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZYZ() { return ExtractComponent<4, 2, 2, 1, 2>(); } 
template <spv::StorageClass C1> void ZZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 1, 2>(_var); } 
__declspec(property(get = ZZYZ, put = ZZYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzyz;
__declspec(property(get = ZZYZ, put = ZZYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbgb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZYW() { return ExtractComponent<4, 2, 2, 1, 3>(); } 
template <spv::StorageClass C1> void ZZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 1, 3>(_var); } 
__declspec(property(get = ZZYW, put = ZZYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzyw;
__declspec(property(get = ZZYW, put = ZZYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZZZ() { return ExtractComponent<3, 2, 2, 2>(); } 
template <spv::StorageClass C1> void ZZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 2>(_var); } 
__declspec(property(get = ZZZ, put = ZZZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zzz;
__declspec(property(get = ZZZ, put = ZZZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> bbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZZX() { return ExtractComponent<4, 2, 2, 2, 0>(); } 
template <spv::StorageClass C1> void ZZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 2, 0>(_var); } 
__declspec(property(get = ZZZX, put = ZZZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzzx;
__declspec(property(get = ZZZX, put = ZZZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZZY() { return ExtractComponent<4, 2, 2, 2, 1>(); } 
template <spv::StorageClass C1> void ZZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 2, 1>(_var); } 
__declspec(property(get = ZZZY, put = ZZZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzzy;
__declspec(property(get = ZZZY, put = ZZZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZZZ() { return ExtractComponent<4, 2, 2, 2, 2>(); } 
template <spv::StorageClass C1> void ZZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 2, 2>(_var); } 
__declspec(property(get = ZZZZ, put = ZZZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzzz;
__declspec(property(get = ZZZZ, put = ZZZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZZW() { return ExtractComponent<4, 2, 2, 2, 3>(); } 
template <spv::StorageClass C1> void ZZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 2, 3>(_var); } 
__declspec(property(get = ZZZW, put = ZZZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzzw;
__declspec(property(get = ZZZW, put = ZZZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZZW() { return ExtractComponent<3, 2, 2, 3>(); } 
template <spv::StorageClass C1> void ZZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 2, 3>(_var); } 
__declspec(property(get = ZZW, put = ZZW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zzw;
__declspec(property(get = ZZW, put = ZZW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> bba;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZWX() { return ExtractComponent<4, 2, 2, 3, 0>(); } 
template <spv::StorageClass C1> void ZZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 3, 0>(_var); } 
__declspec(property(get = ZZWX, put = ZZWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzwx;
__declspec(property(get = ZZWX, put = ZZWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZWY() { return ExtractComponent<4, 2, 2, 3, 1>(); } 
template <spv::StorageClass C1> void ZZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 3, 1>(_var); } 
__declspec(property(get = ZZWY, put = ZZWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzwy;
__declspec(property(get = ZZWY, put = ZZWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZWZ() { return ExtractComponent<4, 2, 2, 3, 2>(); } 
template <spv::StorageClass C1> void ZZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 3, 2>(_var); } 
__declspec(property(get = ZZWZ, put = ZZWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzwz;
__declspec(property(get = ZZWZ, put = ZZWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZZWW() { return ExtractComponent<4, 2, 2, 3, 3>(); } 
template <spv::StorageClass C1> void ZZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 2, 3, 3>(_var); } 
__declspec(property(get = ZZWW, put = ZZWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zzww;
__declspec(property(get = ZZWW, put = ZZWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bbaa;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> ZW() { return ExtractComponent<2, 2, 3>(); } 
template <spv::StorageClass C1> void ZW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 2, 3>(_var); } 
__declspec(property(get = ZW, put = ZW)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> zw;
__declspec(property(get = ZW, put = ZW)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> ba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZWX() { return ExtractComponent<3, 2, 3, 0>(); } 
template <spv::StorageClass C1> void ZWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 0>(_var); } 
__declspec(property(get = ZWX, put = ZWX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zwx;
__declspec(property(get = ZWX, put = ZWX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> bar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWXX() { return ExtractComponent<4, 2, 3, 0, 0>(); } 
template <spv::StorageClass C1> void ZWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 0, 0>(_var); } 
__declspec(property(get = ZWXX, put = ZWXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwxx;
__declspec(property(get = ZWXX, put = ZWXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> barr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWXY() { return ExtractComponent<4, 2, 3, 0, 1>(); } 
template <spv::StorageClass C1> void ZWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 0, 1>(_var); } 
__declspec(property(get = ZWXY, put = ZWXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwxy;
__declspec(property(get = ZWXY, put = ZWXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> barg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWXZ() { return ExtractComponent<4, 2, 3, 0, 2>(); } 
template <spv::StorageClass C1> void ZWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 0, 2>(_var); } 
__declspec(property(get = ZWXZ, put = ZWXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwxz;
__declspec(property(get = ZWXZ, put = ZWXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> barb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWXW() { return ExtractComponent<4, 2, 3, 0, 3>(); } 
template <spv::StorageClass C1> void ZWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 0, 3>(_var); } 
__declspec(property(get = ZWXW, put = ZWXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwxw;
__declspec(property(get = ZWXW, put = ZWXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bara;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZWY() { return ExtractComponent<3, 2, 3, 1>(); } 
template <spv::StorageClass C1> void ZWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 1>(_var); } 
__declspec(property(get = ZWY, put = ZWY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zwy;
__declspec(property(get = ZWY, put = ZWY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> bag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWYX() { return ExtractComponent<4, 2, 3, 1, 0>(); } 
template <spv::StorageClass C1> void ZWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 1, 0>(_var); } 
__declspec(property(get = ZWYX, put = ZWYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwyx;
__declspec(property(get = ZWYX, put = ZWYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bagr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWYY() { return ExtractComponent<4, 2, 3, 1, 1>(); } 
template <spv::StorageClass C1> void ZWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 1, 1>(_var); } 
__declspec(property(get = ZWYY, put = ZWYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwyy;
__declspec(property(get = ZWYY, put = ZWYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bagg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWYZ() { return ExtractComponent<4, 2, 3, 1, 2>(); } 
template <spv::StorageClass C1> void ZWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 1, 2>(_var); } 
__declspec(property(get = ZWYZ, put = ZWYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwyz;
__declspec(property(get = ZWYZ, put = ZWYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> bagb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWYW() { return ExtractComponent<4, 2, 3, 1, 3>(); } 
template <spv::StorageClass C1> void ZWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 1, 3>(_var); } 
__declspec(property(get = ZWYW, put = ZWYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwyw;
__declspec(property(get = ZWYW, put = ZWYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> baga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZWZ() { return ExtractComponent<3, 2, 3, 2>(); } 
template <spv::StorageClass C1> void ZWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 2>(_var); } 
__declspec(property(get = ZWZ, put = ZWZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zwz;
__declspec(property(get = ZWZ, put = ZWZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> bab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWZX() { return ExtractComponent<4, 2, 3, 2, 0>(); } 
template <spv::StorageClass C1> void ZWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 2, 0>(_var); } 
__declspec(property(get = ZWZX, put = ZWZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwzx;
__declspec(property(get = ZWZX, put = ZWZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> babr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWZY() { return ExtractComponent<4, 2, 3, 2, 1>(); } 
template <spv::StorageClass C1> void ZWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 2, 1>(_var); } 
__declspec(property(get = ZWZY, put = ZWZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwzy;
__declspec(property(get = ZWZY, put = ZWZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> babg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWZZ() { return ExtractComponent<4, 2, 3, 2, 2>(); } 
template <spv::StorageClass C1> void ZWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 2, 2>(_var); } 
__declspec(property(get = ZWZZ, put = ZWZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwzz;
__declspec(property(get = ZWZZ, put = ZWZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> babb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWZW() { return ExtractComponent<4, 2, 3, 2, 3>(); } 
template <spv::StorageClass C1> void ZWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 2, 3>(_var); } 
__declspec(property(get = ZWZW, put = ZWZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwzw;
__declspec(property(get = ZWZW, put = ZWZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> baba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ZWW() { return ExtractComponent<3, 2, 3, 3>(); } 
template <spv::StorageClass C1> void ZWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 2, 3, 3>(_var); } 
__declspec(property(get = ZWW, put = ZWW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> zww;
__declspec(property(get = ZWW, put = ZWW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> baa;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWWX() { return ExtractComponent<4, 2, 3, 3, 0>(); } 
template <spv::StorageClass C1> void ZWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 3, 0>(_var); } 
__declspec(property(get = ZWWX, put = ZWWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwwx;
__declspec(property(get = ZWWX, put = ZWWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> baar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWWY() { return ExtractComponent<4, 2, 3, 3, 1>(); } 
template <spv::StorageClass C1> void ZWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 3, 1>(_var); } 
__declspec(property(get = ZWWY, put = ZWWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwwy;
__declspec(property(get = ZWWY, put = ZWWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> baag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWWZ() { return ExtractComponent<4, 2, 3, 3, 2>(); } 
template <spv::StorageClass C1> void ZWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 3, 2>(_var); } 
__declspec(property(get = ZWWZ, put = ZWWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwwz;
__declspec(property(get = ZWWZ, put = ZWWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> baab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> ZWWW() { return ExtractComponent<4, 2, 3, 3, 3>(); } 
template <spv::StorageClass C1> void ZWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 2, 3, 3, 3>(_var); } 
__declspec(property(get = ZWWW, put = ZWWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> zwww;
__declspec(property(get = ZWWW, put = ZWWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> baaa;
var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction> W() { return ExtractComponent<1, 3>(); } 
template <spv::StorageClass C1> void W(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) { InsertComponent<1, 3>(_var); } 
__declspec(property(get = W, put = W)) var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction> w;
__declspec(property(get = W, put = W)) var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction> a;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> WX() { return ExtractComponent<2, 3, 0>(); } 
template <spv::StorageClass C1> void WX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 3, 0>(_var); } 
__declspec(property(get = WX, put = WX)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> wx;
__declspec(property(get = WX, put = WX)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> ar;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WXX() { return ExtractComponent<3, 3, 0, 0>(); } 
template <spv::StorageClass C1> void WXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 0>(_var); } 
__declspec(property(get = WXX, put = WXX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wxx;
__declspec(property(get = WXX, put = WXX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> arr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXXX() { return ExtractComponent<4, 3, 0, 0, 0>(); } 
template <spv::StorageClass C1> void WXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 0, 0>(_var); } 
__declspec(property(get = WXXX, put = WXXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxxx;
__declspec(property(get = WXXX, put = WXXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> arrr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXXY() { return ExtractComponent<4, 3, 0, 0, 1>(); } 
template <spv::StorageClass C1> void WXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 0, 1>(_var); } 
__declspec(property(get = WXXY, put = WXXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxxy;
__declspec(property(get = WXXY, put = WXXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> arrg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXXZ() { return ExtractComponent<4, 3, 0, 0, 2>(); } 
template <spv::StorageClass C1> void WXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 0, 2>(_var); } 
__declspec(property(get = WXXZ, put = WXXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxxz;
__declspec(property(get = WXXZ, put = WXXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> arrb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXXW() { return ExtractComponent<4, 3, 0, 0, 3>(); } 
template <spv::StorageClass C1> void WXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 0, 3>(_var); } 
__declspec(property(get = WXXW, put = WXXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxxw;
__declspec(property(get = WXXW, put = WXXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> arra;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WXY() { return ExtractComponent<3, 3, 0, 1>(); } 
template <spv::StorageClass C1> void WXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 1>(_var); } 
__declspec(property(get = WXY, put = WXY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wxy;
__declspec(property(get = WXY, put = WXY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> arg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXYX() { return ExtractComponent<4, 3, 0, 1, 0>(); } 
template <spv::StorageClass C1> void WXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 1, 0>(_var); } 
__declspec(property(get = WXYX, put = WXYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxyx;
__declspec(property(get = WXYX, put = WXYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> argr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXYY() { return ExtractComponent<4, 3, 0, 1, 1>(); } 
template <spv::StorageClass C1> void WXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 1, 1>(_var); } 
__declspec(property(get = WXYY, put = WXYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxyy;
__declspec(property(get = WXYY, put = WXYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> argg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXYZ() { return ExtractComponent<4, 3, 0, 1, 2>(); } 
template <spv::StorageClass C1> void WXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 1, 2>(_var); } 
__declspec(property(get = WXYZ, put = WXYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxyz;
__declspec(property(get = WXYZ, put = WXYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> argb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXYW() { return ExtractComponent<4, 3, 0, 1, 3>(); } 
template <spv::StorageClass C1> void WXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 1, 3>(_var); } 
__declspec(property(get = WXYW, put = WXYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxyw;
__declspec(property(get = WXYW, put = WXYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> arga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WXZ() { return ExtractComponent<3, 3, 0, 2>(); } 
template <spv::StorageClass C1> void WXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 2>(_var); } 
__declspec(property(get = WXZ, put = WXZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wxz;
__declspec(property(get = WXZ, put = WXZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> arb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXZX() { return ExtractComponent<4, 3, 0, 2, 0>(); } 
template <spv::StorageClass C1> void WXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 2, 0>(_var); } 
__declspec(property(get = WXZX, put = WXZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxzx;
__declspec(property(get = WXZX, put = WXZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> arbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXZY() { return ExtractComponent<4, 3, 0, 2, 1>(); } 
template <spv::StorageClass C1> void WXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 2, 1>(_var); } 
__declspec(property(get = WXZY, put = WXZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxzy;
__declspec(property(get = WXZY, put = WXZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> arbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXZZ() { return ExtractComponent<4, 3, 0, 2, 2>(); } 
template <spv::StorageClass C1> void WXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 2, 2>(_var); } 
__declspec(property(get = WXZZ, put = WXZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxzz;
__declspec(property(get = WXZZ, put = WXZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> arbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXZW() { return ExtractComponent<4, 3, 0, 2, 3>(); } 
template <spv::StorageClass C1> void WXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 2, 3>(_var); } 
__declspec(property(get = WXZW, put = WXZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxzw;
__declspec(property(get = WXZW, put = WXZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> arba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WXW() { return ExtractComponent<3, 3, 0, 3>(); } 
template <spv::StorageClass C1> void WXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 0, 3>(_var); } 
__declspec(property(get = WXW, put = WXW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wxw;
__declspec(property(get = WXW, put = WXW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> ara;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXWX() { return ExtractComponent<4, 3, 0, 3, 0>(); } 
template <spv::StorageClass C1> void WXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 3, 0>(_var); } 
__declspec(property(get = WXWX, put = WXWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxwx;
__declspec(property(get = WXWX, put = WXWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> arar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXWY() { return ExtractComponent<4, 3, 0, 3, 1>(); } 
template <spv::StorageClass C1> void WXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 3, 1>(_var); } 
__declspec(property(get = WXWY, put = WXWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxwy;
__declspec(property(get = WXWY, put = WXWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> arag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXWZ() { return ExtractComponent<4, 3, 0, 3, 2>(); } 
template <spv::StorageClass C1> void WXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 3, 2>(_var); } 
__declspec(property(get = WXWZ, put = WXWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxwz;
__declspec(property(get = WXWZ, put = WXWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> arab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WXWW() { return ExtractComponent<4, 3, 0, 3, 3>(); } 
template <spv::StorageClass C1> void WXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 0, 3, 3>(_var); } 
__declspec(property(get = WXWW, put = WXWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wxww;
__declspec(property(get = WXWW, put = WXWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> araa;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> WY() { return ExtractComponent<2, 3, 1>(); } 
template <spv::StorageClass C1> void WY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 3, 1>(_var); } 
__declspec(property(get = WY, put = WY)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> wy;
__declspec(property(get = WY, put = WY)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> ag;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WYX() { return ExtractComponent<3, 3, 1, 0>(); } 
template <spv::StorageClass C1> void WYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 0>(_var); } 
__declspec(property(get = WYX, put = WYX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wyx;
__declspec(property(get = WYX, put = WYX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> agr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYXX() { return ExtractComponent<4, 3, 1, 0, 0>(); } 
template <spv::StorageClass C1> void WYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 0, 0>(_var); } 
__declspec(property(get = WYXX, put = WYXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wyxx;
__declspec(property(get = WYXX, put = WYXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> agrr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYXY() { return ExtractComponent<4, 3, 1, 0, 1>(); } 
template <spv::StorageClass C1> void WYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 0, 1>(_var); } 
__declspec(property(get = WYXY, put = WYXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wyxy;
__declspec(property(get = WYXY, put = WYXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> agrg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYXZ() { return ExtractComponent<4, 3, 1, 0, 2>(); } 
template <spv::StorageClass C1> void WYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 0, 2>(_var); } 
__declspec(property(get = WYXZ, put = WYXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wyxz;
__declspec(property(get = WYXZ, put = WYXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> agrb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYXW() { return ExtractComponent<4, 3, 1, 0, 3>(); } 
template <spv::StorageClass C1> void WYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 0, 3>(_var); } 
__declspec(property(get = WYXW, put = WYXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wyxw;
__declspec(property(get = WYXW, put = WYXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> agra;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WYY() { return ExtractComponent<3, 3, 1, 1>(); } 
template <spv::StorageClass C1> void WYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 1>(_var); } 
__declspec(property(get = WYY, put = WYY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wyy;
__declspec(property(get = WYY, put = WYY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> agg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYYX() { return ExtractComponent<4, 3, 1, 1, 0>(); } 
template <spv::StorageClass C1> void WYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 1, 0>(_var); } 
__declspec(property(get = WYYX, put = WYYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wyyx;
__declspec(property(get = WYYX, put = WYYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aggr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYYY() { return ExtractComponent<4, 3, 1, 1, 1>(); } 
template <spv::StorageClass C1> void WYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 1, 1>(_var); } 
__declspec(property(get = WYYY, put = WYYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wyyy;
__declspec(property(get = WYYY, put = WYYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aggg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYYZ() { return ExtractComponent<4, 3, 1, 1, 2>(); } 
template <spv::StorageClass C1> void WYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 1, 2>(_var); } 
__declspec(property(get = WYYZ, put = WYYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wyyz;
__declspec(property(get = WYYZ, put = WYYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aggb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYYW() { return ExtractComponent<4, 3, 1, 1, 3>(); } 
template <spv::StorageClass C1> void WYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 1, 3>(_var); } 
__declspec(property(get = WYYW, put = WYYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wyyw;
__declspec(property(get = WYYW, put = WYYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> agga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WYZ() { return ExtractComponent<3, 3, 1, 2>(); } 
template <spv::StorageClass C1> void WYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 2>(_var); } 
__declspec(property(get = WYZ, put = WYZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wyz;
__declspec(property(get = WYZ, put = WYZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> agb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYZX() { return ExtractComponent<4, 3, 1, 2, 0>(); } 
template <spv::StorageClass C1> void WYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 2, 0>(_var); } 
__declspec(property(get = WYZX, put = WYZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wyzx;
__declspec(property(get = WYZX, put = WYZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> agbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYZY() { return ExtractComponent<4, 3, 1, 2, 1>(); } 
template <spv::StorageClass C1> void WYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 2, 1>(_var); } 
__declspec(property(get = WYZY, put = WYZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wyzy;
__declspec(property(get = WYZY, put = WYZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> agbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYZZ() { return ExtractComponent<4, 3, 1, 2, 2>(); } 
template <spv::StorageClass C1> void WYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 2, 2>(_var); } 
__declspec(property(get = WYZZ, put = WYZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wyzz;
__declspec(property(get = WYZZ, put = WYZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> agbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYZW() { return ExtractComponent<4, 3, 1, 2, 3>(); } 
template <spv::StorageClass C1> void WYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 2, 3>(_var); } 
__declspec(property(get = WYZW, put = WYZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wyzw;
__declspec(property(get = WYZW, put = WYZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> agba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WYW() { return ExtractComponent<3, 3, 1, 3>(); } 
template <spv::StorageClass C1> void WYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 1, 3>(_var); } 
__declspec(property(get = WYW, put = WYW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wyw;
__declspec(property(get = WYW, put = WYW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> aga;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYWX() { return ExtractComponent<4, 3, 1, 3, 0>(); } 
template <spv::StorageClass C1> void WYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 3, 0>(_var); } 
__declspec(property(get = WYWX, put = WYWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wywx;
__declspec(property(get = WYWX, put = WYWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> agar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYWY() { return ExtractComponent<4, 3, 1, 3, 1>(); } 
template <spv::StorageClass C1> void WYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 3, 1>(_var); } 
__declspec(property(get = WYWY, put = WYWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wywy;
__declspec(property(get = WYWY, put = WYWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> agag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYWZ() { return ExtractComponent<4, 3, 1, 3, 2>(); } 
template <spv::StorageClass C1> void WYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 3, 2>(_var); } 
__declspec(property(get = WYWZ, put = WYWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wywz;
__declspec(property(get = WYWZ, put = WYWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> agab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WYWW() { return ExtractComponent<4, 3, 1, 3, 3>(); } 
template <spv::StorageClass C1> void WYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 1, 3, 3>(_var); } 
__declspec(property(get = WYWW, put = WYWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wyww;
__declspec(property(get = WYWW, put = WYWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> agaa;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> WZ() { return ExtractComponent<2, 3, 2>(); } 
template <spv::StorageClass C1> void WZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 3, 2>(_var); } 
__declspec(property(get = WZ, put = WZ)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> wz;
__declspec(property(get = WZ, put = WZ)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> ab;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WZX() { return ExtractComponent<3, 3, 2, 0>(); } 
template <spv::StorageClass C1> void WZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 0>(_var); } 
__declspec(property(get = WZX, put = WZX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wzx;
__declspec(property(get = WZX, put = WZX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> abr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZXX() { return ExtractComponent<4, 3, 2, 0, 0>(); } 
template <spv::StorageClass C1> void WZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 0, 0>(_var); } 
__declspec(property(get = WZXX, put = WZXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzxx;
__declspec(property(get = WZXX, put = WZXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abrr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZXY() { return ExtractComponent<4, 3, 2, 0, 1>(); } 
template <spv::StorageClass C1> void WZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 0, 1>(_var); } 
__declspec(property(get = WZXY, put = WZXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzxy;
__declspec(property(get = WZXY, put = WZXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abrg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZXZ() { return ExtractComponent<4, 3, 2, 0, 2>(); } 
template <spv::StorageClass C1> void WZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 0, 2>(_var); } 
__declspec(property(get = WZXZ, put = WZXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzxz;
__declspec(property(get = WZXZ, put = WZXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abrb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZXW() { return ExtractComponent<4, 3, 2, 0, 3>(); } 
template <spv::StorageClass C1> void WZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 0, 3>(_var); } 
__declspec(property(get = WZXW, put = WZXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzxw;
__declspec(property(get = WZXW, put = WZXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abra;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WZY() { return ExtractComponent<3, 3, 2, 1>(); } 
template <spv::StorageClass C1> void WZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 1>(_var); } 
__declspec(property(get = WZY, put = WZY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wzy;
__declspec(property(get = WZY, put = WZY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> abg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZYX() { return ExtractComponent<4, 3, 2, 1, 0>(); } 
template <spv::StorageClass C1> void WZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 1, 0>(_var); } 
__declspec(property(get = WZYX, put = WZYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzyx;
__declspec(property(get = WZYX, put = WZYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abgr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZYY() { return ExtractComponent<4, 3, 2, 1, 1>(); } 
template <spv::StorageClass C1> void WZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 1, 1>(_var); } 
__declspec(property(get = WZYY, put = WZYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzyy;
__declspec(property(get = WZYY, put = WZYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abgg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZYZ() { return ExtractComponent<4, 3, 2, 1, 2>(); } 
template <spv::StorageClass C1> void WZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 1, 2>(_var); } 
__declspec(property(get = WZYZ, put = WZYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzyz;
__declspec(property(get = WZYZ, put = WZYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abgb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZYW() { return ExtractComponent<4, 3, 2, 1, 3>(); } 
template <spv::StorageClass C1> void WZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 1, 3>(_var); } 
__declspec(property(get = WZYW, put = WZYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzyw;
__declspec(property(get = WZYW, put = WZYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WZZ() { return ExtractComponent<3, 3, 2, 2>(); } 
template <spv::StorageClass C1> void WZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 2>(_var); } 
__declspec(property(get = WZZ, put = WZZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wzz;
__declspec(property(get = WZZ, put = WZZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> abb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZZX() { return ExtractComponent<4, 3, 2, 2, 0>(); } 
template <spv::StorageClass C1> void WZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 2, 0>(_var); } 
__declspec(property(get = WZZX, put = WZZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzzx;
__declspec(property(get = WZZX, put = WZZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abbr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZZY() { return ExtractComponent<4, 3, 2, 2, 1>(); } 
template <spv::StorageClass C1> void WZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 2, 1>(_var); } 
__declspec(property(get = WZZY, put = WZZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzzy;
__declspec(property(get = WZZY, put = WZZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abbg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZZZ() { return ExtractComponent<4, 3, 2, 2, 2>(); } 
template <spv::StorageClass C1> void WZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 2, 2>(_var); } 
__declspec(property(get = WZZZ, put = WZZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzzz;
__declspec(property(get = WZZZ, put = WZZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abbb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZZW() { return ExtractComponent<4, 3, 2, 2, 3>(); } 
template <spv::StorageClass C1> void WZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 2, 3>(_var); } 
__declspec(property(get = WZZW, put = WZZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzzw;
__declspec(property(get = WZZW, put = WZZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WZW() { return ExtractComponent<3, 3, 2, 3>(); } 
template <spv::StorageClass C1> void WZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 2, 3>(_var); } 
__declspec(property(get = WZW, put = WZW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wzw;
__declspec(property(get = WZW, put = WZW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> aba;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZWX() { return ExtractComponent<4, 3, 2, 3, 0>(); } 
template <spv::StorageClass C1> void WZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 3, 0>(_var); } 
__declspec(property(get = WZWX, put = WZWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzwx;
__declspec(property(get = WZWX, put = WZWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZWY() { return ExtractComponent<4, 3, 2, 3, 1>(); } 
template <spv::StorageClass C1> void WZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 3, 1>(_var); } 
__declspec(property(get = WZWY, put = WZWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzwy;
__declspec(property(get = WZWY, put = WZWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZWZ() { return ExtractComponent<4, 3, 2, 3, 2>(); } 
template <spv::StorageClass C1> void WZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 3, 2>(_var); } 
__declspec(property(get = WZWZ, put = WZWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzwz;
__declspec(property(get = WZWZ, put = WZWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WZWW() { return ExtractComponent<4, 3, 2, 3, 3>(); } 
template <spv::StorageClass C1> void WZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 2, 3, 3>(_var); } 
__declspec(property(get = WZWW, put = WZWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wzww;
__declspec(property(get = WZWW, put = WZWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> abaa;
var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> WW() { return ExtractComponent<2, 3, 3>(); } 
template <spv::StorageClass C1> void WW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, 3, 3>(_var); } 
__declspec(property(get = WW, put = WW)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> ww;
__declspec(property(get = WW, put = WW)) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> aa;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WWX() { return ExtractComponent<3, 3, 3, 0>(); } 
template <spv::StorageClass C1> void WWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 0>(_var); } 
__declspec(property(get = WWX, put = WWX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wwx;
__declspec(property(get = WWX, put = WWX)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> aar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWXX() { return ExtractComponent<4, 3, 3, 0, 0>(); } 
template <spv::StorageClass C1> void WWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 0, 0>(_var); } 
__declspec(property(get = WWXX, put = WWXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwxx;
__declspec(property(get = WWXX, put = WWXX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aarr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWXY() { return ExtractComponent<4, 3, 3, 0, 1>(); } 
template <spv::StorageClass C1> void WWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 0, 1>(_var); } 
__declspec(property(get = WWXY, put = WWXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwxy;
__declspec(property(get = WWXY, put = WWXY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aarg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWXZ() { return ExtractComponent<4, 3, 3, 0, 2>(); } 
template <spv::StorageClass C1> void WWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 0, 2>(_var); } 
__declspec(property(get = WWXZ, put = WWXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwxz;
__declspec(property(get = WWXZ, put = WWXZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aarb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWXW() { return ExtractComponent<4, 3, 3, 0, 3>(); } 
template <spv::StorageClass C1> void WWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 0, 3>(_var); } 
__declspec(property(get = WWXW, put = WWXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwxw;
__declspec(property(get = WWXW, put = WWXW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aara;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WWY() { return ExtractComponent<3, 3, 3, 1>(); } 
template <spv::StorageClass C1> void WWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 1>(_var); } 
__declspec(property(get = WWY, put = WWY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wwy;
__declspec(property(get = WWY, put = WWY)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> aag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWYX() { return ExtractComponent<4, 3, 3, 1, 0>(); } 
template <spv::StorageClass C1> void WWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 1, 0>(_var); } 
__declspec(property(get = WWYX, put = WWYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwyx;
__declspec(property(get = WWYX, put = WWYX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aagr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWYY() { return ExtractComponent<4, 3, 3, 1, 1>(); } 
template <spv::StorageClass C1> void WWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 1, 1>(_var); } 
__declspec(property(get = WWYY, put = WWYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwyy;
__declspec(property(get = WWYY, put = WWYY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aagg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWYZ() { return ExtractComponent<4, 3, 3, 1, 2>(); } 
template <spv::StorageClass C1> void WWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 1, 2>(_var); } 
__declspec(property(get = WWYZ, put = WWYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwyz;
__declspec(property(get = WWYZ, put = WWYZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aagb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWYW() { return ExtractComponent<4, 3, 3, 1, 3>(); } 
template <spv::StorageClass C1> void WWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 1, 3>(_var); } 
__declspec(property(get = WWYW, put = WWYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwyw;
__declspec(property(get = WWYW, put = WWYW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aaga;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WWZ() { return ExtractComponent<3, 3, 3, 2>(); } 
template <spv::StorageClass C1> void WWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 2>(_var); } 
__declspec(property(get = WWZ, put = WWZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> wwz;
__declspec(property(get = WWZ, put = WWZ)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> aab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWZX() { return ExtractComponent<4, 3, 3, 2, 0>(); } 
template <spv::StorageClass C1> void WWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 2, 0>(_var); } 
__declspec(property(get = WWZX, put = WWZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwzx;
__declspec(property(get = WWZX, put = WWZX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aabr;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWZY() { return ExtractComponent<4, 3, 3, 2, 1>(); } 
template <spv::StorageClass C1> void WWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 2, 1>(_var); } 
__declspec(property(get = WWZY, put = WWZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwzy;
__declspec(property(get = WWZY, put = WWZY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aabg;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWZZ() { return ExtractComponent<4, 3, 3, 2, 2>(); } 
template <spv::StorageClass C1> void WWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 2, 2>(_var); } 
__declspec(property(get = WWZZ, put = WWZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwzz;
__declspec(property(get = WWZZ, put = WWZZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aabb;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWZW() { return ExtractComponent<4, 3, 3, 2, 3>(); } 
template <spv::StorageClass C1> void WWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 2, 3>(_var); } 
__declspec(property(get = WWZW, put = WWZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwzw;
__declspec(property(get = WWZW, put = WWZW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aaba;
var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> WWW() { return ExtractComponent<3, 3, 3, 3>(); } 
template <spv::StorageClass C1> void WWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, 3, 3, 3>(_var); } 
__declspec(property(get = WWW, put = WWW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> www;
__declspec(property(get = WWW, put = WWW)) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> aaa;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWWX() { return ExtractComponent<4, 3, 3, 3, 0>(); } 
template <spv::StorageClass C1> void WWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 3, 0>(_var); } 
__declspec(property(get = WWWX, put = WWWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwwx;
__declspec(property(get = WWWX, put = WWWX)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aaar;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWWY() { return ExtractComponent<4, 3, 3, 3, 1>(); } 
template <spv::StorageClass C1> void WWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 3, 1>(_var); } 
__declspec(property(get = WWWY, put = WWWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwwy;
__declspec(property(get = WWWY, put = WWWY)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aaag;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWWZ() { return ExtractComponent<4, 3, 3, 3, 2>(); } 
template <spv::StorageClass C1> void WWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 3, 2>(_var); } 
__declspec(property(get = WWWZ, put = WWWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwwz;
__declspec(property(get = WWWZ, put = WWWZ)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aaab;
var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> WWWW() { return ExtractComponent<4, 3, 3, 3, 3>(); } 
template <spv::StorageClass C1> void WWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, 3, 3, 3, 3>(_var); } 
__declspec(property(get = WWWW, put = WWWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> wwww;
__declspec(property(get = WWWW, put = WWWW)) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> aaaa;
#endif // !TRACY_SPIRVVECTORCOMPONENTACCESS_H
