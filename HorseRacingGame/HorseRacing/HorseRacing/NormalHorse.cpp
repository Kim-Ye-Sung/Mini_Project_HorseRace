#include "pch.h"
#include "NormalHorse.h"

#include <direct.h>

NormalHorse::NormalHorse()
{
	HRESULT hr = GetHorseImage().Load(L"Horse1.png");	// 소스코드들이 있는 폴더에서 사진을 찾아라.

	if (FAILED(hr))	// 사진을 못찾으면 디버그 텍스트 출력
	{
		AfxMessageBox(L"Horse1.png 로드 실패");
	}
}

void NormalHorse::AddPosition()
{

}

