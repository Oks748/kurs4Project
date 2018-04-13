#pragma once

namespace kursProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnOverview;
	private: System::Windows::Forms::Button^  btnDo;
	private: System::Windows::Forms::Button^  btnAddNewPict;
	private: System::Windows::Forms::Button^  btnClear;
	protected:



	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnOverview = (gcnew System::Windows::Forms::Button());
			this->btnDo = (gcnew System::Windows::Forms::Button());
			this->btnAddNewPict = (gcnew System::Windows::Forms::Button());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// btnOverview
			// 
			this->btnOverview->Location = System::Drawing::Point(412, 10);
			this->btnOverview->Name = L"btnOverview";
			this->btnOverview->Size = System::Drawing::Size(75, 23);
			this->btnOverview->TabIndex = 0;
			this->btnOverview->Text = L"Overview";
			this->btnOverview->UseVisualStyleBackColor = true;
			this->btnOverview->Click += gcnew System::EventHandler(this, &MyForm::btnOverview_Click);
			// 
			// btnDo
			// 
			this->btnDo->Location = System::Drawing::Point(412, 40);
			this->btnDo->Name = L"btnDo";
			this->btnDo->Size = System::Drawing::Size(75, 23);
			this->btnDo->TabIndex = 1;
			this->btnDo->Text = L"Do";
			this->btnDo->UseVisualStyleBackColor = true;
			this->btnDo->Click += gcnew System::EventHandler(this, &MyForm::btnDo_Click);
			// 
			// btnAddNewPict
			// 
			this->btnAddNewPict->Location = System::Drawing::Point(412, 70);
			this->btnAddNewPict->Name = L"btnAddNewPict";
			this->btnAddNewPict->Size = System::Drawing::Size(75, 23);
			this->btnAddNewPict->TabIndex = 2;
			this->btnAddNewPict->Text = L"Add";
			this->btnAddNewPict->UseVisualStyleBackColor = true;
			this->btnAddNewPict->Click += gcnew System::EventHandler(this, &MyForm::btnAddNewPict_Click);
			// 
			// btnClear
			// 
			this->btnClear->Location = System::Drawing::Point(412, 100);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(75, 23);
			this->btnClear->TabIndex = 3;
			this->btnClear->Text = L"Clear";
			this->btnClear->UseVisualStyleBackColor = true;
			this->btnClear->Click += gcnew System::EventHandler(this, &MyForm::btnClear_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox1->Size = System::Drawing::Size(383, 238);
			this->textBox1->TabIndex = 4;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Multiselect = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(499, 262);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->btnClear);
			this->Controls->Add(this->btnAddNewPict);
			this->Controls->Add(this->btnDo);
			this->Controls->Add(this->btnOverview);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private:
	System::Void btnOverview_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void btnDo_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void btnAddNewPict_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void btnClear_Click(System::Object^  sender, System::EventArgs^  e);
};
}
