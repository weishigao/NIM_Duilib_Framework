#include "stdafx.h"
#include "base/thread/thread_manager.h"
#include <sstream>
// These constants are for backward compatibility. They are the 
// sizes used for initialization and reset in RichEdit 1.0

namespace ui {

	template <typename T1>
	T1 StringToNum(const std::string& input, const T1 def) {
		std::istringstream iss(input);
		T1 num;
		iss >> num;
		if (iss.fail()) {
			return def;
		}
		else {
			return num;
		}
	}
	
	NumberEdit::NumberEdit() : 
		RichEdit(), 
		m_bIntOnly(false),
		m_bAllowNegative(false),
		m_bMaxValueEnabled(false), 
		m_iMaxValue(0),
	    m_bMinValueEnabled(false),
	    m_iMinValue(0) //��Сֵ
	{
		m_bWantTab = false;
		m_lTwhStyle &= ~ES_MULTILINE;
	}

	bool NumberEdit::IsIntOnly()
	{
		return m_bIntOnly;
	}

	void NumberEdit::SetIntOnly(bool bIntOnly)
	{
		m_bIntOnly = bIntOnly;
	}

	bool NumberEdit::IsAllowNegative()
	{
		return m_bAllowNegative;
	}

	void NumberEdit::SetAllowNegative(bool bAllowNegative)
	{
		m_bAllowNegative = bAllowNegative;
	}

	int NumberEdit::GetIntValue(int def)
	{
		return StringToNum<int>(GetUTF8Text(), def);
	}

	double NumberEdit::GetValue(double def)
	{
		return StringToNum<double>(GetUTF8Text(), def);
	}

	void NumberEdit::SetValue(int value)
	{
		SetText(std::to_wstring(value));
	}

	void NumberEdit::SetValue(double value)
	{
		SetText(std::to_wstring(value));
	}

	bool NumberEdit::IsMaxValueEnabled()
	{
		return m_bMaxValueEnabled;
	}

	void NumberEdit::SetMaxValueEnabled(bool bMaxValueEnabled)
	{
		m_bMaxValueEnabled = bMaxValueEnabled;
	}

	bool NumberEdit::IsMinValueEnabled()
	{
		return m_bMinValueEnabled;
	}

	void NumberEdit::SetMinValueEnabled(bool bMinValueEnabled)
	{
		m_bMinValueEnabled = bMinValueEnabled;
	}

	int NumberEdit::GetMaxValue()
	{
		return m_iMaxValue;
	}

	void NumberEdit::SetMaxValue(int value)
	{
		m_iMaxValue = value;
	}

	int NumberEdit::GetMinValue()
	{
		return m_iMinValue;
	}

	void NumberEdit::SetMinValue(int value)
	{
		m_iMinValue = value;
	}
	void NumberEdit::SetText(const std::wstring & strText)
	{
		std::wstring strNum = _ToNumberStr(strText);
		m_sText = strNum;
		if (!m_bInited)
			return;

		SetSel(0, -1);
		ReplaceSel(strNum, FALSE);

		m_linkInfo.clear();
	}

	void NumberEdit::OnChar(EventArgs& event)
	{
		//TAB
		if (::GetKeyState(VK_TAB) < 0) 
		{
			if (m_pWindow != NULL)
				m_pWindow->SendNotify((Control*)this, kEventTab);

			return;
		}

		if (event.wParam < '0' || event.wParam > '9') //������Ƿ�����
		{
			if (event.wParam == 46) //�������С����
			{
				if (m_bIntOnly) //�����֧������
				{
					return;
				}
				else
				{
					if (GetTextLength() == 0) 
					{
						return;
					}
					else if (GetText().find('.') != -1) 
					{
						return;
					}
					else if ((GetTextLength() == 1) && (GetText().find('-') == 0)) 
					{
						return;
					}
				}
			}
			else if (event.wParam == 45) //������Ǽ���
			{
				if (!m_bAllowNegative) //�����������
				{
					return;
				}
				else
				{
					if (GetTextLength() > 0) 
					{
						return;
					}
					else if (GetText().find('-') != -1) 
					{
						return;
					}
				}
			}
			else
			{
				return;
			}
		}

		TxSendMessage(WM_CHAR, event.wParam, event.lParam, NULL);
	}

