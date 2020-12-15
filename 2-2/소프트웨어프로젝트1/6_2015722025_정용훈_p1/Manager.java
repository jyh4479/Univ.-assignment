package p1;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.StringTokenizer;
import java.io.BufferedWriter;

import java.io.File; //The importing for checking existion of file


public class Manager { //Declare manger
   
   public CircularLinkedList cll=null;   // MEMORIZED Circular Linked List
   public AlphabetBST bst=null;         // MEMORIZING BST
   public Queue queue=null;            // TO_MEMORIZE Queue
   public String cmd=null;            // command 
   public BufferedWriter bw = null;
   public Manager() //constructor
   {

   }

   public void run(String command) throws IOException
   { //The function of run
      BufferedReader br = null; //Declare BufferedReader
      StringTokenizer st = null; //Declare String Tokenizer
      String line; //Declare String
      String cmd1;
      String cmd2;
      String cmd3;
      char[] word; //Declare char
      int num=0; //Declare integer
      int check=0; //Delcare integer

      br=new BufferedReader(new FileReader(command)); //Read command
      bw=new BufferedWriter(new FileWriter("log.txt",true)); //For Writing log file
      
      while((line = br.readLine())!= null) //repeat the function if line is not NULL
      {
         st=new StringTokenizer(line," "); //Split the String
         cmd1 = st.nextToken(); //Save next string to cmd1
         word = new char[cmd1.length()];
         for(int i=0, j=0; i<cmd1.length();i++)
         {
            if(cmd1.charAt(i)<='z')
            {
               word[j]=cmd1.charAt(i);
               j++;
            }

         }
         
         cmd2=new String(word); // Save word to cmd2
         if(cmd2.contains("LOAD")) //if cmd2 contains LOAD, run function
            check=1; //Save 1 to check
            
         if(cmd1.equals("ADD")) //if cmd1 is ADD
         { 
            if(st.hasMoreTokens()) //If there is more parameter
            { //Print error
               printErrorCode(200);
               continue; //continue
            }
            
            if(queue!=null || bst!=null || cll!=null) //if there are not three data structure
               printErrorCode(200); //Print Error
            else if(ADD()) //else if run ADD
               printSuccessCode("ADD"); //if return true Print SucceseeCode
            else //else
               printErrorCode(200); //Print Error
         }
         
         else if(check==1) //if check is 1 run function
         {
            check=0; //Save 0 to check
            
            if(line.equals("LOAD")) //check parameter
            {
               printErrorCode(100); //Error
               continue;
            }
            
            if(queue!=null || bst!=null || cll!=null) //if there are not three data structure
               printErrorCode(100); //print Error
            else if(LOAD()) //run LOAD
               printSuccessCode("  LOAD"); //Print Success
            else
               printErrorCode(100); //Print Error
         }   
         
         else if(cmd1.equals("MOVE")) //Run Move
         {   
            if(line.equals("MOVE")) //Check parameter
            {
               printErrorCode(300); //Print Error
               continue;
            }
               
            cmd2 = st.nextToken(); //Save next String to cmd2
            
            if(st.hasMoreTokens()) //Check parameter
            {
               printErrorCode(300); //Print Error
               continue;
            }

            num=Integer.parseInt(cmd2); //Save number of parameter
            if(MOVE(num)) //run Move function with parameter
               printSuccessCode("MOVE"); //Print Success
            else
               printErrorCode(300); //Print Error
         }
         
         else if(cmd1.equals("SEARCH")) //if cmd1 is equals SEARCH, run function
         {
            if(line.equals("SEARCH")) //Check parameter
            {
               printErrorCode(600); //Print error
               continue;
            }
            
            cmd2 = st.nextToken(); //Save next String to cmd2
            
            if(st.hasMoreTokens()) //check parameter
            {
               printErrorCode(600); //Print Error
               continue;
            }
            
            SEARCH(cmd2); //Run Search function      
         }
         
         else if(cmd1.equals("PRINT")) //if the command is PRINT, run function
         {
            if(line.equals("PRINT")) //check parameter
            {
               printErrorCode(700); //Print error
               continue;
            }
            
            cmd2 = st.nextToken(); //Save next string to cmd2
            
            if(st.hasMoreTokens()) //check parameter
            {
               printErrorCode(700); //Print Error
               continue;
            }
            
            PRINT(cmd2); //Run Print function
         }
         
         else if(cmd1.equals("SAVE")) //if the command is SAVE, run function
         {
            if(st.hasMoreTokens()) //check parameter
            {
               printErrorCode(400); //Print Error
               continue;
            }
            
            if(SAVE()) //Run Save function and check boolean
               printSuccessCode("SAVE"); //Success
            else
               printErrorCode(400); //Error
         }
         
         else if(cmd1.equals("TEST")) //if command is TEST, run function
         {
            if(line.equals("TEST")) //check parameter
            {
               printErrorCode(500); //Print Error
               continue;
            }
            
            cmd2 = st.nextToken(); //Save next string to cmd2
                     
            if(line.equals("TEST "+cmd2)) //check parameter
            {
               printErrorCode(500); //Print Error
               continue;
            }
            
            cmd3 = st.nextToken(); //Save next String to cmd3
            
            if(st.hasMoreTokens()) //check parameter
            {
               printErrorCode(500); //Print Error
               continue;
            }
            
            TEST(cmd2,cmd3,bw); //Run TEST function
            
         }
         
         else if(cmd1.equals("UPDATE")) //if command is UPDATE, run function
         {
            if(line.equals("UPDATE")) //check parameter
            {
               printErrorCode(800); //Print Error
               continue;
            }
            
            cmd2 = st.nextToken(); //Save next string to cmd2
            
            if(line.equals("UPDATE "+cmd2)) //check parameter
            {
               printErrorCode(800); //Print Error
               continue;
            }
   
            cmd3 = st.nextToken(); //Save next string to cmd3

            if(st.hasMoreTokens()) //check parameter
            {
               printErrorCode(800); //Print Error
               continue;
            }
            
            if(UPDATE(cmd2,cmd3)); //Run UPDATE function, and check boolean
            
            else
               printErrorCode(800); //Print Error
         }
         
         else if(cmd1.equals("EXIT")) //if command is EXIT, Run function
         {
            if(st.hasMoreTokens()) //Check parameter
            {
               printErrorCode(0); //Print Error
               continue;
            }
            
            EXIT(); //run EXIT function
            printSuccessCode("EXIT"); //Print Error
            br.close(); //close file
            bw.close(); //close file
            return; //return void
         }
      }

   }

