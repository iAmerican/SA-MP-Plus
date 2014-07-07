#include "CLocalPlayer.h"
#include "Network/CRPCCallback.h"
#include "Network/Network.h"

DWORD CLocalPlayer::m_actionMemory[ePlayerAction::COUNT - 1] =
{
	0xB7CE20,
	0xB73571,
	0xB73572,
	0xB73573,
	0xB73574,
	0xB73575,
	0xB73576
};

void CLocalPlayer::SetActionEnabled(unsigned char action, bool bEnabled)
{
	if (action >= ePlayerAction::COUNT)
		return;

	if (action == ePlayerAction::ALL)
	{
		for (unsigned char i = 1; i < ePlayerAction::COUNT; ++i)
			SetActionEnabled(i, bEnabled);

	}
	else
		CMem::PutSingle<BYTE>(m_actionMemory[action-1], !bEnabled);

}

// TODO: make cancellable
void CLocalPlayer::OnDriveByShot()
{
	Network::SendRPC(eRPC::ON_DRIVE_BY_SHOT);
}

void CLocalPlayer::OnStuntBonus(sStuntDetails* pStuntDetails)
{
	RakNet::BitStream bitStream;
	bitStream.Write(*pStuntDetails);

	Network::SendRPC(eRPC::ON_STUNT_BONUS, &bitStream);
}

void CLocalPlayer::SetClipAmmo(BYTE bSlot, int bAmmo)
{
	DWORD address = ((*(int*)0xB6F5F0) + 0x588) + (0x28 * bSlot) + 0x8;
	CMem::PutSingle<int>(address, bAmmo);
}

void CLocalPlayer::SetNoReload(bool toggle) {
	if (toggle) 
	{
		CMem::PutSingle<BYTE>(0x07428AB, 0x90);
		CMem::PutSingle<BYTE>(0x07428AC, 0x90);
	}
	else
	{
		CMem::PutSingle<BYTE>(0x07428AB, 0x85); // test eax,eax
		CMem::PutSingle<BYTE>(0x07428AC, 0xC0);
	}
}