	void NumberEdit::OnKeyDown(EventArgs & event)
	{
		if (event.wParam == VK_RETURN && ::GetAsyncKeyState(VK_SHIFT) >= 0)
		{
			if (m_bNeedReturnMsg && ((m_bReturnMsgWantCtrl && ::GetAsyncKeyState(VK_CONTROL) < 0) ||
				(!m_bReturnMsgWantCtrl && ::GetAsyncKeyState(VK_CONTROL) >= 0)))
			{
				if (m_pWindow != NULL)
					m_pWindow->SendNotify((Control*)this, kEventReturn);
				return;
			}
		}
		else if (event.wParam == 'V' && ::GetKeyState(VK_CONTROL) < 0) {
			std::wstring strClipText;
			GetClipboardText(strClipText);
			if (!strClipText.empty()) 
			{
				std::wstring strNum = _ToNumberStr(strClipText);
				SetClipBoardText(strNum); //�޸ļ��а�����Ϊ������
				nbase::ThreadManager::PostTask([strClipText]() { SetClipBoardText(strClipText); }); //ճ������ְѼ��а����ݸĻ���
			}
		}

		TxSendMessage(WM_KEYDOWN, event.wParam, event.lParam, NULL);
	}

	bool NumberEdit::OnTxTextChanged()
	{
		if (m_pWindow != NULL) {
			if (m_bMaxValueEnabled) {
				if (GetValue() > m_iMaxValue) {
					SetValue(m_iMaxValue);
				}
			}

			if (m_bMinValueEnabled) {
				if (GetValue() < m_iMinValue) {
					SetValue(m_iMinValue);
				}
			}

			m_pWindow->SendNotify(this, kEventTextChange);
		}

		return true;
	}
	void NumberEdit::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
	{
		if (strName == _T("number")) {}
		else if (strName == _T("wanttab")) {}
		else if (strName == _T("multiline")) {}
		else if (strName == _T("intonly")) SetIntOnly(strValue == _T("true"));
		else if (strName == _T("allownegative")) SetAllowNegative(strValue == _T("true"));
		else if (strName == _T("maxvalueenabled")) SetMaxValueEnabled(strValue == _T("true"));
		else if (strName == _T("minvalueenabled")) SetMinValueEnabled(strValue == _T("true"));
		else if (strName == _T("maxvalue")) SetMaxValue(std::stoi(strValue));
		else if (strName == _T("minvalue")) SetMinValue(std::stoi(strValue));
		else RichEdit::SetAttribute(strName, strValue);
	}

	std::wstring NumberEdit::_ToNumberStr(std::wstring str)
	{
		std::wstring strNum;
		for (auto it = str.begin(); it != str.end(); it++)
		{
			if ((*it) <= L'9' && (*it) >= L'0') {
				strNum.push_back((*it));
			}
			else if ((*it) == L'.')
			{
				if (!m_bIntOnly) //���֧��ʵ��
				{
					if ((strNum.length() == 0) || ((strNum.length() == 1) && (strNum.find('-') == 0))) //������������ݵ���λ��ǰ���0
					{
						strNum += L"0.";
						//strNum.push_back((L'0'));
						//strNum.push_back((*it));
					}
					else if (strNum.find('.') == -1) //�����δ��С���㣬����˴�����
					{
						strNum.push_back((*it));
					}
				}
			}
			else if ((*it) == L'-')
			{
				if (m_bAllowNegative) //���������
				{
					if (strNum.length() == 0) //������������ݵ���λ������
					{
						strNum.push_back((*it));
					}
				}
			}
		}

		return strNum;
	}

} // namespace ui
