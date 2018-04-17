#include "MyForm.h"
#include "cluster.h"
#include <msclr\marshal_cppstd.h>
using namespace kursProject;
using namespace System::IO;
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
			textBox1->Text += "\r\n" + Path::GetFileName(file);
			dataGridView1->Rows->Add(Path::GetFileName(file), gcnew Bitmap(file));
						
			Bitmap^ bbb = my.toGrayScale(gcnew Bitmap(file));
			//dataGridView1->Rows->Add(Path::GetFileName(file), bbb);
			
			P vectP = my.vectorization(bbb);
			msclr::interop::marshal_context context;
			vectP.pathToFile = context.marshal_as<std::string>(file);

			my.koord.push_back(vectP);
			nnp++;

			for(unsigned int i = 0; i < 100; i++)
			{
				textBox1->Text += "\t" + vectP.x[i];
			}
		}
		my.n = 100; //dimension
		my.np = nnp; //number of point
	}
}

System::Void kursProject::MyForm::btnDo_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!my.koord.empty() && my.koord.size() > 1 && Convert::ToInt32(textBox2->Text) > 1)
	{
		my.k = Convert::ToInt32(textBox2->Text);
		my.choosecenters();
		textBox1->Text += "\r\n CentersNumb="+ my.k + "\r\n";
		for (unsigned int j = 0; j < my.k; j++)
		{
			textBox1->Text += "numb" + (j+1) +"p";
			for (unsigned int i = 0; i < 100; i++)
			{
				textBox1->Text +="\t"+ my.centry[j].x[i];
			}
			textBox1->Text += "\r\n";
		}

		my.previouscentry.clear();
		for (unsigned int g = 0; g < my.k; g++)
		{
			my.previouscentry.push_back(my.centry[g]);//dlja kmeans
		}
		my.end = 0;
		my.bindpoints();// -->kmeans
		
		textBox1->Text += "\r\n" + "---------------------------------------------";
		for (unsigned int g = 0; g < my.kser.size(); g++)
		{
			textBox1->Text += "\r\n"+(g + 1) + " cluster " + my.kser[g].size() + " points\r\n";
			for (unsigned int j = 0; j < my.kser[g].size(); j++)
			{
				String^ str3 = gcnew String(my.kser[g][j].pathToFile.c_str());
				textBox1->Text += "  " + (g + 1) + "_" + (j + 1) + Path::GetFileName(gcnew String(str3)) +" p( ";
				for (unsigned int i = 0; i < my.kser[g][j].x.size(); i++)
				{
					if (i == my.n - 1) textBox1->Text += my.kser[g][j].x[i];
					else textBox1->Text += my.kser[g][j].x[i] + ", ";
				}
				if (j == 0) textBox1->Text += " center";
				textBox1->Text += " )\r\n";
			}
		}
	}
}

System::Void kursProject::MyForm::btnAddNewPict_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!my.koord.empty() && !my.kser.empty())
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
		
			textBox1->Text += "\r\n" + "---------------------------------------------";
			unsigned int nnp = 0;
			for each(String^ file in openFileDialog1->FileNames)
			{

				textBox1->Text += "\r\n" + Path::GetFileName(file);
				dataGridView1->Rows->Add(Path::GetFileName(file), gcnew Bitmap(file));

				Bitmap^ bbb = my.toGrayScale(gcnew Bitmap(file));
				//dataGridView1->Rows->Add(Path::GetFileName(file), bbb);

				my.pointkNN = my.vectorization(bbb);
				msclr::interop::marshal_context context;
				my.pointkNN.pathToFile = context.marshal_as<std::string>(file);

				my.koord.push_back(my.pointkNN);
				nnp++;

				for (unsigned int i = 0; i < 100; i++)
				{
					textBox1->Text += "\t" + my.pointkNN.x[i];
				}

				///////////////////////////////////////////////////////
				my.kNearest();

				textBox1->Text += ")\r\n Point dropped into " + (my.ki + 1) + " cluster";
				my.pointkNN.x.clear();
			}
			my.np += nnp;
		}
	}
}

System::Void kursProject::MyForm::btnClear_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	my.koord.clear();
	my.centry.clear();
	my.previouscentry.clear();
	my.kser.clear();
	my.end = 0;
	my.vidstani.clear();
	my.pointkNN.x.clear();
	my.pointkNN.pathToFile.clear();
	my.np = 0;
	textBox1->Text = "";
	textBox2->Text = "2";
	dataGridView1->Rows->Clear();
	dataGridView1->Refresh();
}