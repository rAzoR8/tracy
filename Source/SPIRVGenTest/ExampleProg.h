#ifndef TRACY_EXAMPLEPROG_H
#define TRACY_EXAMPLEPROG_H

#include "SPIRVProgram.h"
#include "SPIRVAssembler.h"

namespace Tracy
{
	template <bool Assemble>
	class ExampleProg : public SPIRVProgram<Assemble>
	{
	public:
		ExampleProg() : SPIRVProgram<Assemble>(){};
		~ExampleProg() {};

		struct B
		{
			SPVStruct
			float2 UVCoord = "UVCoords";
			float2 Offset;

			u32 SampleCount;
		};

		struct PushBlock
		{
			SPVStruct
			float4 stuff;
		};

		CBuffer<B> BufferBlock;
		RenderTarget OutputColor;
		SamplerState Sampler;
		Texture2DEx<float3_t> InputImg;
		//SubPassColor SubPass;
		PushConstant<PushBlock> Push;
		Array<float3_t, 4> TestArray;

		inline void operator()()
		{
			u32 size = TestArray.Length();
			f32 sum = 0.f;

			complex z1(3.0f, 4.0f);
			complex z2(3.0f, -2.0f);

			z1 *= z2;
			
			If(sum < 2.f)
			{
				sum += 2.f;
			}
			Else
			{
				sum -= 1.f;
			});

			//u32 uVertexID(1);
			auto id1 = (kVertexIndex & 1) << 2;
			auto id2 = (kInstanceIndex & 2) << 1;

			For(u32 e = 0u, e < size, ++e)
			{
				auto elem = TestArray[e];
				sum += Length(elem);
			});

			float3x4 m34;

			float3 v3 = { 1.f, 2.f, 3.f };
			float3 a, b, c;

			matrix m;

			m = Inverse(m);
			auto det = Determinant(m);

			c = Atan2(a, b);
			b = Pow(c, a);
			a = Exp2(c);
			c = Log(a);
			b = InvSqrt(a + b);
			a = Reflect(b, Normalize(c));
			b = Refract(a, c, 0.5f);

			v3 = Fma(a, float3{ 1.f, 2.f, 3.f }, c);
			//v3 = Cross(a, b) * Dot(a, c);
			quaternion q1 = quaternion(v3, sum);
			quaternion q2;

			auto q = q1 * q2;
			q *= q2;

			auto sp = SpecConst<float>(2.f);

			auto res = m34 * v3 * sp; // instead of using mul
			auto k = Length(res.xyz);

			float2 offset = BufferBlock->Offset;
			For(u32 i = 0u, i < BufferBlock->SampleCount, ++i)
			{
				OutputColor.rgb = InputImg.Sample(Sampler, BufferBlock->UVCoord + offset);
				OutputColor.a = Length(OutputColor.rgb);
			});
		};
	private:
	};

}; // !Tracy

#endif // !TRACY_EXAMPLEPROG_H
