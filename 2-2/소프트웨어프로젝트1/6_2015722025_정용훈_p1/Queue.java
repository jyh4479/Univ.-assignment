package p1;
import java.io.BufferedWriter; // import declaration
import java.io.FileWriter; // import declaration
import java.io.IOException; // import declaration

import p1.WordNode; // WordNode class declaration

public class Queue { // Queue class

   public WordNode pHead;
   public BufferedWriter queueSave;
   private int count=1;
   Queue() // constructor
   {
   
   }
   
   

   public void Push(WordNode node)   // Pushing Node function to execute LOAD, ADD
   {
      if(pHead==null) // head is null
         pHead=node;
      else // head is not null
      {
         WordNode tmp=pHead;
         
         for(;tmp.GetNext()!=null;tmp=tmp.GetNext()) // looping when tmp will be last node
         {
            if(tmp.GetWord().equals(node.GetWord())) // a duplicate word
               return;
         }
         tmp.SetNext(node); // node set
      }
      return;
   }
   
   public WordNode   Pop()// popping node function to execution MOVE
   {
      WordNode pNode=pHead;
      pHead=pNode.GetNext(); // head change
      pNode.SetNext(null);
      return null;
   }
      
   public WordNode Search(String word) // Search node function to execution SEARCH, UPDATE
   {
      WordNode pNode=pHead;
      
      while(pNode!=null && !pNode.GetWord().equals(word)) // loop for finding word
      {
         pNode=pNode.GetNext();
      }
      if(pNode!=null) // find pNode
         return pNode;
      else // can't find pNode
         return null;
   }
   
   public boolean Print(BufferedWriter flog) throws IOException // PRINT function
   {
      WordNode pNode=pHead;
      if(pNode!=null) // pNode is exist
      {
         while(pNode!=null) // pNode is exist
         {
            System.out.println(pNode.GetWord()+" "+pNode.GetMean());
            flog.write((pNode.GetWord()+" "+pNode.GetMean()));
            flog.newLine();
            pNode=pNode.GetNext();
         }
         return true;
      }
      else // pNode is not exist
         return false;
   }
   
   public boolean Save(BufferedWriter flog) throws IOException// SAVE function
   {
      
      queueSave = new BufferedWriter(new FileWriter ("to_memorize_word.txt")); // outputting file writer
      if(pHead==null) // head is null
         return false;
      else // head is not null
      {
         WordNode pNode=pHead;

         while(pNode!=null) // looping when pNode will be null
         {
            queueSave.write(pNode.GetWord()+" "+pNode.GetMean());
            queueSave.newLine();
            pNode=pNode.GetNext();
         }
         queueSave.close();
         return true;
      }
   }
}