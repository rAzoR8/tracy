#ifndef TRACY_GENERATESWIZZLEHEADER_H
#define TRACY_GENERATESWIZZLEHEADER_H

#include <fstream>
void GenerateSwizzleHeader()
{
	char ups[4] = { 'X', 'Y', 'Z', 'W' };
	char lows[2][4] = { { 'x', 'y', 'z', 'w' },{ 'r', 'g', 'b', 'a' } };

	std::ofstream out("SPIRVVectorComponentAccess.h");

	if (out.is_open())
	{
		out << "#ifndef TRACY_SPIRVVECTORCOMPONENTACCESS_H" << std::endl;
		out << "#define TRACY_SPIRVVECTORCOMPONENTACCESS_H" << std::endl;

		for (uint32_t x = 0; x < 4; ++x)
		{
			// getter
			out << "var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction> "
				<< ups[x] << "() { return ExtractComponent<1, "
				<< x << ">(); } " << std::endl;

			// setter
			out << "template <spv::StorageClass C1> void "
				<< ups[x] << "(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) { InsertComponent<1, "
				<< x << ">(_var); } " << std::endl;

			// property
			for (uint32_t l = 0; l < 2; ++l)
			{
				out << "__declspec(property(get = " << ups[x] << ", put = " << ups[x] <<
					")) var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction> " << lows[l][x] << ";" << std::endl;
			}

			for (uint32_t y = 0; y < 4; ++y)
			{
				// getter
				out << "var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> "
					<< ups[x] << ups[y] << "() { return ExtractComponent<2, "
					<< x << ", " << y << ">(); } " << std::endl;

				// setter
				out << "template <spv::StorageClass C1> void "
					<< ups[x] << ups[y] << "(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) { InsertComponent<2, "
					<< x << ", " << y << ">(_var); } " << std::endl;

				// property
				for (uint32_t l = 0; l < 2; ++l)
				{
					out << "__declspec(property(get = " << ups[x] << ups[y] << ", put = " << ups[x] << ups[y] <<
						")) var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction> " << lows[l][x] << lows[l][y] << ";" << std::endl;
				}

				for (uint32_t z = 0; z < 4; ++z)
				{
					// getter
					out << "var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> "
						<< ups[x] << ups[y] << ups[z] << "() { return ExtractComponent<3, "
						<< x << ", " << y << ", " << z << ">(); } " << std::endl;

					// setter
					out << "template <spv::StorageClass C1> void "
						<< ups[x] << ups[y] << ups[z] << "(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) { InsertComponent<3, "
						<< x << ", " << y << ", " << z << ">(_var); } " << std::endl;

					// property
					for (uint32_t l = 0; l < 2; ++l)
					{
						out << "__declspec(property(get = " << ups[x] << ups[y] << ups[z] << ", put = " << ups[x] << ups[y] << ups[z] <<
							")) var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction> " << lows[l][x] << lows[l][y] << lows[l][z] << ";" << std::endl;
					}

					for (uint32_t w = 0; w < 4; ++w)
					{
						// getter
						out << "var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> "
							<< ups[x] << ups[y] << ups[z] << ups[w] << "() { return ExtractComponent<4, "
							<< x << ", " << y << ", " << z << ", " << w << ">(); } " << std::endl;

						// setter
						out << "template <spv::StorageClass C1> void "
							<< ups[x] << ups[y] << ups[z] << ups[w] << "(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) { InsertComponent<4, "
							<< x << ", " << y << ", " << z << ", " << w << ">(_var); } " << std::endl;

						// property
						for (uint32_t l = 0; l < 2; ++l)
						{
							out << "__declspec(property(get = " << ups[x] << ups[y] << ups[z] << ups[w] << ", put = " << ups[x] << ups[y] << ups[z] << ups[w] <<
								")) var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction> " << lows[l][x] << lows[l][y] << lows[l][z] << lows[l][w] << ";" << std::endl;
						}
					}
				}
			}
		}

		out << "#endif // !TRACY_SPIRVVECTORCOMPONENTACCESS_H" << std::endl;
	}

	out.close();
}

#endif // !TRACY_GENERATESWIZZLEHEADER_H
