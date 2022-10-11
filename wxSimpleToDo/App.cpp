#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/textFile.h>

class MainFrame : public wxFrame {
public:

	wxTextCtrl* textBox;
	wxListBox* listBox;
	bool editing;
	int selectedIndex;

	MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
	{
		wxFont font(this->GetFont());
		font.SetPointSize(12);
		this->SetFont(font);
		wxPanel* panel = new wxPanel(this, wxID_ANY);
		textBox = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(15, 17), wxSize(430, 29), wxTE_PROCESS_ENTER);
		wxButton* btnAdd = new wxButton(panel, wxID_ANY, "Add", wxPoint(454, 17), wxSize(96, 32));
		listBox = new wxListBox(panel, wxID_ANY, wxPoint(15, 57), wxSize(534, 613), {});
		wxButton* btnEdit = new wxButton(panel, wxID_ANY, "Edit", wxPoint(236, 680), wxSize(96, 32));
		wxButton* btnRemove = new wxButton(panel, wxID_ANY, "Remove", wxPoint(340, 680), wxSize(96, 32));
		wxButton* btnRemoveAll = new wxButton(panel, wxID_ANY, "Remove All", wxPoint(444, 680), wxSize(108, 32));

		btnAdd->Bind(wxEVT_BUTTON, &MainFrame::OnAdd, this);
		btnRemove->Bind(wxEVT_BUTTON, &MainFrame::OnRemove, this);
		btnEdit->Bind(wxEVT_BUTTON, &MainFrame::OnEdit, this);
		this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
		textBox->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnTextEnter, this);
		listBox->Bind(wxEVT_LISTBOX_DCLICK, &MainFrame::OnListBoxItemDClicked, this);
		btnRemoveAll->Bind(wxEVT_BUTTON, &MainFrame::OnRemoveAll, this);

		whereToStore();
		this->listBox->Delete(this->listBox->GetCount() - 1);

	}

	void OnListBoxItemDClicked(wxCommandEvent& evt) {
		EditItem();
	}

	void OnClose(wxCloseEvent& evt) {
		wxStandardPaths path = wxStandardPaths::Get();

		wxTextFile      tFile;
		if (!wxFile::Exists(path.GetAppDocumentsDir() + "\\notes.txt")) {

			tFile.Create(path.GetAppDocumentsDir() + "\\notes.txt");
		}
		tFile.Open(path.GetAppDocumentsDir() + "\\notes.txt");

		tFile.Clear();

		for (int i = 0; i < listBox->GetCount(); i++)
		{
			tFile.AddLine(listBox->GetString(i));
		}

		tFile.Write();
		tFile.Close();
		evt.Skip();
	}


	void whereToStore() {
		wxStandardPaths path = wxStandardPaths::Get();

		wxTextFile      tFile;
		if (!wxFile::Exists(path.GetAppDocumentsDir() + "\\notes.txt")) {

			tFile.Create(path.GetAppDocumentsDir() + "\\notes.txt");
		}
		tFile.Open(path.GetAppDocumentsDir() + "\\notes.txt");

		this->listBox->AppendString(tFile.GetFirstLine());

		while (!tFile.Eof())
		{
			this->listBox->AppendString(tFile.GetNextLine());
		}

	}

	void OnTextEnter(wxCommandEvent& evt) {
		OnAdd(evt);
	}


	void OnRemove(wxCommandEvent& evt) {

		if (!this->listBox->GetCount()) return;
		if (this->listBox->GetSelection() == wxNOT_FOUND) return;
		selectedIndex = this->listBox->GetSelection();
		this->listBox->Delete(selectedIndex);
		if (selectedIndex == this->listBox->GetCount()) { this->listBox->Select(this->listBox->GetCount() - 1); return; }
		this->listBox->Select(selectedIndex);
	}

	void OnRemoveAll(wxCommandEvent& evt) {
		if (!this->listBox->GetCount()) return;
		this->listBox->Clear();
	}

	void OnEdit(wxCommandEvent& evt) {
		EditItem();
	}

	void EditItem()
	{
		selectedIndex = this->listBox->GetSelection();
		this->textBox->SetValue(this->listBox->GetString(selectedIndex));

		editing = true;
		this->textBox->SetFocus();
		this->textBox->SelectAll();
	}

	void OnAdd(wxCommandEvent& evt)
	{
		if ((this->textBox->GetValue()).IsNull()) return;

		if (!editing) {
			this->listBox->AppendString(this->textBox->GetValue());

		}
		else
		{

			this->listBox->SetString(selectedIndex, this->textBox->GetValue());
			editing = false;
		}

		this->textBox->Clear();
		this->listBox->DeselectAll();
	}
};


class App : public wxApp
{
public:
	bool OnInit() {
		MainFrame* mainFrame = new MainFrame("Simple To-Do");
		mainFrame->Show();
		mainFrame->SetClientSize(565, 720);
		mainFrame->Center();
		return true;
	}
};

wxIMPLEMENT_APP(App);