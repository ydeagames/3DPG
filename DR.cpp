#include "pch.h"

#include "DR.h"

// �V���O���g��static�|�C���^
DR* DR::s_dr = nullptr;

DR::DR()
	: m_deviceResources(nullptr)
{
	// ��x�ڂ͂Ȃ�
	if (s_dr)
		throw std::exception("DR is a singleton");
	m_deviceResources = std::make_unique<DX::DeviceResources>();
	// static�|�C���^�ɃZ�b�g
	s_dr = this;
}

DR::~DR()
{
	// static�|�C���^���폜
	s_dr = nullptr;
}

// �A���[�Ăяo��
DX::DeviceResources* DR::operator->() const
{
	// �|�C���^�ԋp
	return m_deviceResources.get();
}

// �V���O���g��
DR& DR::Get()
{
	// ���������K�v
	if (!s_dr)
		throw std::exception("DR is a singleton");
	// �V���O���g���|�C���^�ԋp
	return *s_dr;
}
