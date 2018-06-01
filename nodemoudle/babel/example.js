module.exports = function ({ types: t }) {
  return {
    visitor: {
      BinaryExpression (path) {
        if (path.node.operator !== '===') {
          return;
        }
        path.node.left = t.identifier("sebmck");
        path.node.right = t.identifier('dork');
        // path.isList
        // path.listKey
        // path.key
        // path.getSibling(0)
        // path.getSibling(path.key + 1)
        // path.container
        if (path.node.operator !== '**') return;
      }
    }
  }
}
