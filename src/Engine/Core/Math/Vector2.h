//The MIT License
//
//Copyright(c) 2018 - 2019 littleblue
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//copies of the Software, and to permit persons to whom the Software is furnished
//to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
//COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "../EngineDefs.h"
#include <string>
#include "im.h"

using namespace glm;

namespace TmingEngine
{
	ENGINE_CLASS class Vector2
	{
	public:
		float x = 0;
		float y = 0;

		Vector2()
		{
		}

		//���ǲ�ϣ������������ж��������и�ֵ�ġ�ԭ�桱���κ��޸ġ���������const��׺�������Ǳ��������������޸����Ա������
		//����const������const�ĺͷ�const��ʵ�Σ��������ܽ��ܣ�������ӣ���ֻ�ܽ��ܷ�const��ʵ�Ρ�
		//�������Ա����ں�������ʱ��ʵ�ε�һ�ο����������Ч�ʡ�
		Vector2 operator - (const Vector2& v) const
		{
			return Vector2(x - v.x, y - v.y);
		}

		Vector2 operator + (const Vector2& v) const
		{
			return Vector2(x + v.x, y + v.y);
		}

		Vector2 operator * (const int num) const
		{
			return Vector2(x * num, y * num);
		}
		
		//��Ӧ�����ֵ����˲����,ͨ�����ڼ��������ļн�
		// A * B = |A|*|B|*Cos(��)=(a1*b1 + a2*b2 + ... + an*bn)
		float Dot(Vector2& v)
		{
			return  x * v.x + y * v.y;
		}

		//б�Խ���� �����
		float Cross(Vector2& v)
		{
			return  x * v.y - v.x * y;
		}

		Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		operator ImVec2()
		{
			return ImVec2(x, y);
		}

		operator vec2()
		{
			return vec2(x, y);
		}

		static const Vector2 Zero;
		static const Vector2 One;
		std::string ToString() const;
	};
}