   public boolean LOAD() throws IOException
   {
      File filequeue = new File("to_memorize_word.txt"); //The Declare for checking opened file
      File filebst = new File("memorizing_word.txt");
      File filecll = new File("memorized_word.txt");
      
      boolean isExists1=filequeue.exists(); //Check exists file
      boolean isExists2=filebst.exists();
      boolean isExists3=filecll.exists();
      
      if(!isExists1 || !isExists2 || !isExists3 ) //Without any data, return false
         return false;
         
      BufferedReader queueW=new BufferedReader(new FileReader("to_memorize_word.txt")); //Read file
      BufferedReader bstW=new BufferedReader(new FileReader("memorizing_word.txt"));
      BufferedReader cllW=new BufferedReader(new FileReader("memorized_word.txt"));
      StringTokenizer st=null;
      String line=null; //string
      String word=null;
      String mean=null;
      int count=0;
      
      while((line=queueW.readLine())!=null) //Read file until end file
      {
         st=new StringTokenizer(line); //Declare Tokenizer
         
         word = st.nextToken(); //Load word
         mean = st.nextToken(); //Load mean
         
         WordNode newNode = new WordNode(); //make new Node
         
         if(line.length()<2) //Check wrong data
         {
            cll=null;
            queue=null;
            bst=null;
            return false;
         }
         
         newNode.SetWord(word); //Set word
         newNode.SetMean(mean); //Set mean
         
         if(queue==null) //if queue is null
         {
            Queue newQ = new Queue(); //make queue
            queue = newQ;
            queue.Push(newNode); //push new data
         }
         
         else
            queue.Push(newNode); //push new data   
      }
      
      while((line=bstW.readLine())!=null)
      { //Read file until end file
         char alphabet; //Declare char
         st=new StringTokenizer(line); //Declare st from line
         
         if(line.length()<2) //Check wrong data
         {
            cll=null;
            queue=null;
            bst=null;
            return false;
         }
         
         word = st.nextToken(); //Load word
         mean = st.nextToken(); //Load mean
         
         WordNode newNode = new WordNode(); //make new Node
         
         newNode.SetWord(word); //Set word
         newNode.SetMean(mean); //Set mean
         alphabet=word.charAt(0); //Save first alphabet
         
         if(bst==null) //Check bst
         {
            AlphabetBST newABST = new AlphabetBST(); //make new BST
            bst=newABST;
         }
         if(bst.Search(alphabet).GetBST()==null) //Search alphabet Node's bst
         {
            WordBST newBST= new WordBST(); //make new bst node
            bst.Search(alphabet).SetBST(newBST);
         }
         bst.Search(alphabet).GetBST().Insert(newNode); //Insert new Node
         bst.setCnt(++count); //plus count         
      }
      
      while((line=cllW.readLine())!=null)
      { //Read file until end file
         if(line.length()<2) //check wrong data
         {
            cll=null;
            queue=null;
            bst=null;
            return false;
         }
         st=new StringTokenizer(line); //Declare st from line
      
         word = st.nextToken(); //Load word
         mean = st.nextToken(); //Load mean
         
         WordNode newNode = new WordNode(); //make new Node
         
         newNode.SetWord(word); //Set word
         newNode.SetMean(mean); //Set mean
         
         if(cll==null) //check existion of cll
         {
            CircularLinkedList newCll = new CircularLinkedList(); //make new cll
            cll = newCll;
            cll.Insert(newNode); //insert new Node
         }
         
         else
            cll.Insert(newNode); //insert new Node 
      }
      if(queue==null || bst.getCnt()==0 || cll==null) //check data of structure
         return false; //return false
      else
         return true; //return true
   }
   
      
   public boolean ADD() throws IOException
   { //Run ADD
      BufferedReader br = null; //For reading data
      StringTokenizer st = null; //For spliting string
      br = new BufferedReader(new FileReader("word.txt")); //Load data from txt file
      String line; //String
      String word;
      String mean;
          
      while((line=br.readLine())!=null)
      { //Read file until end file
         st=new StringTokenizer(line); //Declare st from line
         
         if(line.length()<2) //Check wrong data
            continue;
         
         word = st.nextToken(); //Load word
         mean = st.nextToken(); //Load mean
         
         WordNode newNode = new WordNode(); //make new Node
         
         newNode.SetWord(word); //set word
         newNode.SetMean(mean); //set mean
         
         if(queue==null) //if queue is null
         {
            Queue newQ = new Queue(); //make queue
            queue = newQ;
            queue.Push(newNode); //insert new Node
         }
         
         else
            queue.Push(newNode); //insert new Node   
      }   
      if(queue==null) //if queue is null
         return false; //return false
      else
         return true; //return true
   }
   
