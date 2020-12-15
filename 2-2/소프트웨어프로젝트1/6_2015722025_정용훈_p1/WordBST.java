package p1;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class WordBST { // Class WordBST

   public WordNode root;   // Word BST Root
      
   public WordBST()
   {
      
   }
   
   public void Insert(WordNode node) // Insertion of Word 
   {
      WordNode p = root, pp = null; // Declaration of node and set to null
      while (p!=null) // while p isn't null
      {
         pp = p; // set pp to p
         if (node.GetWord().compareTo(p.GetWord()) < 0) // if node that is inserted is smaller 
            p = p.GetLeft(); // get to left child
         else if (node.GetWord().compareTo(p.GetWord()) > 0) // if node that is inserted is bigger
            p = p.GetRight(); // get to right child

         else
            break; // break
      }

      if (root!=null) // if root isn't null
      {
         if (node.GetWord().compareTo(pp.GetWord()) < 0) // if node that is inserted is smaller
            pp.SetLeft(node); // set to left child
         else // if node that is inserted is bigger
            pp.SetRight(node); // set to right child
      }
      else // if root is null
         root = node; // set root to node
   }
   
   public WordNode Delete(String word) // Delete
   {
      WordNode pNode=root; // set pnode to root
      WordNode ppNode=null; // set pnode to null
      while(pNode!=null) // loop while pnode isn't null
      {
         ppNode=pNode; // set ppnode to pnode
         if(pNode.GetWord().compareTo(word)<0) // if pnode's word is smaller than word
            pNode=pNode.GetRight(); // set pnode's right child
         else if(pNode.GetWord().compareTo(word)>0) // if pnode's word is bigger than word
            pNode=pNode.GetLeft(); // set pnode's left child
         else
            break; // break
      }
      
      if(pNode==null) // if pnode is null 
         return null;
      else if(pNode.GetLeft()==null&&pNode.GetRight()==null) // if pnode's left and right are null
      {
         if(ppNode==null) // if ppnode is null
            root=null; // set root to null
         else if(ppNode.GetLeft()==pNode) // if ppnode's left is same as pnode
            ppNode.SetLeft(null); // set ppnode's left child to null
         else 
            ppNode.SetRight(null); // ppnode's right child to null
         pNode=null; // set pnode to null
      }
      else if(pNode.GetLeft()!=null) // if left child isn't null
      {
         WordNode prevprev=pNode; // prevprev node to pnode
         WordNode prev=pNode.GetLeft(); // prev node to left child
         WordNode curr=pNode.GetLeft().GetRight(); // current node to left child's right child
         
         while(curr!=null) // loop while current isn't null
         {
            prevprev = prev; // set prevprev to prev
            prev = curr; // set prev to current
            curr = curr.GetRight(); // set current to current's right child
         }
         
         pNode.SetWord(prev.GetWord()); // set pnode to prev's node's word
         pNode.SetMean(prev.GetMean()); // set pnode to prev's node's mean
         prev.DeletePair(prev); // delete prev pair node
         if (prevprev == pNode) // if prevprev is same as pnode
            prevprev.SetLeft(prev.GetLeft()); // set prevprev's left node to prev's left child
         else
            prevprev.SetRight(prev.GetLeft()); // set prevprev's right node to prev's right child
         prev=null; // set prev to null
      }
      else
      {
         WordNode prevprev=pNode; // prevprev node to pnode
         WordNode prev=pNode.GetRight(); // prev node to right child
         WordNode curr=pNode.GetRight().GetLeft(); // current node to right child's left child
         while(curr!=null) // loop while current isn't null
         {
            prevprev = prev; // set prevprev to prev
            prev = curr; // set prev to current
            curr = curr.GetLeft(); // set current to current's left child
         }
         
         pNode.SetWord(prev.GetWord()); // set pnode to prev's node's word
         pNode.SetMean(prev.GetMean()); // set pnode to prev's node's mean
         prev.DeletePair(prev); // delete prev pair node
         if (prevprev == pNode) // if prevprev is same as pnode
            prevprev.SetRight(prev.GetRight()); //set prevprev's right node to prev's right child
         else
            prevprev.SetLeft(prev.GetRight()); // set prevprev's left node to prev's right child
         prev=null; // set prev to null
      }
      return null;
   }
   
   public WordNode Search(String word) // Search
   {
      WordNode pNode=root; // set pnode to root
      
      while(pNode!=null) // loop while pnode isn't 
      {
         if(pNode.GetWord().compareTo(word)<0) // if pnode's word is bigger than inserted
            pNode=pNode.GetRight(); // set pnode to right child
         else if(pNode.GetWord().compareTo(word)>0) // if pnode's  word is smaller than inserted
            pNode=pNode.GetLeft(); // set pnode to left child
         else
            return pNode;
      }
      return null;
   }
   public boolean Print(BufferedWriter flog) throws IOException // Print
   {
      if(root==null) // if root is null
         return false;
      Preorder(root, flog); // preorder print
      return true;
   }
   public boolean Save(BufferedWriter bstSave) throws IOException // Save
   {
      if(root==null) // if root is null
         return false;
      
      SavePreorder(root,bstSave); // save preorder
      return true;
   }
   
   public void   Preorder(WordNode node, BufferedWriter flog) throws IOException // Preorder Travesal
   {
      if(node!=null) // if node isn't null
      {
         System.out.println(node.GetWord()+" "+node.GetMean());
         flog.write(node.GetWord()+" "+node.GetMean());
         flog.newLine();
         Preorder(node.GetLeft(), flog); // recursive
         Preorder(node.GetRight(), flog); // recursive
      }

      return;
   }
   
   public void   SavePreorder(WordNode node,BufferedWriter bstSave) throws IOException // Save preorder
   {
      if(node!=null) // if node isn't null
      {
         bstSave.write(node.GetWord()+" "+node.GetMean());
         bstSave.newLine();
         SavePreorder(node.GetLeft(),bstSave); // recursive save
         SavePreorder(node.GetRight(),bstSave); // recursive save
      }
      return;
   }

}