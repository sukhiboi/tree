const createNode = function (value) {
  return { value, left: null, right: null };
};

const insert = function (tree, value) {
  if (tree == null) return createNode(value);
  if (value < tree.value) tree.left = insert(tree.left, value);
  else tree.right = insert(tree.right, value);
  return tree;
};

const printInOrder = function (tree) {
  if (tree == null) return '';
  printInOrder(tree.left);
  process.stdout.write(`${tree.value} `);
  printInOrder(tree.right);
};

const printPreOrder = function (tree) {
  if (tree == null) return '';
  process.stdout.write(`${tree.value} `);
  printPreOrder(tree.left);
  printPreOrder(tree.right);
};

const printPostOrder = function (tree) {
  if (tree == null) return '';
  printPostOrder(tree.left);
  printPostOrder(tree.right);
  process.stdout.write(`${tree.value} `);
};

const search = function (tree, value) {
  if (tree == null) return false;
  if (tree.value == value) return true;
  if (value < tree.value) return search(tree.left, value);
  return search(tree.right, value);
};

/**
 * 1. if node is leaf...
 * 2. if node left is empty
 * 3. if node right is empty
 */

const getParent = function (parent, tree, value) {
  if (tree == null) return null;
  if (tree.value == value) return parent;
  if (value < tree.value) {
    return getParent(tree, tree.left, value);
  }
  return getParent(tree, tree.right, value);
};

const getCompatibleNode = function (node) {
  if (node.left == null) return node;
  let compatibleNode = node.left;
  while (compatibleNode.right != null) compatibleNode = compatibleNode.right;
  return compatibleNode;
};

const deleteLeafNode = function (tree, node) {
  const parent = getParent(tree, tree, node.value);
  if (parent.left.value == node.value) parent.left = null;
  if (parent.right.value == node.value) parent.right = null;
};

const deleteNode = function (tree, node) {
  let compatibleNode = getCompatibleNode(node);
  node.value = compatibleNode.value;
  if (compatibleNode.left == null && compatibleNode.right == null)
    return deleteLeafNode(tree, compatibleNode);
  deleteNode(tree, compatibleNode);
};

const tree = [10, 5, 20].reduce(insert, null);
deleteNode(tree, tree);
console.log(tree);

/**
DOING WITH MAX OF LEFT
STEP1: Choose which element to delete.
STEP2: Get the deepest right node from the left child of the tree (call it compatible)
STEP3: Swap the value's of the both the nodes (i.e. the compatible and the one you want to delete)
STEP4: Check if compatible node have any left child if yes
            then make the child the right child of the grandparent (compatible's parent) node
STEP5: Delete the compatible
 */
