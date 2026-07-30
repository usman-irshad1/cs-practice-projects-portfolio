#pragma once
//#include "Header.h"
using namespace System::Media; // For SoundPlayer
using namespace System::IO;    // For Path handling
#include <msclr\marshal_cppstd.h>

namespace PROJECTGUI {

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
	private:
		SoundPlayer^ player = gcnew SoundPlayer();
	private: System::Windows::Forms::ComboBox^ comboPlaylist;
	private: System::Windows::Forms::Button^ btnLoad;
	private: System::Windows::Forms::Button^ btnClear;
	private: System::Windows::Forms::Button^ btnPlay;
	private: System::Windows::Forms::Button^ btnPause;
	private: System::Windows::Forms::Button^ btnStop;
	private: System::Windows::Forms::Button^ btnNext;
	private: System::Windows::Forms::Button^ btnPrev;

	private: System::Windows::Forms::Label^ lblDuration;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::RadioButton^ radioShuffle;

	private: System::Windows::Forms::RadioButton^ radioRepeat;


	private: System::Windows::Forms::RadioButton^ radioNormal;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Label^ lblStatus;



		   // A list to keep track of the full file paths
		   Collections::Generic::List<String^>^ playlistPaths = gcnew Collections::Generic::List<String^>();
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



	private: System::Windows::Forms::Label^ label1;
	private: System::ComponentModel::IContainer^ components;

	protected:




