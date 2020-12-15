
package p1;
import java.io.BufferedWriter; // import declaration
import java.io.FileWriter; // import declaration
import java.io.IOException; // import declaration

import p1.Pair; // class declaration
import p1.WordNode; // class declaration

public class main { // main class

	public static void main(String[] args) throws IOException { // main function
							
		Manager manager = new Manager(); // manager dynamic allocation
		manager.run("command.txt");	// run function read command.txt
		return; // return
	}

}