   public boolean MOVE(int num)
   { //The Move function
      if(queue==null||queue.pHead==null) //if queue or pHead is null
         return false; //return false
      
      char[] alphabet; //Char
      WordNode tmp = queue.pHead; //Save pHead to tmp
      WordNode prev = queue.pHead; //Save pHead to prev
   
      if(bst==null) //check existion of bst
      {
         AlphabetBST newABST = new AlphabetBST(); //make new bst
         bst=newABST;
      }
      
      if(bst.getCnt()>100) //Check number of data
         return false; //if over 100, return false
      
      int count=bst.getCnt(); //integer
      int check =0; //Save 0 to check
      while(num!=check&&tmp!=null)
      {//num is not check, and is not null
         if(bst.getCnt()==100) //if count is 100, run function
            return false; //return false
         
         
         
         alphabet=new char[tmp.GetWord().length()]; //change to char
         
         for(int k=0; k<tmp.GetWord().length();k++)
         {
             if(tmp.GetWord().charAt(k)<123)
             {
                alphabet[0]=(tmp.GetWord().charAt(k)); //Save first alphabet
                break;
             }
         }
        // alphabet[0]=(tmp.GetWord().charAt(0)); //Save first alphabet
            
         if(bst.Search(alphabet[0])==null) //if there is no data
            return false; //return false
         
         else
         {
            if(bst.Search(alphabet[0]).GetBST()==null) //Check bst is not null or null
            {
               WordBST newBST = new WordBST(); //make new bst
               bst.Search(alphabet[0]).SetBST(newBST);
            }
            bst.Search(alphabet[0]).GetBST().Insert(tmp); //insert correct data of node
            //queue.Pop(); //run Pop function
         }
         tmp=tmp.GetNext(); //Move node pinter to next
         queue.Pop(); //run Pop function
         bst.setCnt(++count); //The number of node that in bst
         check++; //check = check + 1

      }
      return true; //return true
   }

