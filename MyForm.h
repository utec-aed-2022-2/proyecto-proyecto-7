#pragma once

namespace frontendblockchain {

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
	private: System::Windows::Forms::Label^ Inputlabel;
	private: System::Windows::Forms::TextBox^ Inputtextbox;
	private: System::Windows::Forms::TextBox^ noncetextbox;
	private: System::Windows::Forms::Label^ noncelabel;
	private: System::Windows::Forms::Button^ inputbutton;
	private: System::Windows::Forms::Label^ BC_1;
	protected:

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
			this->Inputlabel = (gcnew System::Windows::Forms::Label());
			this->Inputtextbox = (gcnew System::Windows::Forms::TextBox());
			this->noncetextbox = (gcnew System::Windows::Forms::TextBox());
			this->noncelabel = (gcnew System::Windows::Forms::Label());
			this->inputbutton = (gcnew System::Windows::Forms::Button());
			this->BC_1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// Inputlabel
			// 
			this->Inputlabel->AutoSize = true;
			this->Inputlabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->Inputlabel->Location = System::Drawing::Point(13, 13);
			this->Inputlabel->Name = L"Inputlabel";
			this->Inputlabel->Size = System::Drawing::Size(39, 17);
			this->Inputlabel->TabIndex = 0;
			this->Inputlabel->Text = L"Input";
			// 
			// Inputtextbox
			// 
			this->Inputtextbox->Location = System::Drawing::Point(58, 13);
			this->Inputtextbox->Name = L"Inputtextbox";
			this->Inputtextbox->Size = System::Drawing::Size(405, 20);
			this->Inputtextbox->TabIndex = 1;
			// 
			// noncetextbox
			// 
			this->noncetextbox->Location = System::Drawing::Point(58, 50);
			this->noncetextbox->Name = L"noncetextbox";
			this->noncetextbox->Size = System::Drawing::Size(405, 20);
			this->noncetextbox->TabIndex = 3;
			// 
			// noncelabel
			// 
			this->noncelabel->AutoSize = true;
			this->noncelabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->noncelabel->Location = System::Drawing::Point(10, 50);
			this->noncelabel->Name = L"noncelabel";
			this->noncelabel->Size = System::Drawing::Size(47, 17);
			this->noncelabel->TabIndex = 2;
			this->noncelabel->Text = L"nonce";
			// 
			// inputbutton
			// 
			this->inputbutton->Location = System::Drawing::Point(160, 341);
			this->inputbutton->Name = L"inputbutton";
			this->inputbutton->Size = System::Drawing::Size(171, 50);
			this->inputbutton->TabIndex = 4;
			this->inputbutton->Text = L"insert";
			this->inputbutton->UseVisualStyleBackColor = true;
			this->inputbutton->Click += gcnew System::EventHandler(this, &MyForm::inputbutton_Click);
			// 
			// BC_1
			// 
			this->BC_1->AutoSize = true;
			this->BC_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->BC_1->Location = System::Drawing::Point(35, 146);
			this->BC_1->Name = L"BC_1";
			this->BC_1->Size = System::Drawing::Size(40, 20);
			this->BC_1->TabIndex = 5;
			this->BC_1->Text = L"BC1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(475, 425);
			this->Controls->Add(this->BC_1);
			this->Controls->Add(this->inputbutton);
			this->Controls->Add(this->noncetextbox);
			this->Controls->Add(this->noncelabel);
			this->Controls->Add(this->Inputtextbox);
			this->Controls->Add(this->Inputlabel);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void inputbutton_Click(System::Object^ sender, System::EventArgs^ e)  //excecuted when ok button is pressed
	{
		String^ inputtext = this->Inputtextbox->Text;
		this->BC_1->Text = "Blockchain1" + inputtext;
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) 
	{
		this->Inputtextbox->Text = "";
	}
};
}
