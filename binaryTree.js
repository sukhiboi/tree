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

const getParent = function (tree, value) {
  const isCorrectNode =
    (tree.left && tree.left.value == value) ||
    (tree.right && tree.right.value == value) ||
    tree.value == value;
  if (isCorrectNode) return tree;
  if (value < tree.value) {
    return getParent(tree.left, value);
  } else {
    return getParent(tree.right, value);
  }
};

const getMaxNode = function (tree) {
  if (tree.right == null) return tree;
  return getMaxNode(tree.right);
};

const getMinNode = function (tree) {
  if (tree.left == null) return tree;
  return getMinNode(tree.left);
};

const getCompatibleNode = function (tree) {
  if (tree.left != null) return getMaxNode(tree.left);
  if (tree.right != null) return getMinNode(tree.right);
  return null;
};

const getNodeToDelete = function (parent, value) {
  if (parent.right && parent.right.value == value) return parent.right;
  return parent.left;
};

const deleteLeafNode = function (parent, node) {
  if (parent.right && parent.right.value == node.value) parent.right = null;
  if (parent.left && parent.left.value == node.value) parent.left = null;
};

const deleteNode = function (tree, node_to_delete) {
  const compatibleNode = getCompatibleNode(node_to_delete);
  const node_to_delete_parent = getParent(tree, node_to_delete.value);
  if (compatibleNode == null)
    return deleteLeafNode(node_to_delete_parent, node_to_delete);
  const parent = getParent(tree, compatibleNode.value);
  let temp = compatibleNode.value;
  node_to_delete.value = compatibleNode.value;
  compatibleNode.value = temp;
  if (compatibleNode.right == null && compatibleNode.left == null) {
    return deleteLeafNode(parent, compatibleNode);
  }
  deleteNode(compatibleNode, compatibleNode);
};

const tree = [10, 5, 20].reduce(insert, null);
deleteNode(tree, tree);
console.log(tree);