   public boolean SAVE() throws IOException
   { //The Save function
      if(cll==null||bst==null||bst.getCnt()==0||queue==null) //check data of structure
         return false; //return false
      
      else if(queue.pHead!=null&&bst.getCnt()>0&&cll.pHead!=null) //check data of structure
      {
         queue.Save(bw); //Save queue
         bst.Save(bw); //Save bst
         cll.Save(bw); //Save cll
         return true; //return true
      }
      
      else
         return false; //return false
   }
   
   public boolean TEST(String word,String meaning, BufferedWriter bw) throws IOException
   { //The function of TEST
      word=word.toLowerCase(); //For change alphabet to low case
      char alphabet = word.charAt(0); //Save front alphabet to char
      
      if(bst==null) //if bst is null
      {
         bw.write("======== ERROR ========"); bw.newLine(); //Print error
         System.out.println("======== ERROR ========");
         System.out.println("500");
         bw.write("500");
         bw.newLine(); 
         bw.write("======================="); bw.newLine(); bw.newLine();
         System.out.println("======================="); System.out.println("");
         return false; //return false
      }
      
      if(bst.getCnt()==0) //if number of node is zero
      {
         bw.write("======== ERROR ========"); bw.newLine(); //print error
         System.out.println("======== ERROR ========");
         System.out.println("500");
         bw.write("500");
         bw.newLine(); 
         bw.write("======================="); bw.newLine(); bw.newLine();
         System.out.println("======================="); System.out.println("");
         return false;
      }
      WordNode pNode=null; //Save null to pNode
      if(bst.Search(alphabet).GetBST()!=null)
         pNode=bst.Search(alphabet).GetBST().Search(word); //Search word
      
      if(pNode!=null) //if pNode is exist
      {
         
         if(pNode.GetMean().compareTo(meaning)==0) //if the mean is correct
         {
            System.out.println("======== TEST ========"); //Print
            bw.write("======== TEST ========");
            bw.newLine();
            
            if(cll==null) //if cll is null
               cll = new CircularLinkedList(); //make new cll
            WordNode newNode = new WordNode(); //make New Node
            newNode.SetWord(pNode.GetWord()); //set data
            newNode.SetMean(pNode.GetMean());
            cll.Insert(newNode); //insert
            bst.Search(alphabet).GetBST().Delete(word); //delete
            bst.setCnt(bst.getCnt()-1); //delete and count=count-1
            System.out.println("Pass"); //print data
            bw.write("Pass");
            bw.newLine();
            bw.write("======================="); bw.newLine(); bw.newLine();
            System.out.println("======================="); System.out.println("");
            return true; //return true
         }
         
         else
         {
            bw.write("======== ERROR ========"); bw.newLine(); //print Error
            System.out.println("======== ERROR ========");
            System.out.println("500");
            bw.write("500");
            bw.newLine(); 
            bw.write("======================="); bw.newLine(); bw.newLine();
            System.out.println("======================="); System.out.println("");
            return false; //return false
         }
      }
      else
      {
         bw.write("======== ERROR ========"); bw.newLine(); //print Error
         System.out.println("======== ERROR ========");
         System.out.println("500");
         bw.write("500");
         bw.newLine();
         bw.write("======================="); bw.newLine(); bw.newLine();
         System.out.println("======================="); System.out.println("");
         return false; //return false
      }

   }
   
