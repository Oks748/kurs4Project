#include "MyForm.h"
#include "cluster.h"
#include <msclr\marshal_cppstd.h>
using namespace kursProject;
cluster my;

[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	MyForm form;
	Application::Run(%form);
	my = cluster();
}

System::Void kursProject::MyForm::btnOverview_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		unsigned int nnp = 0;
		for each(String^ file in openFileDialog1->FileNames)
		{
			textBox1->Text = textBox1->Text + "\r\n" + file;
			Bitmap^ bitPict = gcnew Bitmap(file);

			Bitmap^ bbb = my.toGrayScale(bitPict);
			//textBox1->Text = textBox1->Text + "\r\n" + bbb->Height+"_"+bbb->Width;

			P vectP = my.vectorization(bbb);

			msclr::interop::marshal_context context;
			vectP.pathToFile = context.marshal_as<std::string>(file);

			my.koord.push_back(vectP);
			nnp++;


			textBox1->Text = textBox1->Text + "\r\n";
			for(unsigned int i = 0; i < 100; i++)
			{
				textBox1->Text = textBox1->Text + "_" + vectP.x[i];
			}
		}
		my.n = 100; //dimension

		my.k = 2; //amount of clusters
		my.np = nnp; //number of point
	}
}

System::Void kursProject::MyForm::btnDo_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (my.koord.empty())
	{
		//ShowMessage("!!!");
	}
	else
	{
		my.choosecenters();
		for (unsigned int g = 0; g < my.k; g++)
		{
			my.previouscentry.push_back(my.centry[g]);//dlja kmeans
		}
		my.end = 0;
		my.bindpoints();// -->kmeans
	}
}

System::Void kursProject::MyForm::btnAddNewPict_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		for each(String^ file in openFileDialog1->FileNames)
		{
			textBox1->Text = textBox1->Text + "\r\n" + file;
			Bitmap^ bitPict = gcnew Bitmap(file);

			Bitmap^ bbb = my.toGrayScale(bitPict);
			//textBox1->Text = textBox1->Text + "\r\n" + bbb->Height+"_"+bbb->Width;

			P vectP = my.vectorization(bbb);
			
			msclr::interop::marshal_context context;
			vectP.pathToFile = context.marshal_as<std::string>(file);
			
			my.koord.push_back(vectP);
			my.np++;

			textBox1->Text = textBox1->Text + "\r\n";
			for (unsigned int i = 0; i < 100; i++)
			{
				textBox1->Text = textBox1->Text + "_" + vectP.x[i];
			}
			
			///////////////////////////////////////////////////////
			my.kNearest();

		}
	}
		
}

System::Void kursProject::MyForm::btnClear_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//kanva->Canvas->Brush->Color = clWhite;
	my.koord.clear();
	my.centry.clear();
	my.previouscentry.clear();
	my.kser.clear();
	my.end = 0;
	my.pointkNN.x.clear();
	my.vidstani.clear();
	my.fg = false;
}