const createNode = function (value) {
  return { left: null, right: null, value };
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

const tree = [5, 3, 8, 1, 4, 7, 9].reduce(insert, null);
// console.log(tree);
console.log(printInOrder(tree));
console.log(printPreOrder(tree));
console.log(printPostOrder(tree));
