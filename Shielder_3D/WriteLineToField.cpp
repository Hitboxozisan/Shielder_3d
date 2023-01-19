#include "Pch.h"
#include "WriteLineToField.h"

WriteLineToField::WriteLineToField()
{
	lineAreaSize = 10000.0f;
	lineNum = 50;
}

/// <summary>
///  //ˆÊ’uŠÖŒW‚ª•ª‚©‚é‚æ‚¤‚É’n–Ê‚Éƒ‰ƒCƒ“‚ð•`‰æ‚·‚é
/// </summary>
void WriteLineToField::WriteLine()
{
	int i;
	VECTOR Pos1;
	VECTOR Pos2;

	SetUseZBufferFlag(TRUE);

	Pos1 = VGet(-lineAreaSize / 2.0f, 0.0f, -lineAreaSize / 2.0f);
	Pos2 = VGet(-lineAreaSize / 2.0f, 0.0f, lineAreaSize / 2.0f);
	for (i = 0; i <= lineNum; i++)
	{
		DrawLine3D(Pos1, Pos2, GetColor(0, 200, 0));
		Pos1.x += lineAreaSize / lineNum;
		Pos2.x += lineAreaSize / lineNum;
	}

	Pos1 = VGet(-lineAreaSize / 2.0f, 0.0f, -lineAreaSize / 2.0f);
	Pos2 = VGet(lineAreaSize / 2.0f, 0.0f, -lineAreaSize / 2.0f);
	for (i = 0; i < lineNum; i++)
	{
		DrawLine3D(Pos1, Pos2, GetColor(0, 200, 0));
		Pos1.z += lineAreaSize / lineNum;
		Pos2.z += lineAreaSize / lineNum;
	}

	SetUseZBufferFlag(FALSE);
	
}
