#ifndef TRACY_SPIRVPROGRAM_H
#define TRACY_SPIRVPROGRAM_H

#include "SPIRVConstant.h"
#include <unordered_map>
#include <variant>

namespace Tracy
{
	//forward decls
	template <bool Assemble>
	class SPIRVProgram;

	template <bool Assemble>
	struct var_decoration{};

	template <>
	struct var_decoration<true>
	{
		var_decoration(SPIRVProgram<true>* _pParent, const std::string& _sName) :
			pParent(_pParent), sName(_sName) {}
		SPIRVProgram<true> const* pParent;
		const std::string sName;
	};

	template <>
	struct var_decoration<false>
	{
		template <class... Ts>
		var_decoration(Ts ... _args) {} // consume arguments
	};

	template <typename T, bool Assemble = true>
	struct var : public var_decoration<Assemble>
	{
		var(SPIRVProgram<Assemble>* _pParent, const std::string& _sName, const T& _Val = {}) :
			var_decoration<Assemble>(_pParent, _sName), Value(_Val) {}

		var(const T& _Val) : var_decoration<Assemble>(), Value(_Val) {}
		T Value;
	};

	template <bool Assemble>
	class SPIRVProgram
	{
	public:
		SPIRVProgram();
		~SPIRVProgram();

		void Execute();

		// does not work as member:
		//float operator+(const float& l, const float& r);

		template <class T>
		var<T, Assemble>& make_var(const T& _Val = {}, const std::string& _sName = {}); // creates a new variable
	private:
		
		// todo: add vector and matrix types
		using spv_types = std::variant<var<int32_t, Assemble>, var<uint32_t, Assemble>, var<float, Assemble>>;

		std::vector<spv_types> m_Variables;

		std::unordered_map<size_t, SPIRVType> m_Types;
		std::unordered_map<size_t, SPIRVConstant> m_Constants;
	};

	template <bool Assemble>
	SPIRVProgram<Assemble>::SPIRVProgram()
	{
		m_Variables.reserve(4096);
	}

	template <bool Assemble>
	SPIRVProgram<Assemble>::~SPIRVProgram()
	{
	}

	// currently just test code
	template <bool Assemble>
	void SPIRVProgram<Assemble>::Execute()
	{
		auto& f1 = make_var<float>(1.f);
		auto& f2 = make_var<float>(2.f);

		auto f3 = f1 + f2;
	}

	template<bool Assemble>
	template<class T>
	inline var<T, Assemble>& SPIRVProgram<Assemble>::make_var(const T & _Val, const std::string & _sName)
	{
		// todo: check if variable with same name exists, if a name is used
		m_Variables.push_back(std::move(var<T, Assemble>(this, _sName, _Val)));
		return std::get<var<T, Assemble>>(m_Variables.back());
	}

	template <bool Assemble>
	inline var<float, Assemble> operator+(const var<float, Assemble>& l, const var<float, Assemble>& r)
	{
		float val = l.Value + r.Value;
		// intermediate values?
		if constexpr(Assemble)
		{
			// TODO: create instruction etc
			return l.pParent->make_var<float, true>(l.pParent, "imm", val);
		}
		else
		{
			return var<float, false>(val);
		}
	}

}; // !Tracy

#endif // !TRACY_SPIRVPROGRAM_H
