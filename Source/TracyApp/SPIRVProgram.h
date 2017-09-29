#ifndef TRACY_SPIRVPROGRAM_H
#define TRACY_SPIRVPROGRAM_H

#include "SPIRVConstant.h"
#include "SPIRVInstruction.h"
#include <unordered_map>
#include <variant>

#include "SPIRVVariable.h"
namespace Tracy
{
	template <bool Assemble>
	class SPIRVProgram
	{
	public:
		SPIRVProgram();
		~SPIRVProgram();

		void Execute();

		// does not work as member:
		//float operator+(const float& l, const float& r);

		uint32_t NextId() { return m_uId++; }

		template <class T>
		var<T, Assemble>& make_var(const T& _Val = {}, const std::string& _sName = {}); // creates a new variable

	private:
		size_t AddConstant(const SPIRVConstant& _Const);

	private:
		uint32_t m_uId = 0u;// internal id
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
	inline size_t SPIRVProgram<Assemble>::AddConstant(const SPIRVConstant& _Const)
	{
		const size_t uHash = _Const.GetHash();
		if (m_Constants.count(uHash) == 0ull)
		{
			m_Constants.insert({ uHash, _Const });
		}

		return uHash;
	}

	template<bool Assemble>
	template<class T>
	inline var<T, Assemble>& SPIRVProgram<Assemble>::make_var(const T& _Val, const std::string& _sName)
	{
		var<T, Assemble> new_var(this, _sName, _Val);
		size_t uConst = AddConstant(SPIRVConstant::Make(_Val));

		// TODO: create OpVariable instr
		m_Variables.push_back(std::move(new_var));
		return std::get<var<T, Assemble>>(m_Variables.back());
	}

	template <bool Assemble>
	inline var<float, Assemble> operator+(const var<float, Assemble>& l, const var<float, Assemble>& r)
	{
		float val = l.Value + r.Value;
		// intermediate values?
		if constexpr(Assemble)
		{
			auto v = l.pParent->make_var<float, true>(l.pParent, "imm", val);
			v.uImmediateId = l.pParent->NextId();
			// TODO: create instruction etc
			return v;
		}
		else
		{
			return var<float, false>(val);
		}
	}

}; // !Tracy

#endif // !TRACY_SPIRVPROGRAM_H