   public boolean SEARCH(String word) throws IOException
   {
      word=word.toLowerCase(); //For change alphabet to low case
      char alphabet = word.charAt(0); //Save front alphabet to char
      
      if(queue==null) //if queue is null
      {
         printErrorCode(600); //print Error
         return false;
      }
      else if(queue.Search(word)!=null) //if the Node exist
      { //run
         System.out.println("======== SEARCH ========"); //print
         bw.write("======== SEARCH ========");
         bw.newLine();
         System.out.println(queue.Search(word).GetWord()+" "+queue.Search(word).GetMean());
         bw.write(queue.Search(word).GetWord()+" "+queue.Search(word).GetMean());
         bw.newLine();
         bw.write("======================="); bw.newLine(); bw.newLine();
         System.out.println("======================="); System.out.println("");
         return true; //return true
      }
      
      if(bst==null) //if bst is null
      {
         printErrorCode(600); //print Error code
         return false; //return false
      }
      else if(bst.Search(alphabet).GetBST().Search(word)!=null) //if the Node exist
      {
         System.out.println("======== SEARCH ========"); //print
         bw.write("======== SEARCH ========");
         bw.newLine();
         System.out.println(bst.Search(alphabet).GetBST().Search(word).GetWord()+" "+bst.Search(alphabet).GetBST().Search(word).GetMean());
         bw.write(bst.Search(alphabet).GetBST().Search(word).GetWord()+" "+bst.Search(alphabet).GetBST().Search(word).GetMean());
         bw.newLine();
         bw.write("======================="); bw.newLine(); bw.newLine();
         System.out.println("======================="); System.out.println("");
         return true; //return true
      }
      
      if(cll==null) //if cll is null
      {
         printErrorCode(600); //print error
         return false; //return false
      }
      else if(cll.Search(word).GetWord()!=null)
      { //if the Node exist
         System.out.println("======== SEARCH ========"); //print
         bw.write("======== SEARCH ========");
         bw.newLine();
         System.out.println(cll.Search(word).GetWord()+" "+cll.Search(word).GetMean());
         bw.write(cll.Search(word).GetWord()+" "+cll.Search(word).GetMean()); bw.newLine();
         bw.write("======================="); bw.newLine(); bw.newLine();
         System.out.println("======================="); System.out.println("");
         return true; //return true
      }
      
      else
      {
         printErrorCode(600); //print error
         return false; //return false
      }
      

   
   }
   public boolean PRINT(String cmd2) throws IOException
   { //The function of Print
      if(cmd2.equals("TO_MEMORIZE")) //check TO_MEMORIZE
      {
         if(queue==null) //if queue is null
            printErrorCode(700); //error
         else
         {
            System.out.println("======== PRINT ========"); //Print
            bw.write("======== PRINT ========"); bw.newLine();
            queue.Print(bw);
            bw.write("======================="); bw.newLine(); bw.newLine();
            System.out.println("======================="); System.out.println("");
         }
      }
      else if(cmd2.equals("MEMORIZING")) //check MEMORIZING
      {
         if(bst==null) //if bst is null
            printErrorCode(700); //error
         else if(bst.getCnt()==0) //if The number of node is zero
            printErrorCode(700); //error
         else
         {
            System.out.println("======== PRINT ========"); //print
            bw.write("======== PRINT ========"); bw.newLine();
            bst.Print(bw);
            bw.write("======================="); bw.newLine(); bw.newLine();
            System.out.println("======================="); System.out.println("");
         }
      }
      else if(cmd2.equals("MEMORIZED")) 
      {
         if(cll==null) //if cll is null
            printErrorCode(700); //error
         else
         {
            System.out.println("======== PRINT ========"); //print error
            bw.write("======== PRINT ========"); bw.newLine();
            cll.Print(bw);
            bw.write("======================="); bw.newLine(); bw.newLine();
            System.out.println("======================="); System.out.println("");
         }
      }
      return true; //return true
   }
   
