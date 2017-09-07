package cs235.xml;

import java.io.FileOutputStream;

public class TestCase {
	public static void main (String[] args) throws Exception {
		createStudentFile();
	}
	public static void createStudentFile() throws Exception {

		Document doc = ParserFactory.createDocument();
		Element student = ParserFactory.createElement("student");
		student.setAttribute("id", "123456789");
		student.setAttribute("gpa", "3.56");
		student.setAttribute("phone", "(801)375-1234");
		doc.appendChild(student);
		//student.appendChild(ParserFactory.createText("\n "));
		Element name = ParserFactory.createElement("name");
		Element lang = ParserFactory.createElement("English");
		lang.appendChild(ParserFactory.createText("Bill White"));
		Element lang2 = ParserFactory.createElement("Thai");
		lang2.appendChild(ParserFactory.createText("Bin Wai"));
		Element lang3 = ParserFactory.createElement("Esp");
		lang3.setAttribute("name", "Bil");
		Element lang4 = ParserFactory.createElement("Alien");
		lang4.appendChild(ParserFactory.createText("SHUGO"));
		name.appendChild(lang);
		//name.appendChild(lang2);
	//	name.appendChild(lang3);
		name.insertChildBefore(lang4, lang);
		student.appendChild(name);
		//student.appendChild(ParserFactory.createText("\n "));
		Element address = ParserFactory.createElement("address");
		address.appendChild(ParserFactory
				.createText("300 West 721 North Provo, UT 84604"));
		student.appendChild(address);
		//student.appendChild(ParserFactory.createText("\n "));
		Element major = ParserFactory.createElement("major");
		major.appendChild(ParserFactory.createText("Computer Science"));
		student.appendChild(major);
		//student.appendChild(ParserFactory.createText("\n"));
		FileOutputStream output = new FileOutputStream("student-file.xml");
		doc.write(output);
		output.close();

	}
}
