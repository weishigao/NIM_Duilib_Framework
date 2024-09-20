#ifndef UI_CONTROL_NUMBEREDIT_H_
#define UI_CONTROL_NUMBEREDIT_H_

#pragma once

namespace ui 
{

	class UILIB_API NumberEdit : public RichEdit
	{
	public:

	public:
		NumberEdit();
		NumberEdit(const NumberEdit& r) = delete;
		NumberEdit& operator=(const NumberEdit& r) = delete;

		/**
		 * @brief �ж��Ƿ��֧������
		 * @return ���� true ��ʾ��
		 */
		bool IsIntOnly();

		/**
		 * @brief �����Ƿ��֧������
		 * @param[in] bIntOnly Ϊ true ��ֻ������������false Ϊʵ��
		 * @return ��
		 */
		void SetIntOnly(bool bIntOnly = false);

		/**
		 * @brief �ж��Ƿ�������
		 * @return ���� true ��ʾ����
		 */
		bool IsAllowNegative();

		/**
		 * @brief �����Ƿ�������
		 * @param[in] bIntOnly Ϊ true ���������븺��
		 * @return ��
		 */
		void SetAllowNegative(bool bAllowNegative = false);

		 /**
		  * @brief �����ı�������ֵ
		  */
		int GetIntValue(int def = 0);

		/**
		 * @brief �����ı���ʵ��ֵ
		 */
		double GetValue(double def=0);

		/**
		 * @brief ���ı�������һ������ֵ
		 */
		void SetValue(int value);

		/**
		 * @brief ���ı�������һ��ʵ��ֵ
		 */
		void SetValue(double value);

		/**
         * @brief �ж��Ƿ������ֵ����
         * @return ���� true ��ʾ��
        */
		bool IsMaxValueEnabled();

		/**
		 * @brief �����Ƿ������ֵ����
		 * @param[in] bMaxValueEnabled Ϊ true ����
		 * @return ��
		 */
		void SetMaxValueEnabled(bool bMaxValueEnabled = false);

		/**
		 * @brief �ж��Ƿ�����Сֵ����
		 * @return ���� true ��ʾ��
		*/
		bool IsMinValueEnabled();

		/**
		 * @brief �����Ƿ�����Сֵ����
		 * @param[in] bMinValueEnabled Ϊ true ����
		 * @return ��
		 */
		void SetMinValueEnabled(bool bMinValueEnabled = false);

		/**
		 * @brief �������ֵ�趨
		 */
		int GetMaxValue();

		/**
		 * @brief �������ֵ
		 */
		void SetMaxValue(int value);

		/**
		 * @brief ������Сֵ�趨
		 */
		int GetMinValue();

		/**
		 * @brief ������Сֵ
		 */
		void SetMinValue(int value);

		 /**
		  * @brief ���ÿؼ����ı�
		  * @param[in] strText Ҫ���õ��ı�����
		  * @return ��
		  */
		virtual void SetText(const std::wstring& strText) override;

		virtual void OnChar(EventArgs& event) override;
		virtual void OnKeyDown(EventArgs& event) override;
		virtual bool OnTxTextChanged() override;

		virtual void SetAttribute(const std::wstring& pstrName, const std::wstring& pstrValue) override;

	protected:
		bool m_bIntOnly; //��֧������ Ĭ�Ϸ�
		bool m_bAllowNegative; //������ Ĭ�Ϸ�
		bool m_bMaxValueEnabled; //�������ֵ����
		bool m_bMinValueEnabled; //������Сֵ����
		int m_iMaxValue; //���ֵ
		int m_iMinValue; //��Сֵ
	private:
		std::wstring _ToNumberStr(std::wstring str);
	};
	

} // namespace ui

#endif // UI_CONTROL_RICHEDIT_H_