   public boolean UPDATE(String cmd2, String newMeaning ) throws IOException
   { //The function of UPDATE
      cmd2=cmd2.toLowerCase(); //For change alphabet to low case
      
      char alphabet = cmd2.charAt(0); // The front alphabet
      WordNode pNode=null; //Save null to pNode
      if(queue==null) //if queue is null
         return false; //return false
      else if(queue.Search(cmd2)!=null) //search queue
         pNode=queue.Search(cmd2);
      else if(bst==null)
         return false;
      else if(bst.Search(alphabet).GetBST().Search(cmd2)!=null) //search bst
         pNode=bst.Search(alphabet).GetBST().Search(cmd2);
      else if (cll==null)
         return false;
      else if(cll.Search(cmd2)!=null) //search cll
         pNode=cll.Search(cmd2);
      
      if(pNode==null) //if pNode is null
      {
         return false; //return false
      }
      
      else
      {
         System.out.println("======== UPDATE ========"); //Print Update
         bw.write("======== UPDATE ========"); bw.newLine();
         System.out.println(pNode.GetWord() + " " + pNode.GetMean() + " -> " + newMeaning);
         bw.write(pNode.GetWord() + " " + pNode.GetMean() + " -> " + newMeaning);
         bw.newLine();
         bw.write("======================="); bw.newLine(); bw.newLine();
         System.out.println("======================="); System.out.println("");
         pNode.SetMean(newMeaning);
         return true;
      }
   }
   public boolean EXIT() { //The function of Exit
      cll=null;
      queue=null;
      bst=null;
      return true;
      
   }
   
   public void printErrorCode(int n) throws IOException
   { // The function for Printing Error code
   bw.write("======== ERROR ========"); bw.newLine();
   System.out.println("======== ERROR ========");
   if(n==100)
      bw.write("100");
   else if(n==200)
      bw.write("200");
   else if(n==300)
      bw.write("300");
   else if(n==400)
      bw.write("400");
   else if(n==500)
      bw.write("500");
   else if(n==600)
      bw.write("600");
   else if(n==700)
      bw.write("700");
   else if(n==800)
      bw.write("800");

   bw.newLine();
   System.out.println(n);
   bw.write("======================="); bw.newLine(); bw.newLine();
   System.out.println("======================="); System.out.println("");
   
   }
   public void printSuccessCode(String cmdname) throws IOException{ //The function for Printing Error code
   bw.write("======== "+cmdname+" ========"); bw.newLine();
   System.out.println("======== "+cmdname+" ========");
   bw.write("Success"); bw.newLine();
   System.out.println("Success");
   bw.write("======================="); bw.newLine(); bw.newLine();
   System.out.println("======================="); System.out.println("");
   }
}
