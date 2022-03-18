$( document ).ready(function() {

  // Get a reference to the link on the page with an id of "godbolt-link"
  var a = document.getElementById("godbolt-link");

  // If it exists, add a onClick handler
  if(a)
  {
    a.onclick = function()
    {
      // Retrieve the cleanup contents of the div and remove spurious contents if any
      var node        = document.getElementById('godbolt');
      var textContent = node.textContent;
          textContent = textContent.slice(0,textContent.lastIndexOf('}')+1);
          textContent = textContent.trim();

      // Prepare a CE ClientState using the example code + our setup
      let data = {
                    "sessions": [
                      {
                        "id": 1,
                        "language": "c++",
                        "source": textContent,
                        "compilers":  [],
                        "executors": [
                                      {
                                        "compiler":
                                        {
                                            "id": "clang1301",
                                            "libs": [ {"id": "eve", "version": "trunk"}],
                                            "options": "-DEVE_NO_FORCEINLINE -std=c++20 -DNDEBUG"
                                        }
                                      }
                                    ]
                        }
                      ]
                  };

      // Turn into BASE64 and use /clientstate API
      let body  = JSON.stringify(data);
      let state = btoa(body);
      let url   = "https://godbolt.org/clientstate/" + state;

      // Open in a new tab
      window.open(url, "_blank");

      // Don't modify actual page
      return false;
    }
  }
});