	protected:
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboPlaylist = (gcnew System::Windows::Forms::ComboBox());
			this->btnLoad = (gcnew System::Windows::Forms::Button());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			this->btnPlay = (gcnew System::Windows::Forms::Button());
			this->btnPause = (gcnew System::Windows::Forms::Button());
			this->btnStop = (gcnew System::Windows::Forms::Button());
			this->btnNext = (gcnew System::Windows::Forms::Button());
			this->btnPrev = (gcnew System::Windows::Forms::Button());
			this->lblDuration = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->radioShuffle = (gcnew System::Windows::Forms::RadioButton());
			this->radioRepeat = (gcnew System::Windows::Forms::RadioButton());
			this->radioNormal = (gcnew System::Windows::Forms::RadioButton());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold));
			this->label1->Location = System::Drawing::Point(46, 25);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(110, 17);
			this->label1->TabIndex = 3;
			this->label1->Text = L"IPOD PLAYER";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// comboPlaylist
			// 
			this->comboPlaylist->FormattingEnabled = true;
			this->comboPlaylist->Location = System::Drawing::Point(49, 122);
			this->comboPlaylist->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboPlaylist->Name = L"comboPlaylist";
			this->comboPlaylist->Size = System::Drawing::Size(160, 24);
			this->comboPlaylist->TabIndex = 4;
			// 
			// btnLoad
			// 
			this->btnLoad->Location = System::Drawing::Point(49, 249);
			this->btnLoad->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnLoad->Name = L"btnLoad";
			this->btnLoad->Size = System::Drawing::Size(100, 28);
			this->btnLoad->TabIndex = 5;
			this->btnLoad->Text = L"Add Tracks";
			this->btnLoad->UseVisualStyleBackColor = true;
			this->btnLoad->Click += gcnew System::EventHandler(this, &MyForm::btnLoad_Click);
			// 
			// btnClear
			// 
			this->btnClear->Location = System::Drawing::Point(557, 249);
			this->btnClear->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(100, 28);
			this->btnClear->TabIndex = 6;
			this->btnClear->Text = L"ClearAll";
			this->btnClear->UseVisualStyleBackColor = true;
			this->btnClear->Click += gcnew System::EventHandler(this, &MyForm::btnClear_Click);
			// 
			// btnPlay
			// 
			this->btnPlay->Location = System::Drawing::Point(168, 345);
			this->btnPlay->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnPlay->Name = L"btnPlay";
			this->btnPlay->Size = System::Drawing::Size(100, 28);
			this->btnPlay->TabIndex = 7;
			this->btnPlay->Text = L"PLAY";
			this->btnPlay->UseVisualStyleBackColor = true;
			this->btnPlay->Click += gcnew System::EventHandler(this, &MyForm::btnPlay_Click);
			// 
			// btnPause
			// 
			this->btnPause->Location = System::Drawing::Point(431, 345);
			this->btnPause->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnPause->Name = L"btnPause";
			this->btnPause->Size = System::Drawing::Size(100, 28);
			this->btnPause->TabIndex = 8;
			this->btnPause->Text = L"Pause";
			this->btnPause->UseVisualStyleBackColor = true;
			this->btnPause->Click += gcnew System::EventHandler(this, &MyForm::btnPause_Click);
			// 
			// btnStop
			// 
			this->btnStop->Location = System::Drawing::Point(312, 345);
			this->btnStop->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnStop->Name = L"btnStop";
			this->btnStop->Size = System::Drawing::Size(100, 28);
			this->btnStop->TabIndex = 9;
			this->btnStop->Text = L"STOP";
			this->btnStop->UseVisualStyleBackColor = true;
			this->btnStop->Click += gcnew System::EventHandler(this, &MyForm::btnStop_Click);
			// 
			// btnNext
			// 
			this->btnNext->Location = System::Drawing::Point(557, 345);
			this->btnNext->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnNext->Name = L"btnNext";
			this->btnNext->Size = System::Drawing::Size(100, 28);
			this->btnNext->TabIndex = 10;
			this->btnNext->Text = L">>Next";
			this->btnNext->UseVisualStyleBackColor = true;
			this->btnNext->Click += gcnew System::EventHandler(this, &MyForm::btnNext_Click);
			// 
			// btnPrev
			// 
			this->btnPrev->Location = System::Drawing::Point(37, 345);
			this->btnPrev->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnPrev->Name = L"btnPrev";
			this->btnPrev->Size = System::Drawing::Size(100, 28);
			this->btnPrev->TabIndex = 11;
			this->btnPrev->Text = L"<<Prev";
			this->btnPrev->UseVisualStyleBackColor = true;
			this->btnPrev->Click += gcnew System::EventHandler(this, &MyForm::btnPrev_Click);
			// 
			// lblDuration
			// 
			this->lblDuration->AutoSize = true;
			this->lblDuration->Location = System::Drawing::Point(111, 89);
			this->lblDuration->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblDuration->Name = L"lblDuration";
			this->lblDuration->Size = System::Drawing::Size(0, 16);
			this->lblDuration->TabIndex = 13;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(480, 122);
			this->progressBar1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(159, 24);
			this->progressBar1->TabIndex = 14;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->radioShuffle);
			this->groupBox1->Controls->Add(this->radioRepeat);
			this->groupBox1->Controls->Add(this->radioNormal);
			this->groupBox1->Location = System::Drawing::Point(229, 188);
			this->groupBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox1->Size = System::Drawing::Size(267, 123);
			this->groupBox1->TabIndex = 15;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Mode";
			// 
			// radioShuffle
			// 
			this->radioShuffle->AutoSize = true;
			this->radioShuffle->Location = System::Drawing::Point(63, 95);
			this->radioShuffle->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->radioShuffle->Name = L"radioShuffle";
			this->radioShuffle->Size = System::Drawing::Size(60, 20);
			this->radioShuffle->TabIndex = 2;
			this->radioShuffle->Text = L"Mixer";
			this->radioShuffle->UseVisualStyleBackColor = true;
			// 
			// radioRepeat
			// 
			this->radioRepeat->AutoSize = true;
			this->radioRepeat->Location = System::Drawing::Point(63, 65);
			this->radioRepeat->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->radioRepeat->Name = L"radioRepeat";
			this->radioRepeat->Size = System::Drawing::Size(59, 20);
			this->radioRepeat->TabIndex = 1;
			this->radioRepeat->Text = L"Loop";
			this->radioRepeat->UseVisualStyleBackColor = true;
			// 
			// radioNormal
			// 
			this->radioNormal->AutoSize = true;
			this->radioNormal->Checked = true;
			this->radioNormal->Location = System::Drawing::Point(63, 37);
			this->radioNormal->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->radioNormal->Name = L"radioNormal";
			this->radioNormal->Size = System::Drawing::Size(72, 20);
			this->radioNormal->TabIndex = 0;
			this->radioNormal->TabStop = true;
			this->radioNormal->Text = L"Normal";
			this->radioNormal->UseVisualStyleBackColor = true;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"WAV Files|*.wav";
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// lblStatus
			// 
			this->lblStatus->AutoSize = true;
			this->lblStatus->Location = System::Drawing::Point(62, 188);
			this->lblStatus->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(0, 16);
			this->lblStatus->TabIndex = 12;
			this->lblStatus->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->ClientSize = System::Drawing::Size(708, 428);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->lblDuration);
			this->Controls->Add(this->lblStatus);
			this->Controls->Add(this->btnPrev);
			this->Controls->Add(this->btnNext);
			this->Controls->Add(this->btnStop);
			this->Controls->Add(this->btnPause);
			this->Controls->Add(this->btnPlay);
			this->Controls->Add(this->btnClear);
			this->Controls->Add(this->btnLoad);
			this->Controls->Add(this->comboPlaylist);
			this->Controls->Add(this->label1);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion




	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btnLoad_Click(System::Object^ sender, System::EventArgs^ e) {
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			for each (String ^ file in openFileDialog1->FileNames) {
				// Add full path to our hidden list
				playlistPaths->Add(file);
				// Add just the name to the visible dropdown
				comboPlaylist->Items->Add(System::IO::Path::GetFileName(file));
			}
			lblStatus->Text = "Status: Tracks Loaded";
		}

	}
	private: System::Void btnPlay_Click(System::Object^ sender, System::EventArgs^ e) {
		if (comboPlaylist->SelectedIndex != -1) {
			// Retrieve the full path from our hidden list
			String^ filePath = playlistPaths[comboPlaylist->SelectedIndex];

			player->SoundLocation = filePath;
			player->Play(); // Starts asynchronous playback

			lblStatus->Text = "Status: Playing";
			label1->Text = "Playing: " + comboPlaylist->SelectedItem->ToString();

			// Start the timer to update progress bar
			progressBar1->Value = 0;
			timer1->Start();
		}
		else {
			MessageBox::Show("Please select a track first!");
		}
	}
	private: System::Void btnStop_Click(System::Object^ sender, System::EventArgs^ e) {
		player->Stop();
		timer1->Stop();
		lblStatus->Text = "Status: Stopped";
	}
	private: System::Void btnNext_Click(System::Object^ sender, System::EventArgs^ e) {
		if (comboPlaylist->Items->Count > 0) {
			// Increment index, wrap back to 0 if at the end
			int nextIndex = (comboPlaylist->SelectedIndex + 1) % comboPlaylist->Items->Count;
			comboPlaylist->SelectedIndex = nextIndex;

			// Trigger the Play button logic
			btnPlay_Click(sender, e);
		}
	}
	private: System::Void btnPrev_Click(System::Object^ sender, System::EventArgs^ e) {
		if (comboPlaylist->Items->Count > 0) {
			int prevIndex = comboPlaylist->SelectedIndex - 1;
			if (prevIndex < 0) prevIndex = comboPlaylist->Items->Count - 1;

			comboPlaylist->SelectedIndex = prevIndex;
			btnPlay_Click(sender, e);
		}
	}
	private: System::Void btnClear_Click(System::Object^ sender, System::EventArgs^ e) {
		player->Stop();
		playlistPaths->Clear();
		comboPlaylist->Items->Clear();
		lblStatus->Text = "Status: Playlist Cleared";
		label1->Text = "WELCOME TO AUDIO PLAYER";
		progressBar1->Value = 0;
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		// Simulate progress incrementing
		if (progressBar1->Value < progressBar1->Maximum) {
			progressBar1->Value += 2; // Adjust speed as needed
		}
		else {
			// When progress reaches 100%, check the RadioButtons (Mode)
			timer1->Stop();

			if (radioRepeat->Checked) {
				btnPlay_Click(sender, e); // Restart same song
			}
			else if (radioShuffle->Checked) {
				Random^ r = gcnew Random();
				comboPlaylist->SelectedIndex = r->Next(0, comboPlaylist->Items->Count);
				btnPlay_Click(sender, e);
			}
			else {
				btnNext_Click(sender, e); // Play next song
			}
		}
	}
	private: System::Void btnPause_Click(System::Object^ sender, System::EventArgs^ e) {
		player->Stop();      // Stop the sound
		timer1->Stop();      // Freeze the progress bar
		lblStatus->Text = "Status: Paused";
	}
	private: System::Void comboPlaylist_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		// If the user clicks a different song while one is already playing
		if (lblStatus->Text == "Status: Playing") {
			btnPlay_Click(sender, e);
		}
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
