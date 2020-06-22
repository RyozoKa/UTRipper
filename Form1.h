#pragma once

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::WebBrowser^ webBrowser1;
	protected:
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: array<String^>^ Links;
	private: System::Threading::Thread^ T;
	private: System::Int32 Num, Index;
	private: System::Windows::Forms::Button^ button2;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// webBrowser1
			// 
			this->webBrowser1->Location = System::Drawing::Point(12, 12);
			this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
			this->webBrowser1->Name = L"webBrowser1";
			this->webBrowser1->Size = System::Drawing::Size(1368, 727);
			this->webBrowser1->TabIndex = 0;
			this->webBrowser1->Url = (gcnew System::Uri(L"http://ut-files.com/index.php\?dir=Maps/MonsterHunt/", System::UriKind::Absolute));
			this->webBrowser1->FileDownload += gcnew System::EventHandler(this, &Form1::WebBrowser1_FileDownload);
			this->webBrowser1->ProgressChanged += gcnew System::Windows::Forms::WebBrowserProgressChangedEventHandler(this, &Form1::WebBrowser1_ProgressChanged);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(12, 759);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(1223, 23);
			this->progressBar1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(1241, 759);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(54, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Go";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::Button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(21, 742);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"label1";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(1301, 759);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(55, 23);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Stop";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::Button2_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1392, 794);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->webBrowser1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


		//Helper functions

		private: String^ ExecuteJS(String^ S)
		{
			return (String^)webBrowser1->Document->InvokeScript("eval", gcnew array<Object^>{ S });
		}

		//Begin download
	private: System::Void WebBrowser1_FileDownload(System::Object^ sender, System::EventArgs^ e) {
	}

			 //Finish download
	private: System::Void WebBrowser1_ProgressChanged(System::Object^ sender, System::Windows::Forms::WebBrowserProgressChangedEventArgs^ e) {
	}

			 delegate void DelProgress();
	private: void Progress()
	{
		if (progressBar1->InvokeRequired)
		{
			DelProgress^ d = gcnew DelProgress(this, &Form1::Progress);
			Invoke(d);
		}
		else
		{
			progressBar1->Increment(1);
			label1->Text = (Index++) + " / " + Num;
		}
	}
			 //Start
	
	private: void AsyncDownloader()
	{
		int i;
		try
		{
			//Downloader
			System::Net::WebClient^ Cl = gcnew System::Net::WebClient();

			//Begin download
			for (int i = 0; i < Num; ++i)
			{
				Cl->DownloadFile(Links[i], "RippedMaps/" + (Links[i]->Substring(Links[i]->LastIndexOf("=") + 1)));
				Progress();
			}
		}
		catch (System::Exception^ E)
		{
			MessageBox::Show("Exception: " + E->Message + " File " + "RippedMaps/" + (Links[i]->Substring(Links[i]->LastIndexOf("=") + 1)));
		}
	}
private: System::Void Button1_Click(System::Object^ sender, System::EventArgs^ e) {

		//Find out how many entries we have
		Links = gcnew array<String^>(1500);

		Num = Convert::ToInt32(ExecuteJS(" function f() {var ent = document.getElementsByTagName('tbody')[0].getElementsByTagName('tr');\
								return ent.length.toString();} f();")) - 3;	
		Index = 0;
		for (int i = 0; i < Num; ++i)
			Links[i] = ExecuteJS(" function f() {var ent = document.getElementsByTagName('tbody')[0].getElementsByTagName('tr')[" + (i + 2) + "]; return ent.getElementsByTagName('a')[0].href; } f();");

		T = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &Form1::AsyncDownloader));

		System::IO::Directory::CreateDirectory("RippedMaps");
		progressBar1->Maximum = Num;
		label1->Text = "0 / " + Num;

		T->Start();
		//Start 5 downloads
		//for (int i = 0; i < 5; ++i)
		//	Cl->DownloadFile(Links[i], "Test" + i + ".rar");
	}
private: System::Void Button2_Click(System::Object^ sender, System::EventArgs^ e) {
	T->Abort();
}
};
}
