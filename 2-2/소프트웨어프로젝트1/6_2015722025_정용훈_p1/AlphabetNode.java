package p1;

public class AlphabetNode {
   private char alphabet;
   private WordBST bst=null;
   private AlphabetNode pLeft=null;      // BST Left Pointer
   private AlphabetNode pRight=null;;   // BST Right Pointer

   public AlphabetNode()
   {

   }
   
   public char GetAlphabet() // get alphabet
   {
      return alphabet; // return alphabet
   }
   
   public WordBST GetBST() // get bst
   {
      return bst; // return bst
   }
   
   public AlphabetNode GetLeft() // get left 
   {
      return pLeft; // return left
   }
   
   public AlphabetNode GetRight() // get right
   {
      return pRight; // retrun right
   }
   
   public void   SetAlphabet(char alphabet) // set alphabet
   {
      this.alphabet=alphabet; // set alphabet
   }
   
   public void   SetLeft(AlphabetNode node) // set left
   {
      pLeft=node; // set node to left
   }
   
   public void   SetRight(AlphabetNode node) // set right 
   {
      pRight=node; // set node to right
   }
   
   public void SetBST(WordBST node) // set bst
   {
      bst=node; // set node to bst
   }

}