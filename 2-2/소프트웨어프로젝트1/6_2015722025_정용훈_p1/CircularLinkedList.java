package p1;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class CircularLinkedList { // Class Circular Linked List
   public WordNode pHead;   // Circular Linked List Head Pointer
   public WordNode pTail; // Circular Linked List Tail Pointer
   public BufferedWriter cllSave=null; // declaration of Circular Linked List save file writer
   public CircularLinkedList()
   
   {
      pHead=null; // set Head node to null
      pTail=null; // set tail node to null
   }
   
   public void Insert(WordNode node) // Insertion of Circular Linked List
   {
      if(pHead==null) // if head node is null
      {
         pHead=node; // set word node to head node
         node.SetNext(pHead); // set next node
         pTail=node; // set node to tail node
      }
      else // if there is node
      {
         pTail.SetNext(node); // link nodes
         node.SetNext(pHead); // set next node
         pTail=node; // set node to tail node
      }
   }
   
   public WordNode Search(String word) // Search 
   {
      WordNode pNode=pHead; // set pnode to head node
      
      while(pNode!=pTail) // loop while head node isn't tail
      {
         if(pNode.GetWord().equals(word)) // if word of pnode that comes is same as word 
            return pNode;
         pNode=pNode.GetNext(); // set pnode to pnode's next
      }
      if(pNode.GetWord().equals(word)) // if word of pnode that comes is same as word
         return pNode;
      else
         return null;
   }
   
   public boolean   Print(BufferedWriter flog) throws IOException // Print
   {   
      WordNode pNode=pHead; // set pnode to head node
      if(pHead!=null) // if head node isn't null
      {
         while(pNode!=pTail) // while pnode isn't tail node
         {
            System.out.println(pNode.GetWord()+" "+pNode.GetMean()); 
            flog.write(pNode.GetWord()+" "+pNode.GetMean());
            flog.newLine();
            pNode=pNode.GetNext(); // Set pnode to pnode's next
         }
         System.out.println(pNode.GetWord()+" "+pNode.GetMean());
         flog.write(pNode.GetWord()+" "+pNode.GetMean());
         flog.newLine();

            return true;
      }
      else
         return false;
   }
   
   public boolean   Save(BufferedWriter flog) throws IOException // save
   {
      
      cllSave = new BufferedWriter(new FileWriter ("memorized_word.txt")); // Circular Linked List save file
      if(pHead==null) // if head node is null
         return false;
      else
      {
      
         WordNode pNode=pHead; // Set pnode to head node
         cllSave.write(pNode.GetWord()+" "+pNode.GetMean());
         cllSave.newLine();
         pNode=pNode.GetNext(); // set pnode to pnode's next node
         while(pNode!=pHead) // loop while pnode isn't head node
         {
            cllSave.write(pNode.GetWord()+" "+pNode.GetMean());
            cllSave.newLine();
            pNode=pNode.GetNext(); // set pnode to pnode's next node 
         }
         cllSave.close(); // close save file
         return true;
      }
   }
}
