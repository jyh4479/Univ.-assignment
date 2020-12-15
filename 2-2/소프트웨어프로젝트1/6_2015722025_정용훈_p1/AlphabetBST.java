package p1;

import java.io.BufferedWriter; // import declaration
import java.io.FileWriter; // import declaration
import java.io.IOException; // import declaration

public class AlphabetBST { // AlphabetBST class
   //private variable initial set 
   private AlphabetNode root=null;
   private int WordCnt=0; 
   private int count=1;
   public AlphabetBST() // constructor
   {
      root = null;
      WordCnt = 0;
      
      char[] alpha = { 'P', 'H', 'X', 'D', 'L', 'T', 'Z', 'B', 'F', 'J', 'N', 'R', 'V', 'Y', 'A', 'C', 'E', 'G', 'I', 'K',
         'M', 'O', 'Q', 'S', 'U', 'W' };//insert alphabet 
      
      for (int i = 0; i < 26; i++) //26 ( number of alphabet ) 
      {
         AlphabetNode pnew = new AlphabetNode(); // dynamic allocation
         pnew.SetAlphabet(alpha[i]); // set alphabet
         Insert(pnew); // insert alphabet
      }
   }
      
   public void Insert(AlphabetNode node) // insert function
   {
      AlphabetNode p = root, pp = null;
      while (p!=null) // looping when p will be null
      {
         pp = p;
         if (node.GetAlphabet() < p.GetAlphabet()) // node's alphabet < p's alphabet
            p = p.GetLeft(); // move left
         else if (node.GetAlphabet() > p.GetAlphabet()) // node's alphabet > p's alphabet
            p = p.GetRight(); // move right
      }

      if (root!=null) // when root is not null
      {
         if (node.GetAlphabet() < pp.GetAlphabet()) // node's alphabet < pp's alphabet
            pp.SetLeft(node); // set left 
         else //  // node's alphabet > pp's alphabet
            pp.SetRight(node); // set right
      }
      else // root is null
         root = node; // root set
   }
   
   public boolean Print(BufferedWriter flog) throws IOException // Print function
   {
      if(root==null) // root is null
         return false;
      Preorder(root, flog); // preordering when root is not null
      return true;
   }
   
   
   public AlphabetNode Search(char alphabet) // Search function
   {
      AlphabetNode tmp = root;
      while (tmp!=null) // looping when tmp will be null
      {
         if (alphabet-32 < tmp.GetAlphabet()) // when alphabet < tmp's alphabet
            tmp = tmp.GetLeft(); // move left
         else if (alphabet-32 > tmp.GetAlphabet()) // when alphabet > tmp's alphabet
            tmp = tmp.GetRight(); // move right
         else // when alphabet = tmp's alphabet
         {
            return tmp;
         }
      }
      return null; //  // when alphabet != tmp's alphabet
   }
   
   public boolean Save(BufferedWriter flog) throws IOException // save function
   {
      BufferedWriter bstSave=new BufferedWriter(new FileWriter ("memorizing_word.txt")); // ouputting text file 

      if(root==null) // empty bst
         return false;
      SavePreorder(root,bstSave); // save to text file using preordering
      bstSave.close();
      return true;
   }

   public void   Preorder(AlphabetNode node, BufferedWriter flog) throws IOException // Print bst using preordering
   {
      if(node!=null) // node is not null
      {         
         if(node.GetBST()!=null) // node's wordBst is not null
            node.GetBST().Print(flog); // printing wordBST 
         Preorder(node.GetLeft(),flog); // left child preordering
         Preorder(node.GetRight(),flog); // right child preordering
      }
      return;
   }
   
   public void   SavePreorder(AlphabetNode node,BufferedWriter bstSave) throws IOException // Save bst using preordering
   {
      if(node!=null) // node is not null
      {
         if(node.GetBST()!=null) // node's wordBst is not null
            node.GetBST().Save(bstSave); // save wordBST using preordering
         SavePreorder(node.GetLeft(),bstSave); // left child preordering
         SavePreorder(node.GetRight(),bstSave); // right child preordering
      }
      return;
   }

   public int getCnt() // return WordCnt 
   {
      return WordCnt;
   }
   public void setCnt(int cnt) // setting WordCnt
   {
      WordCnt=cnt;
   }
}