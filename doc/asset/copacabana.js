//======================================================================================================================
//  Copacabana - Common CMake Package Tools
//  Copyright : Copacabana Project Contributors
//  SPDX-License-Identifier: BSL-1.0
//======================================================================================================================

class Copacabana
{
  // filter.py rewrites every mention of a detail namespace into <prefix>_implementation_defined before doxygen parses
  // it, which is what keeps those names out of the generated pages. What lands in the text is that token; this turns it
  // into the /*implementation defined*/ a reader expects, and says why on hover.
  static hideImplementationDefined()
  {
    document.addEventListener("DOMContentLoaded", function ()
    {
      const pattern = /\b\w+_implementation_defined\b/g;
      const walker = document.createTreeWalker(document.body, NodeFilter.SHOW_TEXT, null, false);
      const targets = [];

      let node;
      while ((node = walker.nextNode()))
      {
        if (pattern.test(node.nodeValue)) { targets.push(node); pattern.lastIndex = 0; }
      }

      targets.forEach(textNode =>
      {
        const container = document.createElement("span");
        container.innerHTML = textNode.nodeValue.replace(
          pattern,
          '<span class="comment" title="This type is implementation defined and not part of the public API">'
          + '/*implementation defined*/</span>');

        while (container.firstChild) { textNode.parentNode.insertBefore(container.firstChild, textNode); }
        textNode.parentNode.removeChild(textNode);
      });
    });
  }
}
