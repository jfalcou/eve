<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.16.1" doxygen_gitid="669aeeefca743c148e2d935b3d3c69535c7491e6">
  <compound kind="struct">
    <name>eve::abi</name>
    <filename>structeve_1_1abi.html</filename>
    <templarg>typename Type</templarg>
    <templarg>typename Lanes</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::aligned_allocator</name>
    <filename>structeve_1_1aligned__allocator.html</filename>
    <templarg>typename T</templarg>
    <templarg>typename Lanes</templarg>
    <class kind="struct">eve::aligned_allocator::rebind</class>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>structeve_1_1aligned__allocator.html</anchorfile>
      <anchor>a1172a3003ffee8879d69bc92082ba045</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>aligned_allocator</name>
      <anchorfile>structeve_1_1aligned__allocator.html</anchorfile>
      <anchor>ad3fc2e77e415c955d485eae055dd3a8a</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>aligned_allocator</name>
      <anchorfile>structeve_1_1aligned__allocator.html</anchorfile>
      <anchor>a403bc4b07dcee24ed6e85677b0d81c22</anchor>
      <arglist>(aligned_allocator&lt; U, Lanes &gt; const &amp;) noexcept</arglist>
    </member>
    <member kind="function">
      <type>value_type *</type>
      <name>allocate</name>
      <anchorfile>structeve_1_1aligned__allocator.html</anchorfile>
      <anchor>a9ab5015c20a31794a6c1625a58c5ba9a</anchor>
      <arglist>(std::size_t n)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>deallocate</name>
      <anchorfile>structeve_1_1aligned__allocator.html</anchorfile>
      <anchor>af60ee2a91559c5158a13ab8b81f3b2f9</anchor>
      <arglist>(value_type *p, std::size_t) noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr auto</type>
      <name>alignment</name>
      <anchorfile>structeve_1_1aligned__allocator.html</anchorfile>
      <anchor>a5331332172952bf428e51bdf7d53e3bc</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1aligned__allocator.html</anchorfile>
      <anchor>a5b517ec4c0b7a4057e37591cf5ebf87d</anchor>
      <arglist>(aligned_allocator&lt; T, A &gt; const &amp;, aligned_allocator&lt; U, B &gt; const &amp;) noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>structeve_1_1aligned__allocator.html</anchorfile>
      <anchor>a27ab460322a8ed553b665c9da4cd0e38</anchor>
      <arglist>(aligned_allocator&lt; T, A &gt; const &amp;, aligned_allocator&lt; U, B &gt; const &amp;) noexcept</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::aligned_ptr</name>
    <filename>structeve_1_1aligned__ptr.html</filename>
    <templarg>typename Type</templarg>
    <templarg>typename Lanes</templarg>
    <member kind="typedef">
      <type>std::remove_const_t&lt; Type &gt;</type>
      <name>value_type</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>aed55f842914bf195c481887441623ca4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::add_pointer_t&lt; Type &gt;</type>
      <name>pointer</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a01fcaadfc18462725723c6ab049a7153</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>aligned_ptr&lt; T, Lanes &gt;</type>
      <name>rebind</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>ad093d3fbfa02d18d397c33ecbc5b81ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>aligned_ptr</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a243a4819a3e6659e3096adcfb4ed366a</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>aligned_ptr</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a838df7b2c90202ade0f45d01f8134058</anchor>
      <arglist>(std::nullptr_t) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>aligned_ptr</name>
      <anchorfile>structeve_1_1aligned__ptr_a5376a9155a39e6d311e361ef365c222f.html</anchorfile>
      <anchor>a5376a9155a39e6d311e361ef365c222f</anchor>
      <arglist>(pointer p) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>aligned_ptr</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a70871f0fbce27686b5bc87745ada5698</anchor>
      <arglist>(aligned_ptr&lt; UType, L &gt; p) noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr &amp;</type>
      <name>operator=</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>ac34c57982bdea91092bd8d24ed25802d</anchor>
      <arglist>(aligned_ptr&lt; Type, L &gt; p) noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr &amp;</type>
      <name>operator+=</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a2fe3040a6a80afb80eec6e058f4ce9b8</anchor>
      <arglist>(std::ptrdiff_t o) noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr &amp;</type>
      <name>operator-=</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>af6dfde7e9c59f0f8d1cda928fc4e07b9</anchor>
      <arglist>(std::ptrdiff_t o) noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr &amp;</type>
      <name>operator++</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>ad762c64085048c2ba6ae0b8d128bc401</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr</type>
      <name>operator++</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a8f6465c2dbe7f3eafd1f3224fba2cc51</anchor>
      <arglist>(int) noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr &amp;</type>
      <name>operator--</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>ab5f56e187fd085ffc8df8352fbe6f2fd</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr</type>
      <name>operator--</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>ab455c40952363fcdc630a5a192282558</anchor>
      <arglist>(int) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>ab30d7f5154fcc11c9538fb558cbbe7e6</anchor>
      <arglist>(aligned_ptr &amp;that) noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>operator&lt;=&gt;</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a75251b3b42de23e7b33fb87f53d20431</anchor>
      <arglist>(const aligned_ptr&lt; Type, Lanes &gt; &amp;) const =default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a45d36841620158a67436c4c285b16551</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator pointer</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a3eae8f3254e53333dbad75b49401adea</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>pointer</type>
      <name>get</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>aa6c43a41bc91bdc491818820953f7b4d</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>operator*</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>ab37c8571471bda0e72b365cc4d8f9e59</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>operator*</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a99c4ca7e6e42bbec8323085cd27f55e0</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>operator-&gt;</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>aaa88aa0d88cf52b4669be820cca0866b</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>operator-&gt;</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a2c90d6ce8b8bf13b7e09cf4b06c7a271</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr auto</type>
      <name>alignment</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>ac492dbb48b2314f4d9b874fe6cfbe79e</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr&lt; Type, Lanes &gt;</type>
      <name>as_aligned</name>
      <anchorfile>structeve_1_1aligned__ptr_a52d5ad94329c310ad8cb583b4e3f19f1.html</anchorfile>
      <anchor>a52d5ad94329c310ad8cb583b4e3f19f1</anchor>
      <arglist>(Type *ptr, Lanes lanes) noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr&lt; Type &gt;</type>
      <name>as_aligned</name>
      <anchorfile>structeve_1_1aligned__ptr_ac2f686e634604536ddbdcfce629887f3.html</anchorfile>
      <anchor>ac2f686e634604536ddbdcfce629887f3</anchor>
      <arglist>(Type *ptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>previous_aligned_address</name>
      <anchorfile>structeve_1_1aligned__ptr_a28fd884a05e3b74a5252025c69239e7f.html</anchorfile>
      <anchor>a28fd884a05e3b74a5252025c69239e7f</anchor>
      <arglist>(T *p, Lanes width) noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>previous_aligned_address</name>
      <anchorfile>structeve_1_1aligned__ptr_a911aab2fb14b05dcc4625f412282dbe1.html</anchorfile>
      <anchor>a911aab2fb14b05dcc4625f412282dbe1</anchor>
      <arglist>(T *p) noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>next_aligned_address</name>
      <anchorfile>structeve_1_1aligned__ptr_af5f46ed7531da24993e83cbd4ac128c0.html</anchorfile>
      <anchor>af5f46ed7531da24993e83cbd4ac128c0</anchor>
      <arglist>(T *p, Lanes width) noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>next_aligned_address</name>
      <anchorfile>structeve_1_1aligned__ptr_ab3183f3cbe25f5af3b5d3842a76a7cfb.html</anchorfile>
      <anchor>ab3183f3cbe25f5af3b5d3842a76a7cfb</anchor>
      <arglist>(T *p) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>aligned_ptr</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a243a4819a3e6659e3096adcfb4ed366a</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>aligned_ptr</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a838df7b2c90202ade0f45d01f8134058</anchor>
      <arglist>(std::nullptr_t) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>aligned_ptr</name>
      <anchorfile>structeve_1_1aligned__ptr_a5376a9155a39e6d311e361ef365c222f.html</anchorfile>
      <anchor>a5376a9155a39e6d311e361ef365c222f</anchor>
      <arglist>(pointer p) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>aligned_ptr</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a70871f0fbce27686b5bc87745ada5698</anchor>
      <arglist>(aligned_ptr&lt; UType, L &gt; p) noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr &amp;</type>
      <name>operator=</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>ac34c57982bdea91092bd8d24ed25802d</anchor>
      <arglist>(aligned_ptr&lt; Type, L &gt; p) noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr &amp;</type>
      <name>operator+=</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a2fe3040a6a80afb80eec6e058f4ce9b8</anchor>
      <arglist>(std::ptrdiff_t o) noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr &amp;</type>
      <name>operator-=</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>af6dfde7e9c59f0f8d1cda928fc4e07b9</anchor>
      <arglist>(std::ptrdiff_t o) noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr &amp;</type>
      <name>operator++</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>ad762c64085048c2ba6ae0b8d128bc401</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr</type>
      <name>operator++</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a8f6465c2dbe7f3eafd1f3224fba2cc51</anchor>
      <arglist>(int) noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr &amp;</type>
      <name>operator--</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>ab5f56e187fd085ffc8df8352fbe6f2fd</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr</type>
      <name>operator--</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>ab455c40952363fcdc630a5a192282558</anchor>
      <arglist>(int) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>ab30d7f5154fcc11c9538fb558cbbe7e6</anchor>
      <arglist>(aligned_ptr &amp;that) noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>operator&lt;=&gt;</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a75251b3b42de23e7b33fb87f53d20431</anchor>
      <arglist>(const aligned_ptr&lt; Type, Lanes &gt; &amp;) const =default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a45d36841620158a67436c4c285b16551</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator pointer</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a3eae8f3254e53333dbad75b49401adea</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>pointer</type>
      <name>get</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>aa6c43a41bc91bdc491818820953f7b4d</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>operator*</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>ab37c8571471bda0e72b365cc4d8f9e59</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>operator*</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a99c4ca7e6e42bbec8323085cd27f55e0</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>operator-&gt;</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>aaa88aa0d88cf52b4669be820cca0866b</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>operator-&gt;</name>
      <anchorfile>structeve_1_1aligned__ptr.html</anchorfile>
      <anchor>a2c90d6ce8b8bf13b7e09cf4b06c7a271</anchor>
      <arglist>() noexcept</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::as</name>
    <filename>structeve_1_1as.html</filename>
    <templarg>typename T</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>type</name>
      <anchorfile>structeve_1_1as.html</anchorfile>
      <anchor>a904ff0e88e1f435dc24505e3168b52f5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::as_element</name>
    <filename>structeve_1_1as__element.html</filename>
    <templarg>typename T</templarg>
    <base>eve::as&lt; element_type_t&lt; T &gt; &gt;</base>
    <member kind="typedef">
      <type>T</type>
      <name>type</name>
      <anchorfile>structeve_1_1as.html</anchorfile>
      <anchor>a904ff0e88e1f435dc24505e3168b52f5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::as_pattern</name>
    <filename>structeve_1_1as__pattern.html</filename>
    <templarg>pattern_formula F</templarg>
  </compound>
  <compound kind="struct">
    <name>backward_iterator</name>
    <filename>structbackward__iterator.html</filename>
  </compound>
  <compound kind="struct">
    <name>eve::algo::views::backward_iterator</name>
    <filename>structeve_1_1algo_1_1views_1_1backward__iterator.html</filename>
    <templarg>relaxed_iterator I</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::views::backward_iterator</name>
    <filename>structeve_1_1views_1_1backward__iterator.html</filename>
    <templarg>relaxed_iterator I</templarg>
  </compound>
  <compound kind="struct">
    <name>backward_range</name>
    <filename>structbackward__range.html</filename>
  </compound>
  <compound kind="struct">
    <name>eve::algo::views::backward_range</name>
    <filename>structeve_1_1algo_1_1views_1_1backward__range.html</filename>
    <templarg>non_owning_range R</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::views::backward_range</name>
    <filename>structeve_1_1views_1_1backward__range.html</filename>
    <templarg>non_owning_range R</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::callable</name>
    <filename>structeve_1_1callable.html</filename>
    <templarg>template&lt; typename &gt; class Func</templarg>
    <templarg>typename OptionsValues</templarg>
    <templarg>typename... Options</templarg>
    <base>eve::decorated_with&lt; OptionsValues, Options... &gt;</base>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator[]</name>
      <anchorfile>structeve_1_1decorated__with_af3a21e9dd9b24936ba6cce9aae413f5c.html</anchorfile>
      <anchor>af3a21e9dd9b24936ba6cce9aae413f5c</anchor>
      <arglist>(O o) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>options</name>
      <anchorfile>structeve_1_1decorated__with.html</anchorfile>
      <anchor>ac221db6bdb072c16cc54863e8f901bb2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend constexpr bool</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1callable.html</anchorfile>
      <anchor>ae7854c3c19c003878d34e5473ae82f55</anchor>
      <arglist>(callable const &amp;, callable&lt; F2, OV2, O2... &gt; const &amp;)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::cardinal</name>
    <filename>structeve_1_1cardinal.html</filename>
    <templarg>typename Type</templarg>
    <base>eve::fixed&lt; 1 &gt;</base>
  </compound>
  <compound kind="struct">
    <name>eve::common_compatible</name>
    <filename>structeve_1_1common__compatible.html</filename>
    <templarg>typename... Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::common_type</name>
    <filename>structeve_1_1common__type.html</filename>
    <templarg>typename ... Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::comparisons</name>
    <filename>structeve_1_1comparisons.html</filename>
    <templarg>typename T</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::conditional_option</name>
    <filename>structeve_1_1conditional__option.html</filename>
    <member kind="function">
      <type>constexpr auto</type>
      <name>default_to</name>
      <anchorfile>structeve_1_1conditional__option.html</anchorfile>
      <anchor>a22264e22371f852db8baa9e2b604c500</anchor>
      <arglist>(auto const &amp;base) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::constant_callable</name>
    <filename>structeve_1_1constant__callable.html</filename>
    <templarg>template&lt; typename &gt; class Func</templarg>
    <templarg>typename OptionsValues</templarg>
    <templarg>typename... Options</templarg>
    <base>eve::callable&lt; Func, OptionsValues, conditional_option, Options... &gt;</base>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator[]</name>
      <anchorfile>structeve_1_1decorated__with_af3a21e9dd9b24936ba6cce9aae413f5c.html</anchorfile>
      <anchor>af3a21e9dd9b24936ba6cce9aae413f5c</anchor>
      <arglist>(O o) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>options</name>
      <anchorfile>structeve_1_1decorated__with.html</anchorfile>
      <anchor>ac221db6bdb072c16cc54863e8f901bb2</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>converting_iterator</name>
    <filename>structconverting__iterator.html</filename>
  </compound>
  <compound kind="struct">
    <name>eve::algo::views::converting_iterator</name>
    <filename>structeve_1_1algo_1_1views_1_1converting__iterator.html</filename>
    <templarg>relaxed_iterator I</templarg>
    <templarg>typename T</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::views::converting_iterator</name>
    <filename>structeve_1_1views_1_1converting__iterator.html</filename>
    <templarg>relaxed_iterator I</templarg>
    <templarg>typename T</templarg>
  </compound>
  <compound kind="struct">
    <name>converting_range</name>
    <filename>structconverting__range.html</filename>
  </compound>
  <compound kind="struct">
    <name>eve::algo::views::converting_range</name>
    <filename>structeve_1_1algo_1_1views_1_1converting__range.html</filename>
    <templarg>non_owning_range R</templarg>
    <templarg>typename T</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::views::converting_range</name>
    <filename>structeve_1_1views_1_1converting__range.html</filename>
    <templarg>non_owning_range R</templarg>
    <templarg>typename T</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::decorated_with</name>
    <filename>structeve_1_1decorated__with.html</filename>
    <templarg>typename OptionsValues</templarg>
    <templarg>typename... Options</templarg>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator[]</name>
      <anchorfile>structeve_1_1decorated__with_af3a21e9dd9b24936ba6cce9aae413f5c.html</anchorfile>
      <anchor>af3a21e9dd9b24936ba6cce9aae413f5c</anchor>
      <arglist>(O o) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>options</name>
      <anchorfile>structeve_1_1decorated__with.html</anchorfile>
      <anchor>ac221db6bdb072c16cc54863e8f901bb2</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::element_type</name>
    <filename>structeve_1_1element__type.html</filename>
    <templarg>typename T</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::elementwise_callable</name>
    <filename>structeve_1_1elementwise__callable.html</filename>
    <templarg>template&lt; typename &gt; class Func</templarg>
    <templarg>typename OptionsValues</templarg>
    <templarg>typename... Options</templarg>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator[]</name>
      <anchorfile>structeve_1_1decorated__with_af3a21e9dd9b24936ba6cce9aae413f5c.html</anchorfile>
      <anchor>af3a21e9dd9b24936ba6cce9aae413f5c</anchor>
      <arglist>(O o) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>options</name>
      <anchorfile>structeve_1_1decorated__with.html</anchorfile>
      <anchor>ac221db6bdb072c16cc54863e8f901bb2</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::fixed</name>
    <filename>structeve_1_1fixed.html</filename>
    <templarg>std::ptrdiff_t Cardinal</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::fundamental_cardinal</name>
    <filename>structeve_1_1fundamental__cardinal.html</filename>
    <templarg>typename Type</templarg>
    <templarg>regular_abi ABI</templarg>
    <base>eve::fixed&lt; eve::current_abi_type::template fundamental_cardinal&lt; Type &gt; &gt;</base>
  </compound>
  <compound kind="struct">
    <name>eve::if_</name>
    <filename>structeve_1_1if__.html</filename>
    <templarg>typename C</templarg>
    <member kind="function">
      <type></type>
      <name>if_</name>
      <anchorfile>structeve_1_1if__.html</anchorfile>
      <anchor>a1dd72a0565bcd14b0fa5320d511f39a9</anchor>
      <arglist>(C c)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>else_</name>
      <anchorfile>structeve_1_1if___a3c412a82b915cb199e4e120c916fb32c.html</anchorfile>
      <anchor>a3c412a82b915cb199e4e120c916fb32c</anchor>
      <arglist>(V const &amp;v) const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>mask</name>
      <anchorfile>structeve_1_1if__.html</anchorfile>
      <anchor>a6897dfced8eacc49373a2dcda5d55616</anchor>
      <arglist>(eve::as&lt; T &gt; const &amp;) const</arglist>
    </member>
    <member kind="variable">
      <type>C</type>
      <name>condition_</name>
      <anchorfile>structeve_1_1if__.html</anchorfile>
      <anchor>ab95afb50101c2b268a415e4b4bdeb186</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1if__.html</anchorfile>
      <anchor>a49a333565c51224987b48795bc6eb10d</anchor>
      <arglist>(std::basic_ostream&lt; Ch, Ct &gt; &amp;os, if_ const &amp;c)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::ignore_all_</name>
    <filename>structeve_1_1ignore__all__.html</filename>
    <member kind="function">
      <type>constexpr auto</type>
      <name>else_</name>
      <anchorfile>structeve_1_1ignore__all___ab9a3431b0ec4e4872b1db763fcf3213e.html</anchorfile>
      <anchor>ab9a3431b0ec4e4872b1db763fcf3213e</anchor>
      <arglist>(V const &amp;v) const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>mask</name>
      <anchorfile>structeve_1_1ignore__all__.html</anchorfile>
      <anchor>adcff5af1df65386006d67c4ce9412a50</anchor>
      <arglist>(eve::as&lt; T &gt; const &amp;tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr std::ptrdiff_t</type>
      <name>count</name>
      <anchorfile>structeve_1_1ignore__all__.html</anchorfile>
      <anchor>a66b1bd0cf09b1b995817b9fafd748882</anchor>
      <arglist>(eve::as&lt; T &gt; const &amp;) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool friend</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1ignore__all__.html</anchorfile>
      <anchor>a96e1fd8540348e3e19115e87ebd4963e</anchor>
      <arglist>(ignore_all_ const &amp;, ignore_all_ const &amp;)=default</arglist>
    </member>
    <member kind="friend">
      <type>friend auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1ignore__all__.html</anchorfile>
      <anchor>a16ef1dbaad9ae245433e52c74396c884</anchor>
      <arglist>(std::basic_ostream&lt; Ch, Ct &gt; &amp;os, ignore_all_ const &amp;)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::ignore_extrema</name>
    <filename>structeve_1_1ignore__extrema.html</filename>
    <member kind="function">
      <type>constexpr auto</type>
      <name>else_</name>
      <anchorfile>structeve_1_1ignore__extrema_a8b1bf4ee47838a4ae4897f6bcd21b93c.html</anchorfile>
      <anchor>a8b1bf4ee47838a4ae4897f6bcd21b93c</anchor>
      <arglist>(V const &amp;v) const</arglist>
    </member>
    <member kind="function">
      <type>as_logical_t&lt; T &gt;</type>
      <name>mask</name>
      <anchorfile>structeve_1_1ignore__extrema.html</anchorfile>
      <anchor>a4a2136bdee642bce65e9983043d1c488</anchor>
      <arglist>(eve::as&lt; T &gt; tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr std::ptrdiff_t</type>
      <name>count</name>
      <anchorfile>structeve_1_1ignore__extrema.html</anchorfile>
      <anchor>ad148db66efa7766713e4ab46755f0f12</anchor>
      <arglist>(eve::as&lt; T &gt; tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool friend</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1ignore__extrema.html</anchorfile>
      <anchor>ab553daa802541398e3dd66455c0b2706</anchor>
      <arglist>(ignore_extrema const &amp;, ignore_extrema const &amp;)=default</arglist>
    </member>
    <member kind="friend">
      <type>friend auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1ignore__extrema.html</anchorfile>
      <anchor>ad947bba4ba0fbd0402604ed785a6f295</anchor>
      <arglist>(std::basic_ostream&lt; Ch, Ct &gt; &amp;os, ignore_extrema const &amp;c)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::ignore_first</name>
    <filename>structeve_1_1ignore__first.html</filename>
    <member kind="function">
      <type>constexpr auto</type>
      <name>else_</name>
      <anchorfile>structeve_1_1ignore__first_a1a451ef557edf9be9754f6b7dde9e0ea.html</anchorfile>
      <anchor>a1a451ef557edf9be9754f6b7dde9e0ea</anchor>
      <arglist>(V const &amp;v) const</arglist>
    </member>
    <member kind="function">
      <type>as_logical_t&lt; T &gt;</type>
      <name>mask</name>
      <anchorfile>structeve_1_1ignore__first.html</anchorfile>
      <anchor>a9542a4416c2fdd4465e331f8536574d0</anchor>
      <arglist>(eve::as&lt; T &gt; tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr std::ptrdiff_t</type>
      <name>count</name>
      <anchorfile>structeve_1_1ignore__first.html</anchorfile>
      <anchor>a3efcef66ff751ec8f01b38a538e06be7</anchor>
      <arglist>(eve::as&lt; T &gt; tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool friend</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1ignore__first.html</anchorfile>
      <anchor>ad7e3fb7e846eb8b2913808a62d0ba092</anchor>
      <arglist>(ignore_first const &amp;, ignore_first const &amp;)=default</arglist>
    </member>
    <member kind="friend">
      <type>friend auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1ignore__first.html</anchorfile>
      <anchor>a86ef239bf55e13954f2765bcca3073c2</anchor>
      <arglist>(std::basic_ostream&lt; Ch, Ct &gt; &amp;os, ignore_first const &amp;c)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::ignore_last</name>
    <filename>structeve_1_1ignore__last.html</filename>
    <member kind="function">
      <type>constexpr</type>
      <name>ignore_last</name>
      <anchorfile>structeve_1_1ignore__last.html</anchorfile>
      <anchor>a0226e07677869fe33508c2d80a87d819</anchor>
      <arglist>(std::ptrdiff_t n) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>else_</name>
      <anchorfile>structeve_1_1ignore__last_a7c4efa5e5f45c87fbeb7d847aff52320.html</anchorfile>
      <anchor>a7c4efa5e5f45c87fbeb7d847aff52320</anchor>
      <arglist>(V const &amp;v) const</arglist>
    </member>
    <member kind="function">
      <type>as_logical_t&lt; T &gt;</type>
      <name>mask</name>
      <anchorfile>structeve_1_1ignore__last.html</anchorfile>
      <anchor>a3797eecaf2bd6f1cf71c529b6af68800</anchor>
      <arglist>(eve::as&lt; T &gt; tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr std::ptrdiff_t</type>
      <name>count</name>
      <anchorfile>structeve_1_1ignore__last.html</anchorfile>
      <anchor>ac36cc803a7975fe2b567f2aa58ac1425</anchor>
      <arglist>(eve::as&lt; T &gt; tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool friend</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1ignore__last.html</anchorfile>
      <anchor>aab86f28ea5ad50e938519d062c9f480f</anchor>
      <arglist>(ignore_last const &amp;, ignore_last const &amp;)=default</arglist>
    </member>
    <member kind="friend">
      <type>friend auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1ignore__last.html</anchorfile>
      <anchor>a3d4378ec6f99c9615c489cb55bc38ad0</anchor>
      <arglist>(std::basic_ostream&lt; Ch, Ct &gt; &amp;os, ignore_last const &amp;c)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::ignore_none_</name>
    <filename>structeve_1_1ignore__none__.html</filename>
    <member kind="function">
      <type>constexpr auto</type>
      <name>else_</name>
      <anchorfile>structeve_1_1ignore__none___a63d3b649f9420bcb58faf39ecc2d3e12.html</anchorfile>
      <anchor>a63d3b649f9420bcb58faf39ecc2d3e12</anchor>
      <arglist>(V v) const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>mask</name>
      <anchorfile>structeve_1_1ignore__none__.html</anchorfile>
      <anchor>a718bc9661c0078283786c86bff3be09c</anchor>
      <arglist>(eve::as&lt; T &gt; const &amp;tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr std::ptrdiff_t</type>
      <name>count</name>
      <anchorfile>structeve_1_1ignore__none__.html</anchorfile>
      <anchor>a99a2a205e7bf21a00fdac8be29cb815c</anchor>
      <arglist>(eve::as&lt; T &gt; const &amp;) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool friend</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1ignore__none__.html</anchorfile>
      <anchor>a8f7d4de78943e1a0a0e27c1c9a7d1cf0</anchor>
      <arglist>(ignore_none_ const &amp;, ignore_none_ const &amp;)=default</arglist>
    </member>
    <member kind="friend">
      <type>friend auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1ignore__none__.html</anchorfile>
      <anchor>a982750352d08981b01095929fcaa731b</anchor>
      <arglist>(std::basic_ostream&lt; Ch, Ct &gt; &amp;os, ignore_none_ const &amp;)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::algo::views::iota_with_step_iterator</name>
    <filename>structeve_1_1algo_1_1views_1_1iota__with__step__iterator.html</filename>
    <templarg>typename T</templarg>
    <templarg>typename N</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::views::iota_with_step_iterator</name>
    <filename>structeve_1_1views_1_1iota__with__step__iterator.html</filename>
    <templarg>typename T</templarg>
    <templarg>typename N</templarg>
  </compound>
  <compound kind="struct">
    <name>iota_with_step_iterator</name>
    <filename>structiota__with__step__iterator.html</filename>
  </compound>
  <compound kind="struct">
    <name>eve::keep_between</name>
    <filename>structeve_1_1keep__between.html</filename>
    <member kind="function">
      <type>constexpr auto</type>
      <name>else_</name>
      <anchorfile>structeve_1_1keep__between_aca92a195f802ba9cefc4ce60fd9d2ddb.html</anchorfile>
      <anchor>aca92a195f802ba9cefc4ce60fd9d2ddb</anchor>
      <arglist>(V const &amp;v) const</arglist>
    </member>
    <member kind="function">
      <type>as_logical_t&lt; T &gt;</type>
      <name>mask</name>
      <anchorfile>structeve_1_1keep__between.html</anchorfile>
      <anchor>acb2f05a69821cb3d669f0c6e23acdd03</anchor>
      <arglist>(eve::as&lt; T &gt; tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr std::ptrdiff_t</type>
      <name>count</name>
      <anchorfile>structeve_1_1keep__between.html</anchorfile>
      <anchor>a3adf73bac142fb116e37faa66e137174</anchor>
      <arglist>(eve::as&lt; T &gt; tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool friend</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1keep__between.html</anchorfile>
      <anchor>aacc6095fbf602b77019e59007a1c20f7</anchor>
      <arglist>(keep_between const &amp;, keep_between const &amp;)=default</arglist>
    </member>
    <member kind="friend">
      <type>friend auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1keep__between.html</anchorfile>
      <anchor>a969ce653cae900edc1c8345d49eec8ac</anchor>
      <arglist>(std::basic_ostream&lt; Ch, Ct &gt; &amp;os, keep_between const &amp;c)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::keep_first</name>
    <filename>structeve_1_1keep__first.html</filename>
    <member kind="function">
      <type>constexpr</type>
      <name>keep_first</name>
      <anchorfile>structeve_1_1keep__first.html</anchorfile>
      <anchor>a3980975e38c2675ec2f812a4ff3eb7c4</anchor>
      <arglist>(std::ptrdiff_t n) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>else_</name>
      <anchorfile>structeve_1_1keep__first_adfc18e7185cded28f8af09cee992834a.html</anchorfile>
      <anchor>adfc18e7185cded28f8af09cee992834a</anchor>
      <arglist>(V const &amp;v) const</arglist>
    </member>
    <member kind="function">
      <type>as_logical_t&lt; T &gt;</type>
      <name>mask</name>
      <anchorfile>structeve_1_1keep__first.html</anchorfile>
      <anchor>ad61395f1b8bbd57f5433306522d319d0</anchor>
      <arglist>(eve::as&lt; T &gt; tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr std::ptrdiff_t</type>
      <name>count</name>
      <anchorfile>structeve_1_1keep__first.html</anchorfile>
      <anchor>a38300edfb5bd22ae9cc39d9c2738a645</anchor>
      <arglist>(eve::as&lt; T &gt; tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool friend</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1keep__first.html</anchorfile>
      <anchor>a5d8679fe7d0f789184dd908d2f098c9c</anchor>
      <arglist>(keep_first const &amp;, keep_first const &amp;)=default</arglist>
    </member>
    <member kind="friend">
      <type>friend auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1keep__first.html</anchorfile>
      <anchor>a4d7458cca74515e4547b7b126f909d60</anchor>
      <arglist>(std::basic_ostream&lt; Ch, Ct &gt; &amp;os, keep_first const &amp;c)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::keep_last</name>
    <filename>structeve_1_1keep__last.html</filename>
    <member kind="function">
      <type>constexpr auto</type>
      <name>else_</name>
      <anchorfile>structeve_1_1keep__last_a4b92f71c5570ec96efdc6d5d21353961.html</anchorfile>
      <anchor>a4b92f71c5570ec96efdc6d5d21353961</anchor>
      <arglist>(V const &amp;v) const</arglist>
    </member>
    <member kind="function">
      <type>as_logical_t&lt; T &gt;</type>
      <name>mask</name>
      <anchorfile>structeve_1_1keep__last.html</anchorfile>
      <anchor>a05218c5a2645312a4e8d04bd2c7395a1</anchor>
      <arglist>(eve::as&lt; T &gt; tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr std::ptrdiff_t</type>
      <name>count</name>
      <anchorfile>structeve_1_1keep__last.html</anchorfile>
      <anchor>ac80abc105aeb0539f6db682627b0a73e</anchor>
      <arglist>(eve::as&lt; T &gt; tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool friend</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1keep__last.html</anchorfile>
      <anchor>a64e620d72dadf1a643ef816c8ec69332</anchor>
      <arglist>(keep_last const &amp;, keep_last const &amp;)=default</arglist>
    </member>
    <member kind="friend">
      <type>friend auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1keep__last.html</anchorfile>
      <anchor>ab8c37d74daa7658e544a849cb919632f</anchor>
      <arglist>(std::basic_ostream&lt; Ch, Ct &gt; &amp;os, keep_last const &amp;c)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::logical&lt; T &gt;</name>
    <filename>structeve_1_1logical_3_01T_01_4.html</filename>
    <templarg>plain_scalar_value T</templarg>
    <member kind="typedef">
      <type>logical&lt; translate_t&lt; T &gt; &gt;</type>
      <name>translated_type</name>
      <anchorfile>structeve_1_1logical_3_01T_01_4.html</anchorfile>
      <anchor>a10f3da5f5e37929c571303df3fe2933a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>structeve_1_1logical_3_01T_01_4.html</anchorfile>
      <anchor>a4ca253e53d508bd86a04e37251298986</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T</type>
      <name>mask_type</name>
      <anchorfile>structeve_1_1logical_3_01T_01_4.html</anchorfile>
      <anchor>a7f0eebc0478c6f0faf7c0ec92c634609</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>as_integer_t&lt; translate_t&lt; T &gt;, unsigned &gt;</type>
      <name>bits_type</name>
      <anchorfile>structeve_1_1logical_3_01T_01_4.html</anchorfile>
      <anchor>a565e06755bae0876326ea16ffb68abc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01T_01_4.html</anchorfile>
      <anchor>a83188ebd25932c504e2e289b63e223b4</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01T_01_4.html</anchorfile>
      <anchor>ab884507910d1e31e78f65996e28384ca</anchor>
      <arglist>(bool v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01T_01_4.html</anchorfile>
      <anchor>ab653908c20a7064c7aee017040fc596c</anchor>
      <arglist>(U const &amp;v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr logical &amp;</type>
      <name>operator=</name>
      <anchorfile>structeve_1_1logical_3_01T_01_4.html</anchorfile>
      <anchor>a4ed137c0e48ce71166e973abce3f80dd</anchor>
      <arglist>(bool v) &amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01T_01_4.html</anchorfile>
      <anchor>a83188ebd25932c504e2e289b63e223b4</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01T_01_4.html</anchorfile>
      <anchor>ab884507910d1e31e78f65996e28384ca</anchor>
      <arglist>(bool v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01T_01_4.html</anchorfile>
      <anchor>ab653908c20a7064c7aee017040fc596c</anchor>
      <arglist>(U const &amp;v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr logical &amp;</type>
      <name>operator=</name>
      <anchorfile>structeve_1_1logical_3_01T_01_4.html</anchorfile>
      <anchor>a4ed137c0e48ce71166e973abce3f80dd</anchor>
      <arglist>(bool v) &amp;noexcept</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::logical&lt; wide&lt; Type, Cardinal &gt; &gt;</name>
    <filename>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</filename>
    <templarg>arithmetic_scalar_value Type</templarg>
    <templarg>typename Cardinal</templarg>
    <base>eve::_::wide_storage&lt; as_logical_register_t&lt; translate_t&lt; Type &gt;, Cardinal, abi_t&lt; translate_t&lt; Type &gt;, Cardinal &gt; &gt; &gt;</base>
    <member kind="typedef">
      <type>logical&lt; translate_t&lt; Type &gt; &gt;</type>
      <name>translated_element_type</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>af762237b37ee7ef715219473e509a84d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>logical&lt; typename wide&lt; Type, Cardinal &gt;::translated_type &gt;</type>
      <name>translated_type</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a815b515edafa5a1fd54dfa58284cc2b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>logical&lt; Type &gt;</type>
      <name>value_type</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a949b3a102b27d4c7a290ea89caf45e12</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>abi_t&lt; translated_element_type, Cardinal &gt;</type>
      <name>abi_type</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a0d9bc318a83f4b89872d44cf4371e66a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename storage_base::storage_type</type>
      <name>storage_type</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ac94c47f8d965d821d503a0a41818fde8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Cardinal</type>
      <name>cardinal_type</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a1c043e9a2264e6257e715022ffbbe9a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::ptrdiff_t</type>
      <name>size_type</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ad6cf7dc0caa30cc3860f331f683f6c10</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>wide&lt; _::make_integer_t&lt; sizeof(translated_element_type), unsigned &gt;, Cardinal &gt;</type>
      <name>bits_type</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a47cfdf76d5854ca2f0d4257ebdb333c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>wide&lt; Type, Cardinal &gt;</type>
      <name>mask_type</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a552251c1f51965f56d96414cc8f933c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>logical&lt; wide&lt; Type, typename Cardinal::combined_type &gt; &gt;</type>
      <name>combined_type</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ae260f1484d40666e5196dbddc10b2ec1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>logical&lt; wide&lt; T, N &gt; &gt;</type>
      <name>rebind</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a25b557f84e25bb1b30bb67a686d80e84</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>logical&lt; wide&lt; Type, N &gt; &gt;</type>
      <name>rescale</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a0a505c7c261060febd032a868d28af92</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bits_type</type>
      <name>bits</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a127ae630365d174c7d5f8f3332de79dc</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>mask_type</type>
      <name>mask</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a6327cd272b2b30fb1841e218c06a332d</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>bitmap</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a53088b65fa4bba929183f9c4d5792dea</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>storage_type const &amp;</type>
      <name>storage</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>ae243fa6aac6a91ab5981865b306bce5d</anchor>
      <arglist>() const &amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type>storage_type &amp;</type>
      <name>storage</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a6e5b57453be18b7ab65c76db1f3a69e1</anchor>
      <arglist>() &amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type>storage_type</type>
      <name>storage</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a41a9064f838f216eb9f0c2e41e13a1df</anchor>
      <arglist>() &amp;&amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator storage_type const &amp;</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a9c3e7c0e98b4e52924e117c51030cbc1</anchor>
      <arglist>() const &amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator storage_type &amp;</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a1fc129d7b9dd250be0d466b3450cc815</anchor>
      <arglist>() &amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator storage_type</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a24c364353e6976cead7dcecebdfa788e</anchor>
      <arglist>() &amp;&amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ab42e96c04ba7d545273a8411e2172411</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a19f9305f2be6c493a6e86c236fcf4f9e</anchor>
      <arglist>(storage_type const &amp;r) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>abed0447593ed96d503e1b0ca6eac54fb</anchor>
      <arglist>(Range &amp;&amp;r) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ab463edf2bbe092c328f8dc599e49ce8f</anchor>
      <arglist>(Ptr ptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ab463edf2bbe092c328f8dc599e49ce8f</anchor>
      <arglist>(Ptr ptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ae122bd7fa34698be443c7b6e4482f984</anchor>
      <arglist>(logical&lt; U &gt; v) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a32b6d03c03af2e64979367f6d68d7016</anchor>
      <arglist>(std::same_as&lt; bool &gt; auto v) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a3a83d0ff7cbb1ed2e9fc62dec58f7aaa</anchor>
      <arglist>(T0 const &amp;v0, T1 const &amp;v1, Ts const &amp;... vs) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4_a84ea3b085a785e085cbb9a9ffba1c4a4.html</anchorfile>
      <anchor>a84ea3b085a785e085cbb9a9ffba1c4a4</anchor>
      <arglist>(Generator &amp;&amp;g) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4_a84ea3b085a785e085cbb9a9ffba1c4a4.html</anchorfile>
      <anchor>a84ea3b085a785e085cbb9a9ffba1c4a4</anchor>
      <arglist>(Generator &amp;&amp;g) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a767f16dc3944e89d8047d55cb73ea20d</anchor>
      <arglist>(WL0 wl0, WL1 wl1, WLs... wls) noexcept</arglist>
    </member>
    <member kind="function">
      <type>logical &amp;</type>
      <name>operator=</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a21ab888a7a1c9d785657e01d74e12540</anchor>
      <arglist>(logical&lt; Type &gt; v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>logical &amp;</type>
      <name>operator=</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a83aa966901ef9fa80aaf45518c57b1f7</anchor>
      <arglist>(bool v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>logical &amp;</type>
      <name>operator=</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a64946da0cd3477cab6fb2c5132b7fc22</anchor>
      <arglist>(storage_type const &amp;r)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ae56f9b89b700d9668b761c6d5a3167b4</anchor>
      <arglist>(logical &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>af0263a92fa0c41d2252b3a7595695fa7</anchor>
      <arglist>(std::size_t i, std::convertible_to&lt; bool &gt; auto v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>get</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a7e669e8b662996c0cb3553c33a09dedc</anchor>
      <arglist>(std::size_t i) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>back</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a43db7ec7fb3a32fe5b649f4e8a85ab95</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>front</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a7de72be98e577d883e5d4e13487bcb20</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>slice</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4_aa9cd862159f14c1959ab479dc243a310.html</anchorfile>
      <anchor>aa9cd862159f14c1959ab479dc243a310</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>slice</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4_a71e274784f66b6d8f845129e580ae02a.html</anchorfile>
      <anchor>a71e274784f66b6d8f845129e580ae02a</anchor>
      <arglist>(slice_t&lt; Slice &gt; s) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr auto</type>
      <name>alignment</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a618532fc6332155edaf4aca72b5b93aa</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr size_type</type>
      <name>size</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ad4d0897d94f1786e153dcd05ab059be5</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr size_type</type>
      <name>max_size</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a626f66c1c0e65886dda45ba50cac4439</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr bool</type>
      <name>empty</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>abbbe1a87460349d94895917816d5577a</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend common_logical_t&lt; logical, logical&lt; wide&lt; U, Cardinal &gt; &gt; &gt;</type>
      <name>operator&amp;&amp;</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a96233062a69c6e1eefe7c3ad03332165</anchor>
      <arglist>(logical const &amp;a, logical&lt; wide&lt; U, Cardinal &gt; &gt; const &amp;b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend common_logical_t&lt; logical, S &gt;</type>
      <name>operator&amp;&amp;</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a9e795a28664e04873c84933c24412dd3</anchor>
      <arglist>(logical const &amp;w, S s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend common_logical_t&lt; S, logical &gt;</type>
      <name>operator&amp;&amp;</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>aa97147cd59c2f7695c4b5155ba461791</anchor>
      <arglist>(S s, logical const &amp;w) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend common_logical_t&lt; logical, logical&lt; wide&lt; U, Cardinal &gt; &gt; &gt;</type>
      <name>operator||</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a1012cb5c0551a192d0d9890b850ed212</anchor>
      <arglist>(logical const &amp;a, logical&lt; wide&lt; U, Cardinal &gt; &gt; const &amp;b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend common_logical_t&lt; logical, S &gt;</type>
      <name>operator||</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ab5b6c22941f4d42421943daee8f3e7f1</anchor>
      <arglist>(logical const &amp;w, S s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend common_logical_t&lt; S, logical &gt;</type>
      <name>operator||</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>acb3f345b5c49092876e239870521eb37</anchor>
      <arglist>(S s, logical const &amp;w) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator!</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a1bdaef9f0529757040060f464139e90f</anchor>
      <arglist>(logical const &amp;v) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend void</type>
      <name>swap</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a7cec0220f0393e97f10e78ea89c112a0</anchor>
      <arglist>(logical &amp;lhs, logical &amp;rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>afccc614d090f5ed1046fb73afa650494</anchor>
      <arglist>(logical w, S s) noexcept -&gt; decltype(is_equal(w, s))</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator!=</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>af9781f0446ba35ad5bd552cc4a27410e</anchor>
      <arglist>(logical w, S s) noexcept -&gt; decltype(is_not_equal(w, s))</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator!=</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>afe4168d85e4249d0e5b0857f86c3674a</anchor>
      <arglist>(S s, logical w) noexcept -&gt; decltype(is_not_equal(w, s))</arglist>
    </member>
    <member kind="friend">
      <type>friend auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a28c1bda76458566e049f1c9dd20463a6</anchor>
      <arglist>(std::basic_ostream&lt; C, Ct &gt; &amp;os, logical const &amp;p)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr size_type</type>
      <name>size</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ad4d0897d94f1786e153dcd05ab059be5</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr size_type</type>
      <name>max_size</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a626f66c1c0e65886dda45ba50cac4439</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr bool</type>
      <name>empty</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>abbbe1a87460349d94895917816d5577a</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ab42e96c04ba7d545273a8411e2172411</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a19f9305f2be6c493a6e86c236fcf4f9e</anchor>
      <arglist>(storage_type const &amp;r) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>abed0447593ed96d503e1b0ca6eac54fb</anchor>
      <arglist>(Range &amp;&amp;r) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ab463edf2bbe092c328f8dc599e49ce8f</anchor>
      <arglist>(Ptr ptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ab463edf2bbe092c328f8dc599e49ce8f</anchor>
      <arglist>(Ptr ptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ae122bd7fa34698be443c7b6e4482f984</anchor>
      <arglist>(logical&lt; U &gt; v) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a32b6d03c03af2e64979367f6d68d7016</anchor>
      <arglist>(std::same_as&lt; bool &gt; auto v) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a3a83d0ff7cbb1ed2e9fc62dec58f7aaa</anchor>
      <arglist>(T0 const &amp;v0, T1 const &amp;v1, Ts const &amp;... vs) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4_a84ea3b085a785e085cbb9a9ffba1c4a4.html</anchorfile>
      <anchor>a84ea3b085a785e085cbb9a9ffba1c4a4</anchor>
      <arglist>(Generator &amp;&amp;g) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4_a84ea3b085a785e085cbb9a9ffba1c4a4.html</anchorfile>
      <anchor>a84ea3b085a785e085cbb9a9ffba1c4a4</anchor>
      <arglist>(Generator &amp;&amp;g) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>logical</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a767f16dc3944e89d8047d55cb73ea20d</anchor>
      <arglist>(WL0 wl0, WL1 wl1, WLs... wls) noexcept</arglist>
    </member>
    <member kind="function">
      <type>logical &amp;</type>
      <name>operator=</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a21ab888a7a1c9d785657e01d74e12540</anchor>
      <arglist>(logical&lt; Type &gt; v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>logical &amp;</type>
      <name>operator=</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a83aa966901ef9fa80aaf45518c57b1f7</anchor>
      <arglist>(bool v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>logical &amp;</type>
      <name>operator=</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a64946da0cd3477cab6fb2c5132b7fc22</anchor>
      <arglist>(storage_type const &amp;r)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>ae56f9b89b700d9668b761c6d5a3167b4</anchor>
      <arglist>(logical &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>af0263a92fa0c41d2252b3a7595695fa7</anchor>
      <arglist>(std::size_t i, std::convertible_to&lt; bool &gt; auto v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>get</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a7e669e8b662996c0cb3553c33a09dedc</anchor>
      <arglist>(std::size_t i) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>back</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a43db7ec7fb3a32fe5b649f4e8a85ab95</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>front</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4.html</anchorfile>
      <anchor>a7de72be98e577d883e5d4e13487bcb20</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>slice</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4_aa9cd862159f14c1959ab479dc243a310.html</anchorfile>
      <anchor>aa9cd862159f14c1959ab479dc243a310</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>slice</name>
      <anchorfile>structeve_1_1logical_3_01wide_3_01Type_00_01Cardinal_01_4_01_4_a71e274784f66b6d8f845129e580ae02a.html</anchorfile>
      <anchor>a71e274784f66b6d8f845129e580ae02a</anchor>
      <arglist>(slice_t&lt; Slice &gt; s) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::algo::views::map_iterator</name>
    <filename>structeve_1_1algo_1_1views_1_1map__iterator.html</filename>
    <templarg>relaxed_iterator I</templarg>
    <templarg>map_load_op&lt; I &gt; LoadOp</templarg>
    <templarg>map_store_op&lt; LoadOp, I &gt; StoreOp</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::views::map_iterator</name>
    <filename>structeve_1_1views_1_1map__iterator.html</filename>
    <templarg>relaxed_iterator I</templarg>
    <templarg>map_load_op&lt; I &gt; LoadOp</templarg>
    <templarg>map_store_op&lt; LoadOp, I &gt; StoreOp</templarg>
  </compound>
  <compound kind="struct">
    <name>map_load_op</name>
    <filename>structmap__load__op.html</filename>
  </compound>
  <compound kind="struct">
    <name>eve::algo::views::map_range</name>
    <filename>structeve_1_1algo_1_1views_1_1map__range.html</filename>
    <templarg>non_owning_range R</templarg>
    <templarg>map_load_op&lt; R &gt; LoadOp</templarg>
    <templarg>map_store_op&lt; LoadOp, R &gt; StoreOp</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::views::map_range</name>
    <filename>structeve_1_1views_1_1map__range.html</filename>
    <templarg>non_owning_range R</templarg>
    <templarg>map_load_op&lt; R &gt; LoadOp</templarg>
    <templarg>map_store_op&lt; LoadOp, R &gt; StoreOp</templarg>
  </compound>
  <compound kind="struct">
    <name>map_store_op</name>
    <filename>structmap__store__op.html</filename>
  </compound>
  <compound kind="struct">
    <name>eve::algo::nothing_t</name>
    <filename>structeve_1_1algo_1_1nothing__t.html</filename>
  </compound>
  <compound kind="struct">
    <name>eve::options</name>
    <filename>structeve_1_1options.html</filename>
    <templarg>rbr::concepts::settings Settings</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::or_</name>
    <filename>structeve_1_1or__.html</filename>
    <templarg>typename C</templarg>
    <templarg>typename V</templarg>
    <member kind="typedef">
      <type>V</type>
      <name>alternative_type</name>
      <anchorfile>structeve_1_1or__.html</anchorfile>
      <anchor>a1ef2b85f1416669f6fdf95cdfe0c9eee</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>C</type>
      <name>conditional_type</name>
      <anchorfile>structeve_1_1or__.html</anchorfile>
      <anchor>a49644873ed4ff5dbd8db654547ca8643</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>or_</name>
      <anchorfile>structeve_1_1or__.html</anchorfile>
      <anchor>a1ad60d150ff3c184df1c6b99bedfde73</anchor>
      <arglist>(C const &amp;c, V const &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>constexpr C</type>
      <name>base</name>
      <anchorfile>structeve_1_1or__.html</anchorfile>
      <anchor>aa7164869090edd22bd724f4c2ef3f8a5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>rebase</name>
      <anchorfile>structeve_1_1or__.html</anchorfile>
      <anchor>a2646ba4aeead4382e1a22f58755b7257</anchor>
      <arglist>(T v) const</arglist>
    </member>
    <member kind="variable">
      <type>V</type>
      <name>alternative</name>
      <anchorfile>structeve_1_1or__.html</anchorfile>
      <anchor>a5cbd63c0f9840117116c1bbfc5d3d5eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1or__.html</anchorfile>
      <anchor>a511de3db80722d15102c9a744abe42e3</anchor>
      <arglist>(std::basic_ostream&lt; Ch, Ct &gt; &amp;os, or_ const &amp;c)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>or_</name>
    <filename>structor__.html</filename>
    <templarg>typename C</templarg>
    <templarg>typename V</templarg>
    <member kind="typedef">
      <type>V</type>
      <name>alternative_type</name>
      <anchorfile>structor__.html</anchorfile>
      <anchor>a1ef2b85f1416669f6fdf95cdfe0c9eee</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>C</type>
      <name>conditional_type</name>
      <anchorfile>structor__.html</anchorfile>
      <anchor>a49644873ed4ff5dbd8db654547ca8643</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>or_</name>
      <anchorfile>structor__.html</anchorfile>
      <anchor>a1ad60d150ff3c184df1c6b99bedfde73</anchor>
      <arglist>(C const &amp;c, V const &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>constexpr C</type>
      <name>base</name>
      <anchorfile>structor__.html</anchorfile>
      <anchor>aa7164869090edd22bd724f4c2ef3f8a5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>rebase</name>
      <anchorfile>structor__.html</anchorfile>
      <anchor>a2646ba4aeead4382e1a22f58755b7257</anchor>
      <arglist>(T v) const</arglist>
    </member>
    <member kind="variable">
      <type>V</type>
      <name>alternative</name>
      <anchorfile>structor__.html</anchorfile>
      <anchor>a5cbd63c0f9840117116c1bbfc5d3d5eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structor__.html</anchorfile>
      <anchor>a511de3db80722d15102c9a744abe42e3</anchor>
      <arglist>(std::basic_ostream&lt; Ch, Ct &gt; &amp;os, or_ const &amp;c)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::pattern_t</name>
    <filename>structeve_1_1pattern__t.html</filename>
    <templarg>std::ptrdiff_t... I</templarg>
    <member kind="function">
      <type>constexpr std::ptrdiff_t</type>
      <name>operator()</name>
      <anchorfile>structeve_1_1pattern__t.html</anchorfile>
      <anchor>a3548551170354714cada3dea156fceb2</anchor>
      <arglist>(std::ptrdiff_t i, int) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>strictly_over</name>
      <anchorfile>structeve_1_1pattern__t.html</anchorfile>
      <anchor>ad9a31d4204779fdda7cebd0c4322b94d</anchor>
      <arglist>(std::ptrdiff_t n) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>strictly_under</name>
      <anchorfile>structeve_1_1pattern__t.html</anchorfile>
      <anchor>a1272523c834659df8e28caa48d05c0bc</anchor>
      <arglist>(std::ptrdiff_t n) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>over</name>
      <anchorfile>structeve_1_1pattern__t.html</anchorfile>
      <anchor>a7237b50974aed5cd0107f53541ba5ff7</anchor>
      <arglist>(std::ptrdiff_t n) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>under</name>
      <anchorfile>structeve_1_1pattern__t.html</anchorfile>
      <anchor>aef70581b6e3b30db25467efcc08eff1c</anchor>
      <arglist>(std::ptrdiff_t n) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1pattern__t.html</anchorfile>
      <anchor>a0ac89ed3eaeb3470974d0789f53ac116</anchor>
      <arglist>(pattern_t&lt; J... &gt;) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>operator!=</name>
      <anchorfile>structeve_1_1pattern__t.html</anchorfile>
      <anchor>a490329fb584803b715c1a5b3cd843e35</anchor>
      <arglist>(pattern_t&lt; J... &gt;) const noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr std::ptrdiff_t</type>
      <name>size</name>
      <anchorfile>structeve_1_1pattern__t.html</anchorfile>
      <anchor>a7690a2263dcf6673bfd80b48caedefa3</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr bool</type>
      <name>has_zeros</name>
      <anchorfile>structeve_1_1pattern__t.html</anchorfile>
      <anchor>adaf1e7da40b7b86a9e00d120044039df</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr bool</type>
      <name>validate</name>
      <anchorfile>structeve_1_1pattern__t.html</anchorfile>
      <anchor>a828fefe9303d5cfdd45a1bdd67bf0b80</anchor>
      <arglist>(std::ptrdiff_t N) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1pattern__t.html</anchorfile>
      <anchor>ad79eddbbd6c04c0404edfb64c6a76900</anchor>
      <arglist>(std::basic_ostream&lt; Ch, Ct &gt; &amp;os, pattern_t const &amp;)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>fix_pattern</name>
      <anchorfile>structeve_1_1pattern__t.html</anchorfile>
      <anchor>abfc27bc9e535aab6f92c30fc1f7ec756</anchor>
      <arglist>(F)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>pattern_clamp</name>
      <anchorfile>structeve_1_1pattern__t.html</anchorfile>
      <anchor>aac580eb9f0d080a624c6daff238715ef</anchor>
      <arglist>(Pattern const &amp;) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>pattern_view</name>
      <anchorfile>structeve_1_1pattern__t_aba2457c37b6001a44f3c682466fd4e36.html</anchorfile>
      <anchor>aba2457c37b6001a44f3c682466fd4e36</anchor>
      <arglist>(Pattern const &amp;) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>slide_pattern</name>
      <anchorfile>structeve_1_1pattern__t_ad209f6cc99dbfc1a50994908c70159d5.html</anchorfile>
      <anchor>ad209f6cc99dbfc1a50994908c70159d5</anchor>
      <arglist>(Pattern) noexcept</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::platform</name>
    <filename>structeve_1_1platform.html</filename>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>supports_nans</name>
      <anchorfile>structeve_1_1platform.html</anchorfile>
      <anchor>a9d25ead24e42a5f986a811c5a80e673f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>supports_infinites</name>
      <anchorfile>structeve_1_1platform.html</anchorfile>
      <anchor>a00079508a76ddc26da6a37103736efe1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>supports_invalids</name>
      <anchorfile>structeve_1_1platform.html</anchorfile>
      <anchor>aa68340aa769d90df23eac41ccace3202</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>supports_negative_zero</name>
      <anchorfile>structeve_1_1platform.html</anchorfile>
      <anchor>a4a992b4e125de11d8ab63fe5efe67d09</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>supports_denormals</name>
      <anchorfile>structeve_1_1platform.html</anchorfile>
      <anchor>af3360ddd7198824495702e6af43c32b1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::algo::ptr_iterator</name>
    <filename>structeve_1_1algo_1_1ptr__iterator.html</filename>
    <templarg>typename Ptr</templarg>
    <templarg>typename Cardinal</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::algo::range_ref_wrapper</name>
    <filename>structeve_1_1algo_1_1range__ref__wrapper.html</filename>
    <templarg>relaxed_range Rng</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::aligned_allocator::rebind</name>
    <filename>structeve_1_1aligned__allocator_1_1rebind.html</filename>
    <templarg>typename U</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::relative_conditional_option</name>
    <filename>structeve_1_1relative__conditional__option.html</filename>
    <member kind="function">
      <type>constexpr auto</type>
      <name>default_to</name>
      <anchorfile>structeve_1_1relative__conditional__option.html</anchorfile>
      <anchor>ac6970f8101a6b9e3fc67dc4f6c500d61</anchor>
      <arglist>(auto const &amp;base) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>relaxed_iterator</name>
    <filename>structrelaxed__iterator.html</filename>
  </compound>
  <compound kind="struct">
    <name>relaxed_range</name>
    <filename>structrelaxed__range.html</filename>
  </compound>
  <compound kind="struct">
    <name>relaxed_sentinel_for</name>
    <filename>structrelaxed__sentinel__for.html</filename>
  </compound>
  <compound kind="struct">
    <name>eve::algo::views::reverse_iterator</name>
    <filename>structeve_1_1algo_1_1views_1_1reverse__iterator.html</filename>
    <templarg>relaxed_iterator I</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::views::reverse_iterator</name>
    <filename>structeve_1_1views_1_1reverse__iterator.html</filename>
    <templarg>relaxed_iterator I</templarg>
  </compound>
  <compound kind="struct">
    <name>reverse_iterator</name>
    <filename>structreverse__iterator.html</filename>
  </compound>
  <compound kind="struct">
    <name>eve::algo::views::reverse_range</name>
    <filename>structeve_1_1algo_1_1views_1_1reverse__range.html</filename>
    <templarg>non_owning_range R</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::views::reverse_range</name>
    <filename>structeve_1_1views_1_1reverse__range.html</filename>
    <templarg>non_owning_range R</templarg>
  </compound>
  <compound kind="struct">
    <name>reverse_range</name>
    <filename>structreverse__range.html</filename>
  </compound>
  <compound kind="struct">
    <name>eve::soa_ptr</name>
    <filename>structeve_1_1soa__ptr.html</filename>
    <templarg>typename ... Ptrs</templarg>
  </compound>
  <compound kind="class">
    <name>eve::algo::soa_vector</name>
    <filename>structeve_1_1algo_1_1soa__vector.html</filename>
    <templarg>eve::product_type Type</templarg>
    <templarg>eve::simd_allocator Allocator</templarg>
    <member kind="typedef">
      <type>Type</type>
      <name>value_type</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>afa565773f9b92a3d9e6352686dd0caec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>decltype(views::convert(storage_type{}.data(), as&lt; value_type &gt;{}))</type>
      <name>iterator</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a63371337208b1895b475884645b7aff3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>decltype(views::convert(std::declval&lt; storage_type const  &gt;().data(), as&lt; value_type &gt;{}))</type>
      <name>const_iterator</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a08ca84b8e41391cf3323531322cb0838</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>decltype(views::convert(storage_type{}.data_aligned(), as&lt; value_type &gt;{}))</type>
      <name>iterator_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a1cebd79982e022f940660bf05183ff6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>decltype(views::convert(std::declval&lt; storage_type const  &gt;().data_aligned(), as&lt; value_type &gt;{}))</type>
      <name>const_iterator_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a06409dfeb9c697552b3cbc4bbba13663</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>iterator</type>
      <name>pointer</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a7db1163ad1d400fc98afad5b3715b13f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>const_iterator</type>
      <name>const_pointer</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>aa69ac173d5f52992f17bfa1b3db7cb4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>iterator_aligned</type>
      <name>pointer_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a73d36efe89af3939f2d6bcfaf2d0352a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>const_iterator_aligned</type>
      <name>const_pointer_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a10087850fe16634a56678b967843875d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::size_t</type>
      <name>size_type</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>ad4b822a0023ad3a8cec4bc090c41b381</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a7040f8d97e7f099d22ade6df7f853599</anchor>
      <arglist>(Allocator a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a1cfd01b1cec55dd3fab8e0c6809764f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>aea7e91a0c99b91cf1450c54b02836b3c</anchor>
      <arglist>(size_type n, Allocator a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a371c329f5be284001625d7c6c14de497</anchor>
      <arglist>(size_type n)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a2860518add05d6c27812837fca6af7d4</anchor>
      <arglist>(no_init_t, size_type n, Allocator a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a37a921fa715625233a0498098ea5ab08</anchor>
      <arglist>(no_init_t, size_type n)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>aa588a9a21fc315c6f6ef07142937313e</anchor>
      <arglist>(size_type n, value_type v, Allocator a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a2d3663ed3c3c058cd25621becea1aab2</anchor>
      <arglist>(size_type n, value_type v)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>ac634d1c503afc06588b14ca58eb0804f</anchor>
      <arglist>(std::initializer_list&lt; Type &gt; l, Allocator a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>ac908824a2ad8ed2989190452337b922c</anchor>
      <arglist>(std::initializer_list&lt; Type &gt; l)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>size</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>acfa067cbe1080920388e2637eb920180</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>capacity</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a7a932b76d28707377aea95c7332c62c2</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shrink_to_fit</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a0f0bf415832f111ba79c83e51aad08bc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>empty</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a583e0a2bb360fef57e2fb1cfa856fa45</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reserve</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector_a23a8b5cff720fd36c88f8bcda9cc3cf0.html</anchorfile>
      <anchor>a23a8b5cff720fd36c88f8bcda9cc3cf0</anchor>
      <arglist>(size_type n)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>data_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>afb1302da46f4c4235040f1d6717aac60</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>data_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>af0b6bc0e2bb130e9bfc92c15077eb3ce</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>data</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a4305ff633912d03ecf954338c2683176</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>data</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a41ff6fdeb30e98261d9bafa3ffcbe45b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>get</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector_ab8e96562f8b090a2575e0b5a7116a9ed.html</anchorfile>
      <anchor>ab8e96562f8b090a2575e0b5a7116a9ed</anchor>
      <arglist>(size_type i) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector_a2916bce62a37b27a040f50727df724c9.html</anchorfile>
      <anchor>a2916bce62a37b27a040f50727df724c9</anchor>
      <arglist>(size_type i, value_type const &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fill</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>ab508d79bcf317cfc3a543d0c3dcb26aa</anchor>
      <arglist>(value_type v)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>begin_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>aac9595c0eb4efe379e7f34b6e04c83f9</anchor>
      <arglist>() -&gt; iterator_aligned</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>begin_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>af8f93ff8b4c9bafc2035d86edac299e0</anchor>
      <arglist>() const -&gt; const_iterator_aligned</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>cbegin_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>ade7d1e71b4633182d97230c74781198e</anchor>
      <arglist>() const -&gt; const_iterator_aligned</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>begin</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a02dcc5da444d505275581b32a0b1790d</anchor>
      <arglist>() -&gt; iterator</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>begin</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a146dbca0b714b7ecf2af0c92f57aa442</anchor>
      <arglist>() const -&gt; const_iterator</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>cbegin</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a10024e7a9214a6034b376ad4c8303ed6</anchor>
      <arglist>() const -&gt; const_iterator</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>end</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a7db16dc990e0a9f719cad868584894c3</anchor>
      <arglist>() -&gt; iterator</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>end</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a1a854e147b9532862620b217280a1327</anchor>
      <arglist>() const -&gt; const_iterator</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>cend</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>ad5a09db39e7ae09481c4023345e689ef</anchor>
      <arglist>() const -&gt; const_iterator</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>abb509d075fdd2fd5f5669ad45a09c9e9</anchor>
      <arglist>(soa_vector const &amp;lhs, soa_vector const &amp;rhs)</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator!=</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a706408ace5be95890cfc6c9e0cf22d3a</anchor>
      <arglist>(soa_vector const &amp;lhs, soa_vector const &amp;rhs)</arglist>
    </member>
    <member kind="typedef">
      <type>Type</type>
      <name>value_type</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>afa565773f9b92a3d9e6352686dd0caec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>decltype(views::convert(storage_type{}.data(), as&lt; value_type &gt;{}))</type>
      <name>iterator</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a63371337208b1895b475884645b7aff3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>decltype(views::convert(std::declval&lt; storage_type const  &gt;().data(), as&lt; value_type &gt;{}))</type>
      <name>const_iterator</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a08ca84b8e41391cf3323531322cb0838</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>decltype(views::convert(storage_type{}.data_aligned(), as&lt; value_type &gt;{}))</type>
      <name>iterator_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a1cebd79982e022f940660bf05183ff6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>decltype(views::convert(std::declval&lt; storage_type const  &gt;().data_aligned(), as&lt; value_type &gt;{}))</type>
      <name>const_iterator_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a06409dfeb9c697552b3cbc4bbba13663</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>iterator</type>
      <name>pointer</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a7db1163ad1d400fc98afad5b3715b13f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>const_iterator</type>
      <name>const_pointer</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>aa69ac173d5f52992f17bfa1b3db7cb4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>iterator_aligned</type>
      <name>pointer_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a73d36efe89af3939f2d6bcfaf2d0352a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>const_iterator_aligned</type>
      <name>const_pointer_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a10087850fe16634a56678b967843875d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::size_t</type>
      <name>size_type</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>ad4b822a0023ad3a8cec4bc090c41b381</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a7040f8d97e7f099d22ade6df7f853599</anchor>
      <arglist>(Allocator a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a1cfd01b1cec55dd3fab8e0c6809764f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>aea7e91a0c99b91cf1450c54b02836b3c</anchor>
      <arglist>(size_type n, Allocator a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a371c329f5be284001625d7c6c14de497</anchor>
      <arglist>(size_type n)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a2860518add05d6c27812837fca6af7d4</anchor>
      <arglist>(no_init_t, size_type n, Allocator a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a37a921fa715625233a0498098ea5ab08</anchor>
      <arglist>(no_init_t, size_type n)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>aa588a9a21fc315c6f6ef07142937313e</anchor>
      <arglist>(size_type n, value_type v, Allocator a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a2d3663ed3c3c058cd25621becea1aab2</anchor>
      <arglist>(size_type n, value_type v)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>ac634d1c503afc06588b14ca58eb0804f</anchor>
      <arglist>(std::initializer_list&lt; Type &gt; l, Allocator a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>soa_vector</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>ac908824a2ad8ed2989190452337b922c</anchor>
      <arglist>(std::initializer_list&lt; Type &gt; l)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>size</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>acfa067cbe1080920388e2637eb920180</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>capacity</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a7a932b76d28707377aea95c7332c62c2</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shrink_to_fit</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a0f0bf415832f111ba79c83e51aad08bc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>empty</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a583e0a2bb360fef57e2fb1cfa856fa45</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reserve</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector_a23a8b5cff720fd36c88f8bcda9cc3cf0.html</anchorfile>
      <anchor>a23a8b5cff720fd36c88f8bcda9cc3cf0</anchor>
      <arglist>(size_type n)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a1180e9fef3d348b215819ea7217c8b01</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>erase</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector_a9d1fa950c126da0ea504f3cad11ddd28.html</anchorfile>
      <anchor>a9d1fa950c126da0ea504f3cad11ddd28</anchor>
      <arglist>(const_iterator pos)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>erase</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a01c465399be641d08efe38ca634c55d2</anchor>
      <arglist>(const_iterator f, const_iterator l)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>push_back</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector_a2cb689f3ab9c10b4d9530a04bc9f69b7.html</anchorfile>
      <anchor>a2cb689f3ab9c10b4d9530a04bc9f69b7</anchor>
      <arglist>(value_type const &amp;value) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pop_back</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector_a23cd76edc7e71f4d164a571de326a24a.html</anchorfile>
      <anchor>a23cd76edc7e71f4d164a571de326a24a</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector_a00d09efb7c037e5a1b2393e091e94c91.html</anchorfile>
      <anchor>a00d09efb7c037e5a1b2393e091e94c91</anchor>
      <arglist>(size_type n, value_type value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a454bdf6879ae86443e4df0af94642127</anchor>
      <arglist>(size_type n)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector_ab677ad163c4f357e765d5f685f4a327c.html</anchorfile>
      <anchor>ab677ad163c4f357e765d5f685f4a327c</anchor>
      <arglist>(soa_vector &amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>Allocator</type>
      <name>get_allocator</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a2045227da8d8624b2fc82304f54fe4ce</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend">
      <type>friend void</type>
      <name>swap</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a3deb25a3ff1468a7e4ccd1937a8d049e</anchor>
      <arglist>(soa_vector &amp;lhs, soa_vector &amp;rhs) noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>data_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>afb1302da46f4c4235040f1d6717aac60</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>data_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>af0b6bc0e2bb130e9bfc92c15077eb3ce</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>data</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a4305ff633912d03ecf954338c2683176</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>data</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a41ff6fdeb30e98261d9bafa3ffcbe45b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>get</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector_ab8e96562f8b090a2575e0b5a7116a9ed.html</anchorfile>
      <anchor>ab8e96562f8b090a2575e0b5a7116a9ed</anchor>
      <arglist>(size_type i) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector_a2916bce62a37b27a040f50727df724c9.html</anchorfile>
      <anchor>a2916bce62a37b27a040f50727df724c9</anchor>
      <arglist>(size_type i, value_type const &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fill</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>ab508d79bcf317cfc3a543d0c3dcb26aa</anchor>
      <arglist>(value_type v)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>begin_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>aac9595c0eb4efe379e7f34b6e04c83f9</anchor>
      <arglist>() -&gt; iterator_aligned</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>begin_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>af8f93ff8b4c9bafc2035d86edac299e0</anchor>
      <arglist>() const -&gt; const_iterator_aligned</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>cbegin_aligned</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>ade7d1e71b4633182d97230c74781198e</anchor>
      <arglist>() const -&gt; const_iterator_aligned</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>begin</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a02dcc5da444d505275581b32a0b1790d</anchor>
      <arglist>() -&gt; iterator</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>begin</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a146dbca0b714b7ecf2af0c92f57aa442</anchor>
      <arglist>() const -&gt; const_iterator</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>cbegin</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a10024e7a9214a6034b376ad4c8303ed6</anchor>
      <arglist>() const -&gt; const_iterator</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>end</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a7db16dc990e0a9f719cad868584894c3</anchor>
      <arglist>() -&gt; iterator</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>end</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a1a854e147b9532862620b217280a1327</anchor>
      <arglist>() const -&gt; const_iterator</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>cend</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>ad5a09db39e7ae09481c4023345e689ef</anchor>
      <arglist>() const -&gt; const_iterator</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>abb509d075fdd2fd5f5669ad45a09c9e9</anchor>
      <arglist>(soa_vector const &amp;lhs, soa_vector const &amp;rhs)</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator!=</name>
      <anchorfile>structeve_1_1algo_1_1soa__vector.html</anchorfile>
      <anchor>a706408ace5be95890cfc6c9e0cf22d3a</anchor>
      <arglist>(soa_vector const &amp;lhs, soa_vector const &amp;rhs)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::stack_buffer</name>
    <filename>structeve_1_1stack__buffer.html</filename>
    <templarg>simd_value T</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::struct_support</name>
    <filename>structeve_1_1struct__support.html</filename>
    <templarg>typename Self</templarg>
    <templarg>typename ... Fields</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::supports_like</name>
    <filename>structeve_1_1supports__like.html</filename>
    <templarg>typename Wrapper</templarg>
    <templarg>typename Self</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::supports_ordering</name>
    <filename>structeve_1_1supports__ordering.html</filename>
    <templarg>typename Type</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::top_bits</name>
    <filename>structeve_1_1top__bits.html</filename>
    <templarg>logical_simd_value Logical</templarg>
    <member kind="typedef">
      <type>Logical</type>
      <name>logical_type</name>
      <anchorfile>structeve_1_1top__bits.html</anchorfile>
      <anchor>aafee0984a0b3eb86ecf40b8621ddac68</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename as_arithmetic_t&lt; logical_type &gt;::value_type</type>
      <name>scalar_type</name>
      <anchorfile>structeve_1_1top__bits.html</anchorfile>
      <anchor>a46b500a7f5599d078b9c1069f400aa56</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename as_arithmetic_t&lt; logical_type &gt;::abi_type</type>
      <name>abi_type</name>
      <anchorfile>structeve_1_1top__bits.html</anchorfile>
      <anchor>a26911fff000600654309cd3f1587d37f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>logical&lt; wide&lt; scalar_type, eve::fixed&lt; half_size &gt; &gt; &gt;</type>
      <name>half_logical</name>
      <anchorfile>structeve_1_1top__bits.html</anchorfile>
      <anchor>a448b36c0f435bda8170fabbe183de7be</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>decltype(top_bits::storage_type_impl())</type>
      <name>storage_type</name>
      <anchorfile>structeve_1_1top__bits.html</anchorfile>
      <anchor>a9710f1c9c44fda47778a072781e5105a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr void</type>
      <name>set</name>
      <anchorfile>structeve_1_1top__bits.html</anchorfile>
      <anchor>a70e3fa2976c2eca5099140554fb24920</anchor>
      <arglist>(std::ptrdiff_t i, bool x)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr std::ptrdiff_t</type>
      <name>static_size</name>
      <anchorfile>structeve_1_1top__bits.html</anchorfile>
      <anchor>a830692d29a4c59c9d27b3a3fa7ae50ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>is_aggregated</name>
      <anchorfile>structeve_1_1top__bits.html</anchorfile>
      <anchor>a5154a768fbc421af8a5301e9096c7350</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr std::ptrdiff_t</type>
      <name>bits_per_element</name>
      <anchorfile>structeve_1_1top__bits.html</anchorfile>
      <anchor>a9fb25bada3fffe9175449d6f905d1607</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr std::ptrdiff_t</type>
      <name>static_bits_size</name>
      <anchorfile>structeve_1_1top__bits.html</anchorfile>
      <anchor>a5c491e0d8fc88a6a045ea4b0f85aecc3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>is_cheap</name>
      <anchorfile>structeve_1_1top__bits.html</anchorfile>
      <anchor>a8b4e478b0579d0a46ccef25e51b58be9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::algo::traits</name>
    <filename>structeve_1_1algo_1_1traits.html</filename>
    <templarg>typename Settings</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::translation_of</name>
    <filename>structeve_1_1translation__of.html</filename>
    <templarg>typename T</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::underlying_type</name>
    <filename>structeve_1_1underlying__type.html</filename>
    <templarg>typename Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::wide</name>
    <filename>structeve_1_1wide.html</filename>
    <templarg>arithmetic_scalar_value Type</templarg>
    <templarg>typename Cardinal</templarg>
    <base>eve::_::wide_storage&lt; as_register_t&lt; translate_t&lt; Type &gt;, Cardinal, abi_t&lt; translate_t&lt; Type &gt;, Cardinal &gt; &gt; &gt;</base>
    <member kind="typedef">
      <type>Type</type>
      <name>value_type</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ad6e0f9fd221ca191f42484f47660662c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>translate_t&lt; Type &gt;</type>
      <name>translated_element_type</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a6f964ba2b4950d9916b5d280c88e8d6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>wide&lt; translated_element_type, Cardinal &gt;</type>
      <name>translated_type</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aa09188474474c521bce2199283dd0557</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>abi_t&lt; translated_element_type, Cardinal &gt;</type>
      <name>abi_type</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a18742aec2dcd5edb3fd2266adecbc270</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename storage_base::storage_type</type>
      <name>storage_type</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a592b87d63264bcc3271b84bc3a7a0f53</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Cardinal</type>
      <name>cardinal_type</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a920f3e350e21c8f5c217d7e199efc299</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::ptrdiff_t</type>
      <name>size_type</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a49b0787fd69bd2084750eb9d42cfcef4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>value_type</type>
      <name>is_like</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aff3a86e07d2a7b5aac81be591630dc0c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>wide&lt; Type, typename Cardinal::combined_type &gt;</type>
      <name>combined_type</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ab21c115bbd0b073881a3f8754a8d2f96</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>wide&lt; T, N &gt;</type>
      <name>rebind</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a68f8b26fc435b652492ebb9163b30ed5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>wide&lt; Type, N &gt;</type>
      <name>rescale</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a279755384913a23181f151ece5a4658f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>storage_type const &amp;</type>
      <name>storage</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>ae243fa6aac6a91ab5981865b306bce5d</anchor>
      <arglist>() const &amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type>storage_type &amp;</type>
      <name>storage</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a6e5b57453be18b7ab65c76db1f3a69e1</anchor>
      <arglist>() &amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type>storage_type</type>
      <name>storage</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a41a9064f838f216eb9f0c2e41e13a1df</anchor>
      <arglist>() &amp;&amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator storage_type const &amp;</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a9c3e7c0e98b4e52924e117c51030cbc1</anchor>
      <arglist>() const &amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator storage_type &amp;</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a1fc129d7b9dd250be0d466b3450cc815</anchor>
      <arglist>() &amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator storage_type</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a24c364353e6976cead7dcecebdfa788e</anchor>
      <arglist>() &amp;&amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a361d5a9fd15f6b2e4a86ec5ae2880e06</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a4c3c77232aadeb56066359ff149af963</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a4ad46a6f998bb898592da9625181634d</anchor>
      <arglist>(storage_type const &amp;r) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aa4cbde97fec5ebba311f78f757384bb3</anchor>
      <arglist>(Range &amp;&amp;r) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a9e8f8635331b18d7ce9e1c28019722be</anchor>
      <arglist>(Ptr ptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a31d05c169f1e12cad3c2818ef506261d</anchor>
      <arglist>(eve::soa_ptr&lt; Ptr... &gt; ptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a6c8db8292774ad2de873023619cf1456</anchor>
      <arglist>(S const &amp;v) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>adf12020cb7ac67cc5ee1c165c2b563d7</anchor>
      <arglist>(S0 v0, S1 v1, Ss... vs) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aedbf2986f6d9bb3c0968d6659f9b8ff1</anchor>
      <arglist>(S0 const &amp;v0, Ss const &amp;...vs) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide_a007581d779fcbfc70bfcee970ee95451.html</anchorfile>
      <anchor>a007581d779fcbfc70bfcee970ee95451</anchor>
      <arglist>(Generator &amp;&amp;g) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide_a007581d779fcbfc70bfcee970ee95451.html</anchorfile>
      <anchor>a007581d779fcbfc70bfcee970ee95451</anchor>
      <arglist>(Generator &amp;&amp;g) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a3f8ec537fe171202703714d1b1fb2678</anchor>
      <arglist>(W0 w0, W1 w1, Ws... ws) noexcept</arglist>
    </member>
    <member kind="function">
      <type>wide &amp;</type>
      <name>operator=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aba9bb24eb9587da6113d66145fe55966</anchor>
      <arglist>(storage_type const &amp;r)</arglist>
    </member>
    <member kind="function">
      <type>wide &amp;</type>
      <name>operator=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aa76549abd93145924149aba145078104</anchor>
      <arglist>(S v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a0c558b1099d1ab8939c82b766f12355a</anchor>
      <arglist>(std::size_t i, scalar_value auto v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>get</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a6ab6d5f972abe85345b3ba9e5f2db10e</anchor>
      <arglist>(std::size_t i) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>back</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a2ffca3c478214bf4b4ace457e492a100</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>front</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aa279df4c99dbc46206e9f70b44b1f769</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>slice</name>
      <anchorfile>structeve_1_1wide_ac2088fca71239dcd0ab7e7eaa37fb1ca.html</anchorfile>
      <anchor>ac2088fca71239dcd0ab7e7eaa37fb1ca</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>slice</name>
      <anchorfile>structeve_1_1wide_a452a5c32d8a4f59a03610431e9a951a4.html</anchorfile>
      <anchor>a452a5c32d8a4f59a03610431e9a951a4</anchor>
      <arglist>(slice_t&lt; Slice &gt; s) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a55d8e55d3b731a5c3c9e87a6f464faea</anchor>
      <arglist>(wide &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>wide &amp;</type>
      <name>operator++</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aef65082a19780da5397211d2cd070564</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>wide &amp;</type>
      <name>operator--</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a18191cf0606c11d4334837659121f274</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>wide</type>
      <name>operator++</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a926c371e6e63f7c8bbe921b4e66ca41f</anchor>
      <arglist>(int) noexcept</arglist>
    </member>
    <member kind="function">
      <type>wide</type>
      <name>operator--</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a31cc77d8a8f3300e7e810036f7065aa9</anchor>
      <arglist>(int) noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr size_type</type>
      <name>size</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a1d3739186033f12c8fe47755f598b60b</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr size_type</type>
      <name>max_size</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a21322b111e584432db366e3cc3ff7011</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr bool</type>
      <name>empty</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a1d49e69b0ec9ecbabcbffef68eba84eb</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend void</type>
      <name>swap</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ad1d370008485018ecd5bd61aa2fdd7b7</anchor>
      <arglist>(wide &amp;lhs, wide &amp;rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator~</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a12fb180e15ba59b5a3a90887b466fbd7</anchor>
      <arglist>(wide const &amp;v) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a416ed1c4a5b4421444d9913586e2931d</anchor>
      <arglist>(wide &amp;w, V o) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator&amp;</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a5fb8cf5bfe140c7364572a790950d375</anchor>
      <arglist>(wide const &amp;a, wide&lt; U, M &gt; const &amp;b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator&amp;</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a2a7fb57b5069ea3f7e718d8a369cd0df</anchor>
      <arglist>(wide const &amp;w, S s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide&lt; S, Cardinal &gt;</type>
      <name>operator&amp;</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a0ea5a43a912220dc1046cf4d54785615</anchor>
      <arglist>(S s, wide const &amp;w) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide &amp;</type>
      <name>operator|=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a831c238dece0b5e60ba7023c74e55e43</anchor>
      <arglist>(wide &amp;w, V o) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator|</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a510411035e4f3ab616a326c1cf600a43</anchor>
      <arglist>(wide const &amp;a, wide&lt; U, M &gt; const &amp;b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator|</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a5d6f4e9aeb45c455bb46cf4ac44c25ba</anchor>
      <arglist>(wide const &amp;w, S s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide&lt; S, Cardinal &gt;</type>
      <name>operator|</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>abe226796fe038be31f1cd40c4c5c5f46</anchor>
      <arglist>(S s, wide const &amp;w) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide &amp;</type>
      <name>operator^=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>af3a05e9bcd8ee8af072ba161ababd940</anchor>
      <arglist>(wide &amp;w, V o) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator^</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ac58f0ec0cf68c9ffdad5073442baf432</anchor>
      <arglist>(wide const &amp;a, wide&lt; U, M &gt; const &amp;b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator^</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ab38538e6d48efdfe32f6abb82edd18f7</anchor>
      <arglist>(wide const &amp;w, S s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide&lt; S, Cardinal &gt;</type>
      <name>operator^</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a4b0be51d4fbb68efaf0d4b3d9946df9e</anchor>
      <arglist>(S s, wide const &amp;w) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator+</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a722f30687ac48878156e8c633e6edd31</anchor>
      <arglist>(wide const &amp;v) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator-</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aa50a9f56055e9cffdebe32bf84ab9df8</anchor>
      <arglist>(wide const &amp;v) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide &amp;</type>
      <name>operator+=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aa1906f9ef4ccaad27be201d3a1f2a73c</anchor>
      <arglist>(wide &amp;w, V v) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator+</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ab16acf5d7ccb5f1aeb251cdc0aebc13b</anchor>
      <arglist>(wide const &amp;a, wide const &amp;b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator+</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aa9b7b0c83ac5c12b409e5acd988071ea</anchor>
      <arglist>(plain_scalar_value auto s, wide const &amp;v) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator+</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a3911283a2eeb4eba572560231f0a9579</anchor>
      <arglist>(wide const &amp;v, plain_scalar_value auto s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide &amp;</type>
      <name>operator-=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a84059f5993ecae06e44959412fcac46e</anchor>
      <arglist>(wide &amp;w, V v) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator-</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ab6996f68980eadf6ab967bf64b6cd944</anchor>
      <arglist>(wide const &amp;a, wide const &amp;b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator-</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a895e89b9eb2e1dde98715578da198b2e</anchor>
      <arglist>(plain_scalar_value auto s, wide const &amp;w) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator-</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ac95e76ed1339add1611a88869798e2cc</anchor>
      <arglist>(wide const &amp;w, plain_scalar_value auto s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide &amp;</type>
      <name>operator*=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a869930af4cdb046296f3b7130aaea0b1</anchor>
      <arglist>(wide &amp;w, V o) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator*</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ae47f669c4d4b177de43bafa2ca0014d6</anchor>
      <arglist>(wide const &amp;a, wide const &amp;b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator*</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a6ff04146f10e31b38dd414b04fbfcaf5</anchor>
      <arglist>(plain_scalar_value auto s, wide const &amp;w) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator*</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ad50257d51be052f034fea810dc49ff44</anchor>
      <arglist>(wide const &amp;w, plain_scalar_value auto s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide &amp;</type>
      <name>operator/=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a055a89c7bbd3deac103c335dc8c252a5</anchor>
      <arglist>(wide &amp;w, V o) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator/</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a325cd037a695c0a435b299ccaa6fceb2</anchor>
      <arglist>(wide const &amp;a, wide const &amp;b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator/</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aa2b4fdb3f61dc0434a355a62fbd2e234</anchor>
      <arglist>(plain_scalar_value auto s, wide const &amp;w) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator/</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ab9d277ff0f82213a87e497f4e642c286</anchor>
      <arglist>(wide const &amp;v, plain_scalar_value auto s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide &amp;</type>
      <name>operator%=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a2fe1fae1dcf75c2af6152cfc46f55899</anchor>
      <arglist>(wide &amp;w, V o) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator%</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aa9e8696f4a45f9a4fdb41059d4e11db3</anchor>
      <arglist>(wide const &amp;a, wide const &amp;b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator%</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a4b120dbb331ccfbfcb77aaac103d5df8</anchor>
      <arglist>(S s, wide const &amp;w) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator%</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>af1b065ebf8723fa483d0b0ac99215936</anchor>
      <arglist>(wide const &amp;w, integral_scalar_value auto s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a23823f11dc5d05e001c53f1f0c544bd5</anchor>
      <arglist>(wide &amp;w, S s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a1a7607cb0227a4a18ea54b03c418095a</anchor>
      <arglist>(wide &amp;w, index_t&lt; V &gt; const &amp;s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a8a34a40d14b33a7902beae234bfc8f29</anchor>
      <arglist>(wide w, S s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a67e12e28d9c929fe3e3e6418fcb35b75</anchor>
      <arglist>(wide w, index_t&lt; V &gt; const &amp;s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a448987909ba369b08a2fc8eba723e225</anchor>
      <arglist>(wide &amp;w, S s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a0c84acfad363d3ba1cd962895b5dbcfc</anchor>
      <arglist>(wide &amp;w, index_t&lt; V &gt; const &amp;s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend wide</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>afdb167123107c858420b4ce434eadb8a</anchor>
      <arglist>(wide w, S s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a14488e4046da2ed7322bdf6a294aaf3b</anchor>
      <arglist>(wide w, index_t&lt; V &gt; const &amp;s) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ae2dbf0e72ef246b1196ec9c5a72bd736</anchor>
      <arglist>(wide a, wide b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>afbf234567756964622b4c86e7fdb8275</anchor>
      <arglist>(wide w, S s) noexcept -&gt; decltype(is_equal(w, s))</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator==</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a30edc6bb08a0aaaaa099e86f196b1eed</anchor>
      <arglist>(S s, wide w) noexcept -&gt; decltype(is_equal(w, s))</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator!=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ac523c775a527c3d4cfc52919d0c22a41</anchor>
      <arglist>(wide a, wide b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator!=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a61aed544ca5cb58e3f57694f1ed2e85c</anchor>
      <arglist>(wide w, S s) noexcept -&gt; decltype(is_not_equal(w, s))</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator!=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>acae132610faa72786d71dcd9cf83be4b</anchor>
      <arglist>(S s, wide w) noexcept -&gt; decltype(is_not_equal(w, s))</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator&lt;</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a85fd0807a499fb6b08a47ea616c5b623</anchor>
      <arglist>(wide a, wide b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator&lt;</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aec977a9b8514b8d9f53ecc7000381e0d</anchor>
      <arglist>(wide w, S s) noexcept -&gt; decltype(is_less(w, s))</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator&lt;</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ae1c07b07182bad0a655e68f8e4276acc</anchor>
      <arglist>(S s, wide w) noexcept -&gt; decltype(is_less(s, w))</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator&gt;</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a8d2df4c5e6a401209939ff9afdf4be2a</anchor>
      <arglist>(wide a, wide b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator&gt;</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aa189a968f7374d6c8ed4236c69cbfb7c</anchor>
      <arglist>(wide w, S s) noexcept -&gt; decltype(is_greater(w, s))</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator&gt;</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ad1a34707921b1eb0752c60a8b565b2af</anchor>
      <arglist>(S s, wide w) noexcept -&gt; decltype(is_greater(s, w))</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator&gt;=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aba1c246782547cd95bccdc570387ef4c</anchor>
      <arglist>(wide a, wide b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator&gt;=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a31d004b25703f90e7416b0d1af0843f1</anchor>
      <arglist>(wide w, S s) noexcept -&gt; decltype(is_greater_equal(w, s))</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator&gt;=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ac1797654c973c850e6994517f55f4f3a</anchor>
      <arglist>(S s, wide w) noexcept -&gt; decltype(is_greater_equal(s, w))</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator&lt;=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a4fa5516020386fe69dcca898498c443f</anchor>
      <arglist>(wide a, wide b) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator&lt;=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>adea1c22f9a66dc4b9c8af1b5e4c62741</anchor>
      <arglist>(wide w, S s) noexcept -&gt; decltype(is_less_equal(w, s))</arglist>
    </member>
    <member kind="friend">
      <type>friend auto</type>
      <name>operator&lt;=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aeae4c2a8b1b015bad05f105154cdf19c</anchor>
      <arglist>(S s, wide w) noexcept -&gt; decltype(is_less_equal(s, w))</arglist>
    </member>
    <member kind="friend">
      <type>friend logical&lt; wide &gt;</type>
      <name>operator!</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>ad6866135977bdf52db203c4a82b74091</anchor>
      <arglist>(wide v) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a892856cb67eb75305928bb2e9a3e3127</anchor>
      <arglist>(std::basic_ostream&lt; C, Ct &gt; &amp;os, wide p)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr size_type</type>
      <name>size</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a1d3739186033f12c8fe47755f598b60b</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr size_type</type>
      <name>max_size</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a21322b111e584432db366e3cc3ff7011</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr bool</type>
      <name>empty</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a1d49e69b0ec9ecbabcbffef68eba84eb</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a361d5a9fd15f6b2e4a86ec5ae2880e06</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a4c3c77232aadeb56066359ff149af963</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a4ad46a6f998bb898592da9625181634d</anchor>
      <arglist>(storage_type const &amp;r) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aa4cbde97fec5ebba311f78f757384bb3</anchor>
      <arglist>(Range &amp;&amp;r) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a9e8f8635331b18d7ce9e1c28019722be</anchor>
      <arglist>(Ptr ptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a31d05c169f1e12cad3c2818ef506261d</anchor>
      <arglist>(eve::soa_ptr&lt; Ptr... &gt; ptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a6c8db8292774ad2de873023619cf1456</anchor>
      <arglist>(S const &amp;v) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>adf12020cb7ac67cc5ee1c165c2b563d7</anchor>
      <arglist>(S0 v0, S1 v1, Ss... vs) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aedbf2986f6d9bb3c0968d6659f9b8ff1</anchor>
      <arglist>(S0 const &amp;v0, Ss const &amp;...vs) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide_a007581d779fcbfc70bfcee970ee95451.html</anchorfile>
      <anchor>a007581d779fcbfc70bfcee970ee95451</anchor>
      <arglist>(Generator &amp;&amp;g) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide_a007581d779fcbfc70bfcee970ee95451.html</anchorfile>
      <anchor>a007581d779fcbfc70bfcee970ee95451</anchor>
      <arglist>(Generator &amp;&amp;g) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a3f8ec537fe171202703714d1b1fb2678</anchor>
      <arglist>(W0 w0, W1 w1, Ws... ws) noexcept</arglist>
    </member>
    <member kind="function">
      <type>wide &amp;</type>
      <name>operator=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aba9bb24eb9587da6113d66145fe55966</anchor>
      <arglist>(storage_type const &amp;r)</arglist>
    </member>
    <member kind="function">
      <type>wide &amp;</type>
      <name>operator=</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aa76549abd93145924149aba145078104</anchor>
      <arglist>(S v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a0c558b1099d1ab8939c82b766f12355a</anchor>
      <arglist>(std::size_t i, scalar_value auto v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>get</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a6ab6d5f972abe85345b3ba9e5f2db10e</anchor>
      <arglist>(std::size_t i) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>back</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a2ffca3c478214bf4b4ace457e492a100</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>front</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aa279df4c99dbc46206e9f70b44b1f769</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>slice</name>
      <anchorfile>structeve_1_1wide_ac2088fca71239dcd0ab7e7eaa37fb1ca.html</anchorfile>
      <anchor>ac2088fca71239dcd0ab7e7eaa37fb1ca</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>slice</name>
      <anchorfile>structeve_1_1wide_a452a5c32d8a4f59a03610431e9a951a4.html</anchorfile>
      <anchor>a452a5c32d8a4f59a03610431e9a951a4</anchor>
      <arglist>(slice_t&lt; Slice &gt; s) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a55d8e55d3b731a5c3c9e87a6f464faea</anchor>
      <arglist>(wide &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>wide &amp;</type>
      <name>operator++</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>aef65082a19780da5397211d2cd070564</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>wide &amp;</type>
      <name>operator--</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a18191cf0606c11d4334837659121f274</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>wide</type>
      <name>operator++</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a926c371e6e63f7c8bbe921b4e66ca41f</anchor>
      <arglist>(int) noexcept</arglist>
    </member>
    <member kind="function">
      <type>wide</type>
      <name>operator--</name>
      <anchorfile>structeve_1_1wide.html</anchorfile>
      <anchor>a31cc77d8a8f3300e7e810036f7065aa9</anchor>
      <arglist>(int) noexcept</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::_::wide_storage</name>
    <filename>structeve_1_1___1_1wide__storage.html</filename>
    <templarg>typename Storage</templarg>
    <member kind="function">
      <type>storage_type const &amp;</type>
      <name>storage</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>ae243fa6aac6a91ab5981865b306bce5d</anchor>
      <arglist>() const &amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type>storage_type &amp;</type>
      <name>storage</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a6e5b57453be18b7ab65c76db1f3a69e1</anchor>
      <arglist>() &amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type>storage_type</type>
      <name>storage</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a41a9064f838f216eb9f0c2e41e13a1df</anchor>
      <arglist>() &amp;&amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator storage_type const &amp;</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a9c3e7c0e98b4e52924e117c51030cbc1</anchor>
      <arglist>() const &amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator storage_type &amp;</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a1fc129d7b9dd250be0d466b3450cc815</anchor>
      <arglist>() &amp;noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator storage_type</name>
      <anchorfile>structeve_1_1___1_1wide__storage.html</anchorfile>
      <anchor>a24c364353e6976cead7dcecebdfa788e</anchor>
      <arglist>() &amp;&amp;noexcept</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>eve::algo::views::zip_iterator</name>
    <filename>structeve_1_1algo_1_1views_1_1zip__iterator.html</filename>
    <templarg>typename ... Is</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::views::zip_iterator</name>
    <filename>structeve_1_1views_1_1zip__iterator.html</filename>
    <templarg>typename ... Is</templarg>
  </compound>
  <compound kind="struct">
    <name>zip_iterator</name>
    <filename>structzip__iterator.html</filename>
  </compound>
  <compound kind="struct">
    <name>eve::algo::views::zip_range</name>
    <filename>structeve_1_1algo_1_1views_1_1zip__range.html</filename>
    <templarg>relaxed_range ... Rngs</templarg>
  </compound>
  <compound kind="struct">
    <name>eve::views::zip_range</name>
    <filename>structeve_1_1views_1_1zip__range.html</filename>
    <templarg>relaxed_range ... Rngs</templarg>
  </compound>
  <compound kind="struct">
    <name>zip_range</name>
    <filename>structzip__range.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::abelian_monoid</name>
    <filename>concepteve_1_1abelian__monoid.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::algo::non_owning_range</name>
    <filename>concepteve_1_1algo_1_1non__owning__range.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::arithmetic_scalar_value</name>
    <filename>concepteve_1_1arithmetic__scalar__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::arithmetic_value</name>
    <filename>concepteve_1_1arithmetic__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::callable_object</name>
    <filename>concepteve_1_1callable__object.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::combinable</name>
    <filename>concepteve_1_1combinable.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::combinable_to</name>
    <filename>concepteve_1_1combinable__to.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::conditional_expr</name>
    <filename>concepteve_1_1conditional__expr.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::floating_scalar_value</name>
    <filename>concepteve_1_1floating__scalar__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::floating_simd_value</name>
    <filename>concepteve_1_1floating__simd__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::floating_value</name>
    <filename>concepteve_1_1floating__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::generator</name>
    <filename>concepteve_1_1generator.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::generator_from</name>
    <filename>concepteve_1_1generator__from.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::has_plain_translation</name>
    <filename>concepteve_1_1has__plain__translation.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::has_store_equivalent</name>
    <filename>concepteve_1_1has__store__equivalent.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::integral_scalar_value</name>
    <filename>concepteve_1_1integral__scalar__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::integral_simd_value</name>
    <filename>concepteve_1_1integral__simd__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::integral_value</name>
    <filename>concepteve_1_1integral__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::invocable_returning</name>
    <filename>concepteve_1_1invocable__returning.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::irregular_predicate</name>
    <filename>concepteve_1_1irregular__predicate.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::like</name>
    <filename>concepteve_1_1like.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::logical_scalar_value</name>
    <filename>concepteve_1_1logical__scalar__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::logical_simd_value</name>
    <filename>concepteve_1_1logical__simd__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::logical_value</name>
    <filename>concepteve_1_1logical__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::match_option</name>
    <filename>concepteve_1_1match__option.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::only_if</name>
    <filename>concepteve_1_1only__if.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::pattern_formula</name>
    <filename>concepteve_1_1pattern__formula.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::plain_scalar_value</name>
    <filename>concepteve_1_1plain__scalar__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::plain_value</name>
    <filename>concepteve_1_1plain__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::product_scalar_value</name>
    <filename>concepteve_1_1product__scalar__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::relative_conditional_expr</name>
    <filename>concepteve_1_1relative__conditional__expr.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::relaxed_logical_scalar_value</name>
    <filename>concepteve_1_1relaxed__logical__scalar__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::relaxed_logical_value</name>
    <filename>concepteve_1_1relaxed__logical__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::scalar_value</name>
    <filename>concepteve_1_1scalar__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::signed_integral_scalar_value</name>
    <filename>concepteve_1_1signed__integral__scalar__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::signed_integral_simd_value</name>
    <filename>concepteve_1_1signed__integral__simd__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::signed_integral_value</name>
    <filename>concepteve_1_1signed__integral__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::signed_scalar_value</name>
    <filename>concepteve_1_1signed__scalar__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::signed_simd_value</name>
    <filename>concepteve_1_1signed__simd__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::signed_value</name>
    <filename>concepteve_1_1signed__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::simd_predicate</name>
    <filename>concepteve_1_1simd__predicate.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::simd_value</name>
    <filename>concepteve_1_1simd__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::substitute_for</name>
    <filename>concepteve_1_1substitute__for.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::translatable</name>
    <filename>concepteve_1_1translatable.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::translatable_ptr</name>
    <filename>concepteve_1_1translatable__ptr.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::translatable_struct</name>
    <filename>concepteve_1_1translatable__struct.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::unsigned_scalar_value</name>
    <filename>concepteve_1_1unsigned__scalar__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::unsigned_simd_value</name>
    <filename>concepteve_1_1unsigned__simd__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::unsigned_value</name>
    <filename>concepteve_1_1unsigned__value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::value</name>
    <filename>concepteve_1_1value.html</filename>
  </compound>
  <compound kind="concept">
    <name>eve::wide_cardinal</name>
    <filename>concepteve_1_1wide__cardinal.html</filename>
  </compound>
  <compound kind="namespace">
    <name>eve</name>
    <filename>namespaceeve.html</filename>
    <namespace>eve::_</namespace>
    <class kind="struct">eve::abi</class>
    <class kind="struct">eve::fixed</class>
    <class kind="struct">eve::logical&lt; T &gt;</class>
    <class kind="struct">eve::logical&lt; wide&lt; Type, Cardinal &gt; &gt;</class>
    <class kind="struct">eve::top_bits</class>
    <class kind="struct">eve::wide</class>
    <class kind="struct">eve::fundamental_cardinal</class>
    <class kind="struct">eve::platform</class>
    <class kind="struct">eve::as</class>
    <class kind="struct">eve::as_element</class>
    <class kind="struct">eve::or_</class>
    <class kind="struct">eve::if_</class>
    <class kind="struct">eve::ignore_all_</class>
    <class kind="struct">eve::ignore_none_</class>
    <class kind="struct">eve::keep_first</class>
    <class kind="struct">eve::ignore_last</class>
    <class kind="struct">eve::keep_last</class>
    <class kind="struct">eve::ignore_first</class>
    <class kind="struct">eve::keep_between</class>
    <class kind="struct">eve::ignore_extrema</class>
    <class kind="struct">eve::aligned_allocator</class>
    <class kind="struct">eve::aligned_ptr</class>
    <class kind="struct">eve::soa_ptr</class>
    <class kind="struct">eve::stack_buffer</class>
    <class kind="struct">eve::pattern_t</class>
    <class kind="struct">eve::as_pattern</class>
    <class kind="struct">eve::cardinal</class>
    <class kind="struct">eve::common_compatible</class>
    <class kind="struct">eve::common_type</class>
    <class kind="struct">eve::comparisons</class>
    <class kind="struct">eve::element_type</class>
    <class kind="struct">eve::callable</class>
    <class kind="struct">eve::constant_callable</class>
    <class kind="struct">eve::elementwise_callable</class>
    <class kind="struct">eve::options</class>
    <class kind="struct">eve::decorated_with</class>
    <class kind="struct">eve::relative_conditional_option</class>
    <class kind="struct">eve::conditional_option</class>
    <class kind="struct">eve::supports_ordering</class>
    <class kind="struct">eve::supports_like</class>
    <class kind="struct">eve::struct_support</class>
    <class kind="struct">eve::translation_of</class>
    <class kind="struct">eve::underlying_type</class>
    <concept>eve::wide_cardinal</concept>
    <concept>eve::combinable</concept>
    <concept>eve::combinable_to</concept>
    <concept>eve::conditional_expr</concept>
    <concept>eve::relative_conditional_expr</concept>
    <concept>eve::generator</concept>
    <concept>eve::irregular_predicate</concept>
    <concept>eve::invocable_returning</concept>
    <concept>eve::simd_predicate</concept>
    <concept>eve::abelian_monoid</concept>
    <concept>eve::match_option</concept>
    <concept>eve::only_if</concept>
    <concept>eve::translatable_ptr</concept>
    <concept>eve::plain_scalar_value</concept>
    <concept>eve::logical_scalar_value</concept>
    <concept>eve::product_scalar_value</concept>
    <concept>eve::arithmetic_scalar_value</concept>
    <concept>eve::scalar_value</concept>
    <concept>eve::relaxed_logical_scalar_value</concept>
    <concept>eve::logical_simd_value</concept>
    <concept>eve::substitute_for</concept>
    <concept>eve::has_plain_translation</concept>
    <concept>eve::value</concept>
    <concept>eve::integral_value</concept>
    <concept>eve::signed_value</concept>
    <concept>eve::unsigned_value</concept>
    <concept>eve::signed_integral_value</concept>
    <concept>eve::floating_value</concept>
    <concept>eve::logical_value</concept>
    <concept>eve::plain_value</concept>
    <concept>eve::arithmetic_value</concept>
    <concept>eve::relaxed_logical_value</concept>
    <concept>eve::integral_scalar_value</concept>
    <concept>eve::signed_scalar_value</concept>
    <concept>eve::unsigned_scalar_value</concept>
    <concept>eve::signed_integral_scalar_value</concept>
    <concept>eve::floating_scalar_value</concept>
    <concept>eve::simd_value</concept>
    <concept>eve::integral_simd_value</concept>
    <concept>eve::signed_simd_value</concept>
    <concept>eve::unsigned_simd_value</concept>
    <concept>eve::signed_integral_simd_value</concept>
    <concept>eve::floating_simd_value</concept>
    <concept>eve::has_store_equivalent</concept>
    <concept>eve::pattern_formula</concept>
    <concept>eve::callable_object</concept>
    <concept>eve::like</concept>
    <concept>eve::translatable_struct</concept>
    <concept>eve::translatable</concept>
    <concept>eve::generator_from</concept>
    <member kind="typedef">
      <type>fixed&lt; expected_cardinal_v&lt; Type, ABI &gt; &gt;</type>
      <name>expected_cardinal_t</name>
      <anchorfile>group__arch_gab707570aa2d35678c5cd5c686a994d57.html</anchorfile>
      <anchor>gab707570aa2d35678c5cd5c686a994d57</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>decltype(unalign(std::declval&lt; T &gt;()))</type>
      <name>unaligned_t</name>
      <anchorfile>group__memory_ga54bcb5761211b78d9de3101200a49a9e.html</anchorfile>
      <anchor>ga54bcb5761211b78d9de3101200a49a9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>eve::result_t&lt; zip, Vs... &gt;</type>
      <name>zipped</name>
      <anchorfile>namespaceeve.html</anchorfile>
      <anchor>a1322b257556bbaaadfad2df9bdd3f4f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename eve::_::common_value_impl&lt; void, Ts... &gt;::type</type>
      <name>common_value_t</name>
      <anchorfile>namespaceeve.html</anchorfile>
      <anchor>af8149a965ef1e4b8f73ff49e426532d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>decltype(_::iterator_cardinal_impl&lt; T &gt;())</type>
      <name>iterator_cardinal_t</name>
      <anchorfile>group__traits_ga331d84fa4b64e5deb329b1a09d60c747.html</anchorfile>
      <anchor>ga331d84fa4b64e5deb329b1a09d60c747</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename decltype(_::as_translated_type(as&lt; T &gt;{}))::type</type>
      <name>translate_t</name>
      <anchorfile>namespaceeve_a7f168aef1d16a9b1d923d0a26a20ef7d.html</anchorfile>
      <anchor>a7f168aef1d16a9b1d923d0a26a20ef7d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename decltype(_::value_type_impl&lt; T &gt;())::type</type>
      <name>value_type_t</name>
      <anchorfile>group__traits_gaae6fbba5b56b9fab940a05b444c15e6f.html</anchorfile>
      <anchor>gaae6fbba5b56b9fab940a05b444c15e6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>as_wide_t&lt; value_type_t&lt; T &gt;, iterator_cardinal_t&lt; T &gt; &gt;</type>
      <name>wide_value_type_t</name>
      <anchorfile>group__traits_ga55234286d380ec9a9baef96a65649356.html</anchorfile>
      <anchor>ga55234286d380ec9a9baef96a65649356</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>over</name>
      <anchorfile>group__memory_ga069e9f110c0cb2416812ef8fc5a37555.html</anchorfile>
      <anchor>ga069e9f110c0cb2416812ef8fc5a37555</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>under</name>
      <anchorfile>group__memory_ga664bc5b316e0dd3be42aa4c2fd818047.html</anchorfile>
      <anchor>ga664bc5b316e0dd3be42aa4c2fd818047</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>operator==</name>
      <anchorfile>group__simd__types.html</anchorfile>
      <anchor>ga8a5020911faf4ccefcfb1d2a8b718719</anchor>
      <arglist>(logical&lt; wide&lt; T, Cardinal &gt; &gt; a, logical&lt; wide&lt; U, Cardinal &gt; &gt; b) noexcept -&gt; decltype(is_equal(a, b))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>operator!=</name>
      <anchorfile>group__simd__types.html</anchorfile>
      <anchor>gaa3dfaa4cfdde3a9e71e878d8fe9dce3a</anchor>
      <arglist>(logical&lt; wide&lt; T, Cardinal &gt; &gt; a, logical&lt; wide&lt; U, Cardinal &gt; &gt; b) noexcept -&gt; decltype(is_not_equal(a, b))</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>drop_alternative</name>
      <anchorfile>group__conditional_ga8265bd793db77b43d12988c1c297f00b.html</anchorfile>
      <anchor>ga8265bd793db77b43d12988c1c297f00b</anchor>
      <arglist>(C c)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>map_alternative</name>
      <anchorfile>group__conditional_ga6b75905a0b2d6320cadb973c752a8cd1.html</anchorfile>
      <anchor>ga6b75905a0b2d6320cadb973c752a8cd1</anchor>
      <arglist>(C c, auto op)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>bit_cast_alternative</name>
      <anchorfile>group__conditional_gaba39b1743e4775c0c19966dac6342762.html</anchorfile>
      <anchor>gaba39b1743e4775c0c19966dac6342762</anchor>
      <arglist>(C c, as&lt; Tgt &gt; tgt)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>reverse_conditional</name>
      <anchorfile>group__conditional_gab99c14f8c7e6cd5fc693a79c97bc89d8.html</anchorfile>
      <anchor>gab99c14f8c7e6cd5fc693a79c97bc89d8</anchor>
      <arglist>(C c, eve::as&lt; T &gt; tgt)</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_aligned</name>
      <anchorfile>group__memory_gad05ab928f3e9aa972a7e7146f76cce13.html</anchorfile>
      <anchor>gad05ab928f3e9aa972a7e7146f76cce13</anchor>
      <arglist>(aligned_ptr&lt; T, Other &gt; const &amp;ptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr&lt; Type const, Lanes &gt;</type>
      <name>as_aligned</name>
      <anchorfile>namespaceeve.html</anchorfile>
      <anchor>a5c8abb85533f462eaf77e6b4bc945b7f</anchor>
      <arglist>(Type const *ptr, Lanes) noexcept</arglist>
    </member>
    <member kind="function">
      <type>aligned_ptr&lt; Type const &gt;</type>
      <name>as_aligned</name>
      <anchorfile>namespaceeve.html</anchorfile>
      <anchor>a0280fa32cdcf6ac1877275412df23158</anchor>
      <arglist>(Type const *ptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_aligned</name>
      <anchorfile>group__memory_gab1add731db6f65a080c9ec8b4a125858.html</anchorfile>
      <anchor>gab1add731db6f65a080c9ec8b4a125858</anchor>
      <arglist>(T v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_aligned</name>
      <anchorfile>group__memory_ga25228d751afbdd3a2c7d09aea5f2ae74.html</anchorfile>
      <anchor>ga25228d751afbdd3a2c7d09aea5f2ae74</anchor>
      <arglist>(T *ptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_aligned</name>
      <anchorfile>group__memory_ga3c06e236e6195d1a36a43e0fcc7c5eca.html</anchorfile>
      <anchor>ga3c06e236e6195d1a36a43e0fcc7c5eca</anchor>
      <arglist>(T *ptr, Lanes lanes) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap_if</name>
      <anchorfile>group__core__logical_ga2d5530893d21e4e04802f96fd85309df.html</anchorfile>
      <anchor>ga2d5530893d21e4e04802f96fd85309df</anchor>
      <arglist>(Mask const &amp;mask, Value &amp;lhs, Value &amp;rhs) noexcept</arglist>
    </member>
    <member kind="function">
      <type>***constexpr auto</type>
      <name>horner</name>
      <anchorfile>group__math_ga5096faebf5c6aa4322537cf78cfe8e46.html</anchorfile>
      <anchor>ga5096faebf5c6aa4322537cf78cfe8e46</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>***constexpr auto</type>
      <name>newton</name>
      <anchorfile>group__polynomial_ga4293b5bcb8c53576558f6b294fc62a56.html</anchorfile>
      <anchor>ga4293b5bcb8c53576558f6b294fc62a56</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>***constexpr auto</type>
      <name>tchebsum</name>
      <anchorfile>group__math_ga6e2a171376fb33816873c1b5a0937ceb.html</anchorfile>
      <anchor>ga6e2a171376fb33816873c1b5a0937ceb</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr translate_t&lt; V &gt;</type>
      <name>translate</name>
      <anchorfile>namespaceeve_a2ca18720b2c0736de236fbbd8b003ab8.html</anchorfile>
      <anchor>a2ca18720b2c0736de236fbbd8b003ab8</anchor>
      <arglist>(V const &amp;val)</arglist>
    </member>
    <member kind="function">
      <type>constexpr std::array&lt; translate_t&lt; T &gt;, N &gt;</type>
      <name>translate</name>
      <anchorfile>namespaceeve_ae1475d9cc84bb8240682ba568181e438.html</anchorfile>
      <anchor>ae1475d9cc84bb8240682ba568181e438</anchor>
      <arglist>(std::array&lt; T, N &gt; val)</arglist>
    </member>
    <member kind="function">
      <type>constexpr translate_t&lt; V &gt; &amp;</type>
      <name>translate_ref</name>
      <anchorfile>namespaceeve_a0bcd8c2632634d1a1861d352b0ec9ae0.html</anchorfile>
      <anchor>a0bcd8c2632634d1a1861d352b0ec9ae0</anchor>
      <arglist>(V &amp;val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>namespaceeve.html</anchorfile>
      <anchor>a69ab9db52c90128a055b0aaf62db8892</anchor>
      <arglist>(S const &amp;) -&gt; wide&lt; S, expected_cardinal_t&lt; S &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>namespaceeve.html</anchorfile>
      <anchor>ac72f0e04016942948dc0d1bf861296f4</anchor>
      <arglist>(S, Ss...) -&gt; wide&lt; S, fixed&lt; 1+sizeof...(Ss)&gt; &gt;</arglist>
    </member>
    <member kind="variable">
      <type>constexpr std::ptrdiff_t</type>
      <name>nofs_cardinal_v</name>
      <anchorfile>group__arch_gab4d8e703ad1e3e94918f3a3ff44e1324.html</anchorfile>
      <anchor>gab4d8e703ad1e3e94918f3a3ff44e1324</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr ignore_all_</type>
      <name>ignore_all</name>
      <anchorfile>group__conditional.html</anchorfile>
      <anchor>ga6ce7ac450593ee98fe8ca0d9cf65e4b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr ignore_none_</type>
      <name>ignore_none</name>
      <anchorfile>group__conditional.html</anchorfile>
      <anchor>gae234dce7533ecc38fe2c70fd69383633</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>airy</name>
      <anchorfile>group__bessel_ga6c4d8609a742264dca4bdc09d023a22c.html</anchorfile>
      <anchor>ga6c4d8609a742264dca4bdc09d023a22c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>airy_ai</name>
      <anchorfile>group__bessel_ga8d4ff73facf4b69dff9df163055aa5f5.html</anchorfile>
      <anchor>ga8d4ff73facf4b69dff9df163055aa5f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>airy_bi</name>
      <anchorfile>group__bessel_gafe57d2b74c8426e5ab7229371b72c6df.html</anchorfile>
      <anchor>gafe57d2b74c8426e5ab7229371b72c6df</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bessel_i</name>
      <anchorfile>group__functions_ga7452ee5fe3560182c6f4bf00ae2932bb.html</anchorfile>
      <anchor>ga7452ee5fe3560182c6f4bf00ae2932bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bessel_j</name>
      <anchorfile>group__functions_gabb4a644d55742f984dede09b40cc5e4b.html</anchorfile>
      <anchor>gabb4a644d55742f984dede09b40cc5e4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bessel_k</name>
      <anchorfile>group__functions_gacaabaef4d4bb47b01bf39ac76413d44a.html</anchorfile>
      <anchor>gacaabaef4d4bb47b01bf39ac76413d44a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bessel_y</name>
      <anchorfile>group__functions_gae7f2a58376927c82f6a650802d6f6116.html</anchorfile>
      <anchor>gae7f2a58376927c82f6a650802d6f6116</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bernouilli</name>
      <anchorfile>group__combinatorial_ga593a2a4580b4130dcfdf334a86a16409.html</anchorfile>
      <anchor>ga593a2a4580b4130dcfdf334a86a16409</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fibonacci</name>
      <anchorfile>group__combinatorial_ga53fabf7d60ead52b043a80c3733f3567.html</anchorfile>
      <anchor>ga53fabf7d60ead52b043a80c3733f3567</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>gcd</name>
      <anchorfile>group__combinatorial_gadcf37697731fa4c94ebe972425b2dbc3.html</anchorfile>
      <anchor>gadcf37697731fa4c94ebe972425b2dbc3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lcm</name>
      <anchorfile>group__combinatorial_ga6a5fc60b3c1e87c5f71b5c51f5b664b5.html</anchorfile>
      <anchor>ga6a5fc60b3c1e87c5f71b5c51f5b664b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>nth_prime</name>
      <anchorfile>group__combinatorial_ga07a4c4bd17dd7be0c16010a39d9d9d93.html</anchorfile>
      <anchor>ga07a4c4bd17dd7be0c16010a39d9d9d93</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>prime_ceil</name>
      <anchorfile>group__combinatorial_ga4da0702dc11efa19b527fe8020267bf5.html</anchorfile>
      <anchor>ga4da0702dc11efa19b527fe8020267bf5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>prime_floor</name>
      <anchorfile>group__combinatorial_gab62baf715bca909acd246288c46f68b3.html</anchorfile>
      <anchor>gab62baf715bca909acd246288c46f68b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr callable_compress_</type>
      <name>compress</name>
      <anchorfile>group__core__compress_gafec1baa8724fc7e106d718836053db7c.html</anchorfile>
      <anchor>gafec1baa8724fc7e106d718836053db7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>compress_copy</name>
      <anchorfile>group__core__compress_ga8e545371fd605df1555e4cd0b2f62374.html</anchorfile>
      <anchor>ga8e545371fd605df1555e4cd0b2f62374</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>compress_store</name>
      <anchorfile>group__core__compress_ga621a2ba91bb1c5a07e5a51b87ebd5c06.html</anchorfile>
      <anchor>ga621a2ba91bb1c5a07e5a51b87ebd5c06</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>allbits</name>
      <anchorfile>group__core__constants_gafec20985737ed747df5f5f3be1469c6a.html</anchorfile>
      <anchor>gafec20985737ed747df5f5f3be1469c6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>as_value</name>
      <anchorfile>group__core__conversions_gae0215a0e7a791f53d8026ed30cd5c818.html</anchorfile>
      <anchor>gae0215a0e7a791f53d8026ed30cd5c818</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bitincrement</name>
      <anchorfile>group__core__constants_ga8ac2e1af8d69203e7c682b328de94097.html</anchorfile>
      <anchor>ga8ac2e1af8d69203e7c682b328de94097</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eps</name>
      <anchorfile>group__core__constants_ga3a08ea3bf1e679ed4ef0576ddffff08a.html</anchorfile>
      <anchor>ga3a08ea3bf1e679ed4ef0576ddffff08a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>exponentmask</name>
      <anchorfile>group__core__constants_ga15630d42e0187a51aa629ecc00dbe7e7.html</anchorfile>
      <anchor>ga15630d42e0187a51aa629ecc00dbe7e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>false_</name>
      <anchorfile>group__core__constants_gae7b8b0fcffea34e1d766e0db525ce223.html</anchorfile>
      <anchor>gae7b8b0fcffea34e1d766e0db525ce223</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>half</name>
      <anchorfile>group__core__constants_ga615c9124768fecc05e04d58ae24f8870.html</anchorfile>
      <anchor>ga615c9124768fecc05e04d58ae24f8870</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>inf</name>
      <anchorfile>group__core__constants_ga8a568ccc9a870bc971851209c836bc63.html</anchorfile>
      <anchor>ga8a568ccc9a870bc971851209c836bc63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>iota</name>
      <anchorfile>group__core__constants_ga45b9b51c21e6aa1d7879dd2b68f886af.html</anchorfile>
      <anchor>ga45b9b51c21e6aa1d7879dd2b68f886af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>logeps</name>
      <anchorfile>group__core__constants_ga9bd28cd479c5b123576e291079c92252.html</anchorfile>
      <anchor>ga9bd28cd479c5b123576e291079c92252</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>majorant</name>
      <anchorfile>group__core__constants_ga2544f12d841d878129a13f0fab8d1d21.html</anchorfile>
      <anchor>ga2544f12d841d878129a13f0fab8d1d21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>mantissamask</name>
      <anchorfile>group__core__constants_gacf720a49d31c18bade023482b9e7c3d7.html</anchorfile>
      <anchor>gacf720a49d31c18bade023482b9e7c3d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>max_safe_integer</name>
      <anchorfile>group__core__constants_gab391c95d967bf4d809e42b77fa21ab1d.html</anchorfile>
      <anchor>gab391c95d967bf4d809e42b77fa21ab1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>maxexponent</name>
      <anchorfile>group__core__constants_ga44e6675c343b28dca02c76705b40f854.html</anchorfile>
      <anchor>ga44e6675c343b28dca02c76705b40f854</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>maxexponentm1</name>
      <anchorfile>group__core__constants_gad11242a44d43460b85f35dc488e60d44.html</anchorfile>
      <anchor>gad11242a44d43460b85f35dc488e60d44</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>maxexponentp1</name>
      <anchorfile>group__core__constants_gad0fab24db7ab730a02c643c3237a7474.html</anchorfile>
      <anchor>gad0fab24db7ab730a02c643c3237a7474</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>maxflint</name>
      <anchorfile>group__core__constants_gaeee06bbd7d417e000d05bd801a3b8c85.html</anchorfile>
      <anchor>gaeee06bbd7d417e000d05bd801a3b8c85</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>maxrepint</name>
      <anchorfile>group__core__constants_gac0365cd157f1c08a778de3876e4e8f77.html</anchorfile>
      <anchor>gac0365cd157f1c08a778de3876e4e8f77</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>mhalf</name>
      <anchorfile>group__core__constants_ga7e79770188ed1bff8006179660157182.html</anchorfile>
      <anchor>ga7e79770188ed1bff8006179660157182</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minexponent</name>
      <anchorfile>group__core__constants_ga59cbceaa5903da81191784af48fed2c4.html</anchorfile>
      <anchor>ga59cbceaa5903da81191784af48fed2c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minorant</name>
      <anchorfile>group__core__constants_gaf7260a29fbb85cf0cfd97ad1d130c07c.html</anchorfile>
      <anchor>gaf7260a29fbb85cf0cfd97ad1d130c07c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>mone</name>
      <anchorfile>group__core__constants_ga5628ae5a0568eaa5e4672e3e63b6db35.html</anchorfile>
      <anchor>ga5628ae5a0568eaa5e4672e3e63b6db35</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>mzero</name>
      <anchorfile>group__core__constants_ga5551a5df5e64f90f6c9f498cc34f2b48.html</anchorfile>
      <anchor>ga5551a5df5e64f90f6c9f498cc34f2b48</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>nan</name>
      <anchorfile>group__core__constants_ga34b67924fa53bec83dfc96b51bd8fe56.html</anchorfile>
      <anchor>ga34b67924fa53bec83dfc96b51bd8fe56</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>nbmantissabits</name>
      <anchorfile>group__core__constants_gab41a973941d389c6f72a75c0c67cf0aa.html</anchorfile>
      <anchor>gab41a973941d389c6f72a75c0c67cf0aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>one</name>
      <anchorfile>group__core__constants_gac66f3d66fece21b4454e79500cc56f84.html</anchorfile>
      <anchor>gac66f3d66fece21b4454e79500cc56f84</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>oneosqrteps</name>
      <anchorfile>group__core__constants_gaa4dee4a2fdd3007c7da25099e85ea347.html</anchorfile>
      <anchor>gaa4dee4a2fdd3007c7da25099e85ea347</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>signmask</name>
      <anchorfile>group__core__constants_ga25424bccdc3f3ea6a6b9708532d15b05.html</anchorfile>
      <anchor>ga25424bccdc3f3ea6a6b9708532d15b05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>smallestposval</name>
      <anchorfile>group__core__constants_gadf2de69a7c166758ea2c4643e0fae62e.html</anchorfile>
      <anchor>gadf2de69a7c166758ea2c4643e0fae62e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqrteps</name>
      <anchorfile>group__core__constants_gaaf00b43c0dea1f135df9d2ac07b740a5.html</anchorfile>
      <anchor>gaaf00b43c0dea1f135df9d2ac07b740a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqrtsmallestposval</name>
      <anchorfile>group__core__constants_ga7eabdcaa9c3ff3d84982115706c2295b.html</anchorfile>
      <anchor>ga7eabdcaa9c3ff3d84982115706c2295b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqrtvalmax</name>
      <anchorfile>group__core__constants_gae61c7e9e1fdc501c543f2281a83242af.html</anchorfile>
      <anchor>gae61c7e9e1fdc501c543f2281a83242af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>true_</name>
      <anchorfile>group__core__constants_ga38f80597f70583a4be7fcc9ac558af95.html</anchorfile>
      <anchor>ga38f80597f70583a4be7fcc9ac558af95</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>twotonmb</name>
      <anchorfile>group__core__constants_ga68cec35679af23cec74599650704d4ee.html</anchorfile>
      <anchor>ga68cec35679af23cec74599650704d4ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>valmax</name>
      <anchorfile>group__core__constants_ga85073f11abb76d43faf07742435ea083.html</anchorfile>
      <anchor>ga85073f11abb76d43faf07742435ea083</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>valmin</name>
      <anchorfile>group__core__constants_ga1fd45a655473cde0022e08497eba14c1.html</anchorfile>
      <anchor>ga1fd45a655473cde0022e08497eba14c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>zero</name>
      <anchorfile>group__core__constants_gab4ecebb6ef8d0c73695dee1eb7371e6f.html</anchorfile>
      <anchor>gab4ecebb6ef8d0c73695dee1eb7371e6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>blend</name>
      <anchorfile>group__core__named__shuffles_ga43d76ccd08cc93ecbf6ebff44ca6321f.html</anchorfile>
      <anchor>ga43d76ccd08cc93ecbf6ebff44ca6321f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>broadcast_lane</name>
      <anchorfile>group__core__named__shuffles_ga9a82942f0d1facc72749788d545576fa.html</anchorfile>
      <anchor>ga9a82942f0d1facc72749788d545576fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>reverse</name>
      <anchorfile>group__core__named__shuffles_ga64933cc646e6b0711efa760eec8a69d9.html</anchorfile>
      <anchor>ga64933cc646e6b0711efa760eec8a69d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>reverse_in_subgroups</name>
      <anchorfile>group__core__named__shuffles_ga67244946cf4cab4f4f2bc19e0c9f9b81.html</anchorfile>
      <anchor>ga67244946cf4cab4f4f2bc19e0c9f9b81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>swap_adjacent</name>
      <anchorfile>group__core__named__shuffles_gadf4386e52fdcc1b41879ce39ee4a518d.html</anchorfile>
      <anchor>gadf4386e52fdcc1b41879ce39ee4a518d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>abs</name>
      <anchorfile>group__core__arithmetic_ga67722c49041abeb17485c8961f961cd7.html</anchorfile>
      <anchor>ga67722c49041abeb17485c8961f961cd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>absmax</name>
      <anchorfile>group__core__arithmetic_gae3871e8b350b047a88488b22a63cf2e0.html</anchorfile>
      <anchor>gae3871e8b350b047a88488b22a63cf2e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>absmin</name>
      <anchorfile>group__core__arithmetic_ga12cb5353ac66eb2bd19b81edaba931ed.html</anchorfile>
      <anchor>ga12cb5353ac66eb2bd19b81edaba931ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>add</name>
      <anchorfile>group__core__arithmetic_gad99c93772514004f757c09fb54ac6b5f.html</anchorfile>
      <anchor>gad99c93772514004f757c09fb54ac6b5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>agm</name>
      <anchorfile>group__core__arithmetic_ga9cde656e2fe72b65fe834806bda0ade5.html</anchorfile>
      <anchor>ga9cde656e2fe72b65fe834806bda0ade5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>all</name>
      <anchorfile>group__core__reduction_ga5cb8d1d1471423dfa2b00e7da2073169.html</anchorfile>
      <anchor>ga5cb8d1d1471423dfa2b00e7da2073169</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>any</name>
      <anchorfile>group__core__reduction_ga668c3edce7062da8ba1f66504d149f88.html</anchorfile>
      <anchor>ga668c3edce7062da8ba1f66504d149f88</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>average</name>
      <anchorfile>group__core__arithmetic_ga1718ca90633862e1c824380381d05f4f.html</anchorfile>
      <anchor>ga1718ca90633862e1c824380381d05f4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_and</name>
      <anchorfile>group__core__bitops_gae3e108a8e508c1fb8b0aab2c4d76d00c.html</anchorfile>
      <anchor>gae3e108a8e508c1fb8b0aab2c4d76d00c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_andnot</name>
      <anchorfile>group__core__bitops_gafb23397d6d6a6c4208e3ea1d236fcbc5.html</anchorfile>
      <anchor>gafb23397d6d6a6c4208e3ea1d236fcbc5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_cast</name>
      <anchorfile>group__core__bitops_gab65bdc36d2fdc7b11cd170358578e744.html</anchorfile>
      <anchor>gab65bdc36d2fdc7b11cd170358578e744</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_ceil</name>
      <anchorfile>group__core__bitops_gaf7fc9d3210aeb2c8077472eded029bd4.html</anchorfile>
      <anchor>gaf7fc9d3210aeb2c8077472eded029bd4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_flip</name>
      <anchorfile>group__core__bitops_ga1f7c7ed9d58b598d960e7299c06d5e75.html</anchorfile>
      <anchor>ga1f7c7ed9d58b598d960e7299c06d5e75</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_floor</name>
      <anchorfile>group__core__bitops_gafc377f8e75a726776f8d9976767a7334.html</anchorfile>
      <anchor>gafc377f8e75a726776f8d9976767a7334</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_mask</name>
      <anchorfile>group__core__bitops_ga7f9fd1df011b15b9c45ea99d9a628386.html</anchorfile>
      <anchor>ga7f9fd1df011b15b9c45ea99d9a628386</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_not</name>
      <anchorfile>group__core__bitops_ga8e445eb95a6a531251dc42c0af01d630.html</anchorfile>
      <anchor>ga8e445eb95a6a531251dc42c0af01d630</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_notand</name>
      <anchorfile>group__core__bitops_ga286a27cb5dcd6b825c07c93b4261f348.html</anchorfile>
      <anchor>ga286a27cb5dcd6b825c07c93b4261f348</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_notor</name>
      <anchorfile>group__core__bitops_gae31ad364665fdbdd1cac042a7a6d86f2.html</anchorfile>
      <anchor>gae31ad364665fdbdd1cac042a7a6d86f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_or</name>
      <anchorfile>group__core__bitops_gae4baca10d3834da1bedb3d6e1a795fd2.html</anchorfile>
      <anchor>gae4baca10d3834da1bedb3d6e1a795fd2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_ornot</name>
      <anchorfile>group__core__bitops_ga853007cb7c7071b4ce7a8512bdf30589.html</anchorfile>
      <anchor>ga853007cb7c7071b4ce7a8512bdf30589</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_reverse</name>
      <anchorfile>group__core__bitops_ga0050537e0c11470348add6553252bcf1.html</anchorfile>
      <anchor>ga0050537e0c11470348add6553252bcf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_select</name>
      <anchorfile>group__core__bitops_ga83c87079ec3aa4037974b9a319aa3c5a.html</anchorfile>
      <anchor>ga83c87079ec3aa4037974b9a319aa3c5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_set</name>
      <anchorfile>group__core__bitops_ga2582766c752f3b2cff7650c511711aaa.html</anchorfile>
      <anchor>ga2582766c752f3b2cff7650c511711aaa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_shl</name>
      <anchorfile>group__core__bitops_gad35ee755a985994eb93b8dde1fac8a09.html</anchorfile>
      <anchor>gad35ee755a985994eb93b8dde1fac8a09</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_shr</name>
      <anchorfile>group__core__bitops_gafca1861f7d0524b057e04d120df08aff.html</anchorfile>
      <anchor>gafca1861f7d0524b057e04d120df08aff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_swap_adjacent</name>
      <anchorfile>group__core__bitops_ga848f5d866de05cbb3c51b2efb8a6d6f5.html</anchorfile>
      <anchor>ga848f5d866de05cbb3c51b2efb8a6d6f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_swap_pairs</name>
      <anchorfile>group__core__bitops_ga4cbb358e89585c3c8d97d0f06871237d.html</anchorfile>
      <anchor>ga4cbb358e89585c3c8d97d0f06871237d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_ternary</name>
      <anchorfile>group__core__bitops_gadbcf7304c34de136c4c62b68ceaa19cb.html</anchorfile>
      <anchor>gadbcf7304c34de136c4c62b68ceaa19cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_unset</name>
      <anchorfile>group__core__bitops_ga597af6519e08a7019c10310ec3c722c2.html</anchorfile>
      <anchor>ga597af6519e08a7019c10310ec3c722c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_width</name>
      <anchorfile>group__core__bitops_ga82d1cef2e8de85d04ae37cca2fe43759.html</anchorfile>
      <anchor>ga82d1cef2e8de85d04ae37cca2fe43759</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bit_xor</name>
      <anchorfile>group__core__bitops_ga6c8a73d644a582b4684e31c5239e4529.html</anchorfile>
      <anchor>ga6c8a73d644a582b4684e31c5239e4529</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>bitofsign</name>
      <anchorfile>group__core__internal_gae174caf55fb3f276410b94f3b7c5dbfb.html</anchorfile>
      <anchor>gae174caf55fb3f276410b94f3b7c5dbfb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>broadcast</name>
      <anchorfile>group__core__simd_ga0f764f21419f124e1e29c15718520a16.html</anchorfile>
      <anchor>ga0f764f21419f124e1e29c15718520a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr callable_broadcast_group_</type>
      <name>broadcast_group</name>
      <anchorfile>group__core__simd_ga843fbb36980a16f585f8e727da3a8f96.html</anchorfile>
      <anchor>ga843fbb36980a16f585f8e727da3a8f96</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>byte_reverse</name>
      <anchorfile>group__core__bitops_gab21caf2aeece0c2486bd80d7e5d9dc2c.html</anchorfile>
      <anchor>gab21caf2aeece0c2486bd80d7e5d9dc2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>byte_swap_adjacent</name>
      <anchorfile>group__core__bitops_ga26b08595fa85a206ed5bd09848338f55.html</anchorfile>
      <anchor>ga26b08595fa85a206ed5bd09848338f55</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>byte_swap_pairs</name>
      <anchorfile>group__core__bitops_ga030e462fe0a8e9815b08326264d106bd.html</anchorfile>
      <anchor>ga030e462fe0a8e9815b08326264d106bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ceil</name>
      <anchorfile>group__core__arithmetic_gaf450959dd53738dda62b4f4551cd7c11.html</anchorfile>
      <anchor>gaf450959dd53738dda62b4f4551cd7c11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>chi</name>
      <anchorfile>group__core__arithmetic_ga57f7296a0ce7eb3ef1ef0575aee93063.html</anchorfile>
      <anchor>ga57f7296a0ce7eb3ef1ef0575aee93063</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>clamp</name>
      <anchorfile>group__core__arithmetic_ga615259a38bc942276fe618e6621d536b.html</anchorfile>
      <anchor>ga615259a38bc942276fe618e6621d536b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>combine</name>
      <anchorfile>group__core__simd_gaa40b2ed752ac083e7336bfcfb216545a.html</anchorfile>
      <anchor>gaa40b2ed752ac083e7336bfcfb216545a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>compare_absolute</name>
      <anchorfile>group__core__predicates_ga583d31b3efe53ae6fb8bf505254fe9a6.html</anchorfile>
      <anchor>ga583d31b3efe53ae6fb8bf505254fe9a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>convert</name>
      <anchorfile>group__core__conversions_gaa346ad56036f22b3571c873b7ae5bebd.html</anchorfile>
      <anchor>gaa346ad56036f22b3571c873b7ae5bebd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>copysign</name>
      <anchorfile>group__core__arithmetic_ga8e000c8aaa19e94b4dd1f84d5191e8a4.html</anchorfile>
      <anchor>ga8e000c8aaa19e94b4dd1f84d5191e8a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cosine_similarity</name>
      <anchorfile>group__core__arithmetic_gae42f1e89f46871950b9ec3175b3f0015.html</anchorfile>
      <anchor>gae42f1e89f46871950b9ec3175b3f0015</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>count_true</name>
      <anchorfile>group__core__reduction_gaee97bf40ee1dcb8f3cd2477faec994cc.html</anchorfile>
      <anchor>gaee97bf40ee1dcb8f3cd2477faec994cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>countl_one</name>
      <anchorfile>group__core__bitops_ga987af1c5145d33608dbbac832278d990.html</anchorfile>
      <anchor>ga987af1c5145d33608dbbac832278d990</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>countl_zero</name>
      <anchorfile>group__core__bitops_ga13f2d665c65670451c8e6b682bbd4430.html</anchorfile>
      <anchor>ga13f2d665c65670451c8e6b682bbd4430</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>countr_one</name>
      <anchorfile>group__core__bitops_ga7e569a2aab386aa1260facc3f91bbaff.html</anchorfile>
      <anchor>ga7e569a2aab386aa1260facc3f91bbaff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>countr_zero</name>
      <anchorfile>group__core__bitops_ga6d1332c0e797bcc8980f62da2b781edb.html</anchorfile>
      <anchor>ga6d1332c0e797bcc8980f62da2b781edb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>covariance</name>
      <anchorfile>group__core__arithmetic_gad85b8e8aca48a5e1db5ada47d8300950.html</anchorfile>
      <anchor>gad85b8e8aca48a5e1db5ada47d8300950</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cumfun</name>
      <anchorfile>group__core__arithmetic_ga20f1f4d4503b8bdb9ce9aa854fde697f.html</anchorfile>
      <anchor>ga20f1f4d4503b8bdb9ce9aa854fde697f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cumprod</name>
      <anchorfile>group__core__arithmetic_ga54ac3f9e05632d33033e149d784627f1.html</anchorfile>
      <anchor>ga54ac3f9e05632d33033e149d784627f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cumsum</name>
      <anchorfile>group__core__arithmetic_ga6e39a9b0ba3dd0581d60a537c0b09e5e.html</anchorfile>
      <anchor>ga6e39a9b0ba3dd0581d60a537c0b09e5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cumtrapz</name>
      <anchorfile>group__core__arithmetic_ga7f3104b5fdabcc5a06157c869cb4cfc1.html</anchorfile>
      <anchor>ga7f3104b5fdabcc5a06157c869cb4cfc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>dec</name>
      <anchorfile>group__core__arithmetic_ga44e2186aecde5f17445b39043094d85d.html</anchorfile>
      <anchor>ga44e2186aecde5f17445b39043094d85d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr callable_deinterleave_groups_</type>
      <name>deinterleave_groups</name>
      <anchorfile>group__core_ga5c2b47962e4523e5ca348a7e3034032b.html</anchorfile>
      <anchor>ga5c2b47962e4523e5ca348a7e3034032b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr callable_deinterleave_groups_shuffle_</type>
      <name>deinterleave_groups_shuffle</name>
      <anchorfile>group__core__simd_ga275315d7cc9b3cd8f5e063136d4990d1.html</anchorfile>
      <anchor>ga275315d7cc9b3cd8f5e063136d4990d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>diff</name>
      <anchorfile>group__core__arithmetic_ga057eabc3676fe1e9370bd201a21e97d7.html</anchorfile>
      <anchor>ga057eabc3676fe1e9370bd201a21e97d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>diff_of_prod</name>
      <anchorfile>group__core__accuracy_gab21bf1ebf628243f28a10f05ce66f820.html</anchorfile>
      <anchor>gab21bf1ebf628243f28a10f05ce66f820</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>dist</name>
      <anchorfile>group__core__arithmetic_ga0278a079dfdeb50fcb31e27b3ac191f9.html</anchorfile>
      <anchor>ga0278a079dfdeb50fcb31e27b3ac191f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>div</name>
      <anchorfile>group__core__arithmetic_gaf14eacd69db8a64fecf63346475c37fb.html</anchorfile>
      <anchor>gaf14eacd69db8a64fecf63346475c37fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>dot</name>
      <anchorfile>group__core__arithmetic_ga9629bc8a3ce2a95e45bd49e118605156.html</anchorfile>
      <anchor>ga9629bc8a3ce2a95e45bd49e118605156</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>epsilon</name>
      <anchorfile>group__core__fma__internal_ga331b89f386f0ee1b5b8fe337383df088.html</anchorfile>
      <anchor>ga331b89f386f0ee1b5b8fe337383df088</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>exponent</name>
      <anchorfile>group__core__internal_ga0c0d48cc3ee880fde5b8ec3e874933d0.html</anchorfile>
      <anchor>ga0c0d48cc3ee880fde5b8ec3e874933d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fam</name>
      <anchorfile>group__core__fma__family_gad4cb975104900d0011e273b1c0cd8015.html</anchorfile>
      <anchor>gad4cb975104900d0011e273b1c0cd8015</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fanm</name>
      <anchorfile>group__core__fma__family_ga6dae56ba4247691094d46c4451e87012.html</anchorfile>
      <anchor>ga6dae56ba4247691094d46c4451e87012</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fdim</name>
      <anchorfile>group__core__arithmetic_ga6771e04ebcea3881df31805cedc97936.html</anchorfile>
      <anchor>ga6771e04ebcea3881df31805cedc97936</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>first_true</name>
      <anchorfile>group__core__reduction_ga146ea89681f9d926afcc7b3bf968f40d.html</anchorfile>
      <anchor>ga146ea89681f9d926afcc7b3bf968f40d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>firstbitset</name>
      <anchorfile>group__core__bitops_gafd77ecd10dc25572885742db87361954.html</anchorfile>
      <anchor>gafd77ecd10dc25572885742db87361954</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>firstbitunset</name>
      <anchorfile>group__core__bitops_gafbcb9ca39f89d47f3fe847e1f3fdf3fa.html</anchorfile>
      <anchor>gafbcb9ca39f89d47f3fe847e1f3fdf3fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>floor</name>
      <anchorfile>group__core__arithmetic_gad11a9abc8d039fa20ad0b7c1f307133d.html</anchorfile>
      <anchor>gad11a9abc8d039fa20ad0b7c1f307133d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>flush_denormal</name>
      <anchorfile>group__core__internal_ga114b52fbcd864d4005d819c0e1cde554.html</anchorfile>
      <anchor>ga114b52fbcd864d4005d819c0e1cde554</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fma</name>
      <anchorfile>group__core__fma__family_gae79b56378eacf4c4f3b3d7e128facb07.html</anchorfile>
      <anchor>gae79b56378eacf4c4f3b3d7e128facb07</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fmod</name>
      <anchorfile>group__core__arithmetic_ga8708102003ee2323f6bb449cc4f00384.html</anchorfile>
      <anchor>ga8708102003ee2323f6bb449cc4f00384</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fms</name>
      <anchorfile>group__core__fma__family_ga92b3e10cb0fda10eec419cb96378a5f5.html</anchorfile>
      <anchor>ga92b3e10cb0fda10eec419cb96378a5f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fnma</name>
      <anchorfile>group__core__fma__family_ga96c956f8bef9246e2652ca40c3e428d9.html</anchorfile>
      <anchor>ga96c956f8bef9246e2652ca40c3e428d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fnms</name>
      <anchorfile>group__core__fma__family_gab356e39b49a8aed2b5e5f02a2cc392cc.html</anchorfile>
      <anchor>gab356e39b49a8aed2b5e5f02a2cc392cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>frac</name>
      <anchorfile>group__core__arithmetic_ga853653c494446e7321ec6bcc4e229bef.html</anchorfile>
      <anchor>ga853653c494446e7321ec6bcc4e229bef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fracscale</name>
      <anchorfile>group__core__arithmetic_ga5c93230a3df7577707f9fbe32e470e37.html</anchorfile>
      <anchor>ga5c93230a3df7577707f9fbe32e470e37</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fsm</name>
      <anchorfile>group__core__fma__family_ga6387fe7304980f8112f867f5710af925.html</anchorfile>
      <anchor>ga6387fe7304980f8112f867f5710af925</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fsnm</name>
      <anchorfile>group__core__fma__family_ga67d686700aac348f3d75484f38c63d4d.html</anchorfile>
      <anchor>ga67d686700aac348f3d75484f38c63d4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>gather</name>
      <anchorfile>group__core__simd_ga3cbe6596b8e7ca4d4d0611ac642fcf39.html</anchorfile>
      <anchor>ga3cbe6596b8e7ca4d4d0611ac642fcf39</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>has_equal_in</name>
      <anchorfile>group__core__simd_ga517f6b01fca5124ed352087830a713d4.html</anchorfile>
      <anchor>ga517f6b01fca5124ed352087830a713d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>heaviside</name>
      <anchorfile>group__core__arithmetic_ga961f3ecc560ee5d2bcabfe4dd63519d6.html</anchorfile>
      <anchor>ga961f3ecc560ee5d2bcabfe4dd63519d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>hi</name>
      <anchorfile>group__core__bitops_gac36375f33a27d2122d4ca0f3a006f7b2.html</anchorfile>
      <anchor>gac36375f33a27d2122d4ca0f3a006f7b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>if_else</name>
      <anchorfile>group__core__logical_ga4883faa71d1b0e8eaea97fe7cc00b0a8.html</anchorfile>
      <anchor>ga4883faa71d1b0e8eaea97fe7cc00b0a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ifrexp</name>
      <anchorfile>group__core__internal_ga6b68a3922d5bb6703692878a71fbcba8.html</anchorfile>
      <anchor>ga6b68a3922d5bb6703692878a71fbcba8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ilogb</name>
      <anchorfile>group__core__internal_ga7f152bb26aee4fe8157db6c9ec25a64c.html</anchorfile>
      <anchor>ga7f152bb26aee4fe8157db6c9ec25a64c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>inc</name>
      <anchorfile>group__core__arithmetic_ga286feea728eff1a17edeb307b2aeab54.html</anchorfile>
      <anchor>ga286feea728eff1a17edeb307b2aeab54</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_bit_equal</name>
      <anchorfile>group__core__predicates_ga6ec822af7cd03bc7d854a4dad197fda1.html</anchorfile>
      <anchor>ga6ec822af7cd03bc7d854a4dad197fda1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_denormal</name>
      <anchorfile>group__core__predicates_ga514f4eb86f8ab1d6921c9b9ec974c0c4.html</anchorfile>
      <anchor>ga514f4eb86f8ab1d6921c9b9ec974c0c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_eqmz</name>
      <anchorfile>group__core__predicates_ga4c4e922dbc6bdd8e8f9e32eb9d352f76.html</anchorfile>
      <anchor>ga4c4e922dbc6bdd8e8f9e32eb9d352f76</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_eqpz</name>
      <anchorfile>group__core__predicates_ga1f015f87084e3b69efd93498aa2748f1.html</anchorfile>
      <anchor>ga1f015f87084e3b69efd93498aa2748f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_equal</name>
      <anchorfile>group__core__predicates_ga3d2da74d0f6d2327e8dfd4cc109a96b0.html</anchorfile>
      <anchor>ga3d2da74d0f6d2327e8dfd4cc109a96b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_eqz</name>
      <anchorfile>group__core__predicates_gac37d952274c06577a586a75c1f02f33e.html</anchorfile>
      <anchor>gac37d952274c06577a586a75c1f02f33e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_even</name>
      <anchorfile>group__core__predicates_gae52c8a1138e8e9b6da4c0fa568d1d9db.html</anchorfile>
      <anchor>gae52c8a1138e8e9b6da4c0fa568d1d9db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_finite</name>
      <anchorfile>group__core__predicates_ga2caa5fbf925de49ed293175bf493ef9e.html</anchorfile>
      <anchor>ga2caa5fbf925de49ed293175bf493ef9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_flint</name>
      <anchorfile>group__core__predicates_gadd0f931bda75c70a85f70f88c4e4b097.html</anchorfile>
      <anchor>gadd0f931bda75c70a85f70f88c4e4b097</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_gez</name>
      <anchorfile>group__core__predicates_ga580a69727d6d7f6d372eadca43c7f86e.html</anchorfile>
      <anchor>ga580a69727d6d7f6d372eadca43c7f86e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_greater</name>
      <anchorfile>group__core__predicates_ga4506c0d18d8f4bb96a2cc5abaf6a1b5a.html</anchorfile>
      <anchor>ga4506c0d18d8f4bb96a2cc5abaf6a1b5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_greater_equal</name>
      <anchorfile>group__core__predicates_gab91adbe8dd46741068ca460ba873e976.html</anchorfile>
      <anchor>gab91adbe8dd46741068ca460ba873e976</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_gtz</name>
      <anchorfile>group__core__predicates_ga2d321e392856f49b230e9cba211b517d.html</anchorfile>
      <anchor>ga2d321e392856f49b230e9cba211b517d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_infinite</name>
      <anchorfile>group__core__predicates_ga1e2cf3b5bed23375e108126c92ca7ec3.html</anchorfile>
      <anchor>ga1e2cf3b5bed23375e108126c92ca7ec3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_less</name>
      <anchorfile>group__core__predicates_ga7dd417908ae322f8f3ef9a16779ee63f.html</anchorfile>
      <anchor>ga7dd417908ae322f8f3ef9a16779ee63f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_less_equal</name>
      <anchorfile>group__core__predicates_ga9344864ee9268d43aa1e8defdfd292c3.html</anchorfile>
      <anchor>ga9344864ee9268d43aa1e8defdfd292c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_lessgreater</name>
      <anchorfile>group__core__predicates_ga46f7779bc0bc962904db287b4f356f55.html</anchorfile>
      <anchor>ga46f7779bc0bc962904db287b4f356f55</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_lez</name>
      <anchorfile>group__core__predicates_gaceb6deba8172c276ce8444224ef5b7ef.html</anchorfile>
      <anchor>gaceb6deba8172c276ce8444224ef5b7ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_ltz</name>
      <anchorfile>group__core__predicates_ga7671d935e3e1036b64c20aa1e58c9177.html</anchorfile>
      <anchor>ga7671d935e3e1036b64c20aa1e58c9177</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_minf</name>
      <anchorfile>group__core__predicates_ga553ea3bc7c8408ff19b87aec1d03a651.html</anchorfile>
      <anchor>ga553ea3bc7c8408ff19b87aec1d03a651</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_nan</name>
      <anchorfile>group__core__predicates_gaa9f5fcd9c22232d6bef49e308c6df357.html</anchorfile>
      <anchor>gaa9f5fcd9c22232d6bef49e308c6df357</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_negative</name>
      <anchorfile>group__core__predicates_gae28d45c4c5af89e0f3ad48191e63c80e.html</anchorfile>
      <anchor>gae28d45c4c5af89e0f3ad48191e63c80e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_nemz</name>
      <anchorfile>group__core__predicates_ga9b8f733fd01e02e1ff6e47bbc1e17011.html</anchorfile>
      <anchor>ga9b8f733fd01e02e1ff6e47bbc1e17011</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_nepz</name>
      <anchorfile>group__core__predicates_ga978c7ce937b0b6a5e9bd45c19d601928.html</anchorfile>
      <anchor>ga978c7ce937b0b6a5e9bd45c19d601928</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_nez</name>
      <anchorfile>group__core__predicates_gac0b0097d6ffbd2e47b39aae1ac6ca23a.html</anchorfile>
      <anchor>gac0b0097d6ffbd2e47b39aae1ac6ca23a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_ngez</name>
      <anchorfile>group__core__predicates_ga7a8456291e3dc2fe427dbc92a750b706.html</anchorfile>
      <anchor>ga7a8456291e3dc2fe427dbc92a750b706</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_ngtz</name>
      <anchorfile>group__core__predicates_ga972fa009bc9fca501f81d392640e590b.html</anchorfile>
      <anchor>ga972fa009bc9fca501f81d392640e590b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_nlez</name>
      <anchorfile>group__core__predicates_gaf04a54efc3842831e52cbded6ff0dd40.html</anchorfile>
      <anchor>gaf04a54efc3842831e52cbded6ff0dd40</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_nltz</name>
      <anchorfile>group__core__predicates_ga255d9a4c467d32979093166a602b22cb.html</anchorfile>
      <anchor>ga255d9a4c467d32979093166a602b22cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_normal</name>
      <anchorfile>group__core__predicates_ga5e2bc26739efdc174f39bf038e13722e.html</anchorfile>
      <anchor>ga5e2bc26739efdc174f39bf038e13722e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_denormal</name>
      <anchorfile>group__core__predicates_ga43711d74c94b96ed6033d864a8941a35.html</anchorfile>
      <anchor>ga43711d74c94b96ed6033d864a8941a35</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_equal</name>
      <anchorfile>group__core__predicates_ga005f052be0bb62e30b57c344c3b2fb73.html</anchorfile>
      <anchor>ga005f052be0bb62e30b57c344c3b2fb73</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_finite</name>
      <anchorfile>group__core__predicates_ga56235829fa196aeff4b505402e73134a.html</anchorfile>
      <anchor>ga56235829fa196aeff4b505402e73134a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_flint</name>
      <anchorfile>group__core__predicates_ga297e673a2c4cfaa8becfa5391cef1653.html</anchorfile>
      <anchor>ga297e673a2c4cfaa8becfa5391cef1653</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_greater</name>
      <anchorfile>group__core__predicates_ga65a064e86c209d9dae346b39aa4495da.html</anchorfile>
      <anchor>ga65a064e86c209d9dae346b39aa4495da</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_greater_equal</name>
      <anchorfile>group__core__predicates_gad179ebf1cd63eb9b50b27a56a8102977.html</anchorfile>
      <anchor>gad179ebf1cd63eb9b50b27a56a8102977</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_infinite</name>
      <anchorfile>group__core__predicates_ga00207423a3f94e5f718e277d3bc1af60.html</anchorfile>
      <anchor>ga00207423a3f94e5f718e277d3bc1af60</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_less</name>
      <anchorfile>group__core__predicates_gaccd4f24060de6bb1e4d3f4e3ddb3e2db.html</anchorfile>
      <anchor>gaccd4f24060de6bb1e4d3f4e3ddb3e2db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_less_equal</name>
      <anchorfile>group__core__predicates_gad33a8c5bdcad7a64e7cd444382c0a423.html</anchorfile>
      <anchor>gad33a8c5bdcad7a64e7cd444382c0a423</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_nan</name>
      <anchorfile>group__core__predicates_ga8a2c95ffd0596f82eed78b2d006eca53.html</anchorfile>
      <anchor>ga8a2c95ffd0596f82eed78b2d006eca53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_odd</name>
      <anchorfile>group__core__predicates_gac4734a17484558619109e9728463636d.html</anchorfile>
      <anchor>gac4734a17484558619109e9728463636d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_ordered</name>
      <anchorfile>group__core__predicates_ga708d743aa5bd73579b85d7cbe23fcb51.html</anchorfile>
      <anchor>ga708d743aa5bd73579b85d7cbe23fcb51</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_pinf</name>
      <anchorfile>group__core__predicates_gaefc265e877011d473280abd9e3874e03.html</anchorfile>
      <anchor>gaefc265e877011d473280abd9e3874e03</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_positive</name>
      <anchorfile>group__core__predicates_ga7f5eb7e1557f2613b3e9691fbdce1c32.html</anchorfile>
      <anchor>ga7f5eb7e1557f2613b3e9691fbdce1c32</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_pow2</name>
      <anchorfile>group__core__predicates_gaa700138e1f2eaf422ccf4e108ad159bb.html</anchorfile>
      <anchor>gaa700138e1f2eaf422ccf4e108ad159bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_unit</name>
      <anchorfile>group__core__predicates_ga55a97aa36ad10be2e0f6f31584df7bb6.html</anchorfile>
      <anchor>ga55a97aa36ad10be2e0f6f31584df7bb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_unordered</name>
      <anchorfile>group__core__predicates_gaba27d3ee71282f573b094255e7d24c59.html</anchorfile>
      <anchor>gaba27d3ee71282f573b094255e7d24c59</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>iterate_selected</name>
      <anchorfile>group__core__simd_ga48cbc739f85673ad20ccc29debcb2183.html</anchorfile>
      <anchor>ga48cbc739f85673ad20ccc29debcb2183</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>last_true</name>
      <anchorfile>group__core__reduction_gabc10fff649535870a897cef2a1e1673e.html</anchorfile>
      <anchor>gabc10fff649535870a897cef2a1e1673e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ldexp</name>
      <anchorfile>group__core__internal_ga9d262f5be47d761c18d548c04cda7c8f.html</anchorfile>
      <anchor>ga9d262f5be47d761c18d548c04cda7c8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lerp</name>
      <anchorfile>group__core__arithmetic_ga251fc4447bfae16b155723a7ba52b7ee.html</anchorfile>
      <anchor>ga251fc4447bfae16b155723a7ba52b7ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lo</name>
      <anchorfile>group__core__bitops_ga61fa2a64540198462d0aed12e93967a1.html</anchorfile>
      <anchor>ga61fa2a64540198462d0aed12e93967a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>load</name>
      <anchorfile>group__simd_gac2eed14dbdfb4cf1b36d157e27825cba.html</anchorfile>
      <anchor>gac2eed14dbdfb4cf1b36d157e27825cba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>logical_and</name>
      <anchorfile>group__core__logical_gac4b0a0de4e227615b5514f739e478a50.html</anchorfile>
      <anchor>gac4b0a0de4e227615b5514f739e478a50</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>logical_andnot</name>
      <anchorfile>group__core__logical_gaa46d435f0a6b06b058e106e37cc1cb29.html</anchorfile>
      <anchor>gaa46d435f0a6b06b058e106e37cc1cb29</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>logical_not</name>
      <anchorfile>group__core__logical_ga5da44a758a10d4d4419fd3df1a4f90e6.html</anchorfile>
      <anchor>ga5da44a758a10d4d4419fd3df1a4f90e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>logical_notand</name>
      <anchorfile>group__core__logical_gadaf632f20d2d6fc4e406459acbf53bb2.html</anchorfile>
      <anchor>gadaf632f20d2d6fc4e406459acbf53bb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>logical_notor</name>
      <anchorfile>group__core__logical_ga0a6fef84dca69e378253433e2b31f647.html</anchorfile>
      <anchor>ga0a6fef84dca69e378253433e2b31f647</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>logical_or</name>
      <anchorfile>group__core__logical_ga4a287385b8f9c1d91c1523bc36ef35a6.html</anchorfile>
      <anchor>ga4a287385b8f9c1d91c1523bc36ef35a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>logical_ornot</name>
      <anchorfile>group__core__logical_gac904b8dce17c980bd3542af1cd6cb875.html</anchorfile>
      <anchor>gac904b8dce17c980bd3542af1cd6cb875</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>logical_xor</name>
      <anchorfile>group__core__logical_ga4681644b17aaa0a3ca3d0f6967d8513e.html</anchorfile>
      <anchor>ga4681644b17aaa0a3ca3d0f6967d8513e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lohi</name>
      <anchorfile>group__core__bitops_gaaf5061a57a817fcd65de7dc459bd465b.html</anchorfile>
      <anchor>gaaf5061a57a817fcd65de7dc459bd465b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>manhattan</name>
      <anchorfile>group__core__arithmetic_ga38a5508b78008f2f5bd66008b5b0a60f.html</anchorfile>
      <anchor>ga38a5508b78008f2f5bd66008b5b0a60f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>mantissa</name>
      <anchorfile>group__core__internal_ga33c3958f43208dc6ffa54acdd33cf8c0.html</anchorfile>
      <anchor>ga33c3958f43208dc6ffa54acdd33cf8c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>max</name>
      <anchorfile>group__core__arithmetic_ga208ca607f968474fa9e4d016e0eb4e5f.html</anchorfile>
      <anchor>ga208ca607f968474fa9e4d016e0eb4e5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>maxabs</name>
      <anchorfile>group__core__arithmetic_ga93a4c90ace3fd4450ac5a3a6fe9004f1.html</anchorfile>
      <anchor>ga93a4c90ace3fd4450ac5a3a6fe9004f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>maximum</name>
      <anchorfile>group__core__reduction_gaf7f045ef2ed35833e8c3dc0228de48b8.html</anchorfile>
      <anchor>gaf7f045ef2ed35833e8c3dc0228de48b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>maxmag</name>
      <anchorfile>group__core__arithmetic_gadebe5f60fa3f0943b1deb3a58cea39f0.html</anchorfile>
      <anchor>gadebe5f60fa3f0943b1deb3a58cea39f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>min</name>
      <anchorfile>group__core__arithmetic_ga11d112beae386b529269a6ba2eb02471.html</anchorfile>
      <anchor>ga11d112beae386b529269a6ba2eb02471</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minabs</name>
      <anchorfile>group__core__arithmetic_ga73f4a496ba999b5d065a0c21aaad0a04.html</anchorfile>
      <anchor>ga73f4a496ba999b5d065a0c21aaad0a04</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minimum</name>
      <anchorfile>group__core__reduction_ga729853eb0b9c9f168dd104b1df7a8ec8.html</anchorfile>
      <anchor>ga729853eb0b9c9f168dd104b1df7a8ec8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minmag</name>
      <anchorfile>group__core__arithmetic_ga92cce254fcde7c4d9a7a55d320b6b3e9.html</anchorfile>
      <anchor>ga92cce254fcde7c4d9a7a55d320b6b3e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minmax</name>
      <anchorfile>group__core__arithmetic_gab5afa8e5630450ad2ab117f96535356e.html</anchorfile>
      <anchor>gab5afa8e5630450ad2ab117f96535356e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>modf</name>
      <anchorfile>group__core__arithmetic_gaec55902ec0dd1ce8ec09bcda822dac81.html</anchorfile>
      <anchor>gaec55902ec0dd1ce8ec09bcda822dac81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>mul</name>
      <anchorfile>group__core__arithmetic_ga19c1e5e8e7a04678ee99fdc2bbff0e7b.html</anchorfile>
      <anchor>ga19c1e5e8e7a04678ee99fdc2bbff0e7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>nb_values</name>
      <anchorfile>group__core__internal_ga6a445739414b920ec65978c6bbc5b315.html</anchorfile>
      <anchor>ga6a445739414b920ec65978c6bbc5b315</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>negabsmax</name>
      <anchorfile>group__core__arithmetic_ga56d748dd6c74b235bc2aaad77391c9ac.html</anchorfile>
      <anchor>ga56d748dd6c74b235bc2aaad77391c9ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>negabsmin</name>
      <anchorfile>group__core__arithmetic_gabe2d9f7bc95472170c85bd1e9437cb45.html</anchorfile>
      <anchor>gabe2d9f7bc95472170c85bd1e9437cb45</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>negate</name>
      <anchorfile>group__core__arithmetic_ga204db0b8c77052a8a3eadc039abb2e73.html</anchorfile>
      <anchor>ga204db0b8c77052a8a3eadc039abb2e73</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>negatenz</name>
      <anchorfile>group__core__arithmetic_ga250e72507a1740ed75af67f72fc47d90.html</anchorfile>
      <anchor>ga250e72507a1740ed75af67f72fc47d90</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>negmaxabs</name>
      <anchorfile>group__core__arithmetic_ga7ab645c942cb4745b4f50947e2526527.html</anchorfile>
      <anchor>ga7ab645c942cb4745b4f50947e2526527</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>negminabs</name>
      <anchorfile>group__core__arithmetic_gabcdcf0169de90c64260492e8d2300bde.html</anchorfile>
      <anchor>gabcdcf0169de90c64260492e8d2300bde</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>next</name>
      <anchorfile>group__core__internal_gad1c0d7b11ba73f9ea7f39864166d7fb4.html</anchorfile>
      <anchor>gad1c0d7b11ba73f9ea7f39864166d7fb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>nextafter</name>
      <anchorfile>group__core__internal_ga3b419a68a0b99756c3138528b7db9941.html</anchorfile>
      <anchor>ga3b419a68a0b99756c3138528b7db9941</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>nextint</name>
      <anchorfile>group__core__internal_gac2a2df9c3159d70e5e580c008fdeb66c.html</anchorfile>
      <anchor>gac2a2df9c3159d70e5e580c008fdeb66c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>none</name>
      <anchorfile>group__core__reduction_ga6c3f7d70fe96da70a69c2139a7c325ea.html</anchorfile>
      <anchor>ga6c3f7d70fe96da70a69c2139a7c325ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>of_class</name>
      <anchorfile>group__core__internal_ga056f305b9a8385ae40ee917d661666f9.html</anchorfile>
      <anchor>ga056f305b9a8385ae40ee917d661666f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>oneminus</name>
      <anchorfile>group__core__arithmetic_ga06d1ba16e6d014da9fb540261012ad76.html</anchorfile>
      <anchor>ga06d1ba16e6d014da9fb540261012ad76</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>popcount</name>
      <anchorfile>group__core__bitops_gaae5db78cfc6d7dbce0141f945d1516d7.html</anchorfile>
      <anchor>gaae5db78cfc6d7dbce0141f945d1516d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>prev</name>
      <anchorfile>group__core__internal_ga5e851835c26e1c3583bf12fe2eea6c23.html</anchorfile>
      <anchor>ga5e851835c26e1c3583bf12fe2eea6c23</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>prevint</name>
      <anchorfile>group__core__internal_ga3ad43aa378eecf62d5b437b320d45d84.html</anchorfile>
      <anchor>ga3ad43aa378eecf62d5b437b320d45d84</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rat</name>
      <anchorfile>group__core__arithmetic_gaaeb43898a1160bf5dd03cb5863075e83.html</anchorfile>
      <anchor>gaaeb43898a1160bf5dd03cb5863075e83</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>read</name>
      <anchorfile>group__memory_ga49de20d14b6d3133b2bc19a95b1af7bd.html</anchorfile>
      <anchor>ga49de20d14b6d3133b2bc19a95b1af7bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rec</name>
      <anchorfile>group__core__arithmetic_ga25aad5d506c66c95818e1839a1855b12.html</anchorfile>
      <anchor>ga25aad5d506c66c95818e1839a1855b12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>reduce</name>
      <anchorfile>group__core__reduction_gaa1ec7a1068d9a82ce9b7bb9d1f9d7f37.html</anchorfile>
      <anchor>gaa1ec7a1068d9a82ce9b7bb9d1f9d7f37</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>reldist</name>
      <anchorfile>group__core__arithmetic_ga1f25877c9ddf62e0062c17f10be721b2.html</anchorfile>
      <anchor>ga1f25877c9ddf62e0062c17f10be721b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rem</name>
      <anchorfile>group__core__arithmetic_ga05a5bad217bfe7393357bece8e5ed056.html</anchorfile>
      <anchor>ga05a5bad217bfe7393357bece8e5ed056</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>remainder</name>
      <anchorfile>group__core__arithmetic_ga9c700f632f4d9140adfa0a52f0582629.html</anchorfile>
      <anchor>ga9c700f632f4d9140adfa0a52f0582629</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>replace_ignored</name>
      <anchorfile>group__core__logical_ga427432fa10542d6737316973309004e4.html</anchorfile>
      <anchor>ga427432fa10542d6737316973309004e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr callable_rotate_</type>
      <name>rotate</name>
      <anchorfile>group__core_ga2b09f7ec6c1c06462052833c3d08cefb.html</anchorfile>
      <anchor>ga2b09f7ec6c1c06462052833c3d08cefb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rotl</name>
      <anchorfile>group__core__bitops_ga4edb8cc8f3593c76c58eb1f5d899ac33.html</anchorfile>
      <anchor>ga4edb8cc8f3593c76c58eb1f5d899ac33</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rotr</name>
      <anchorfile>group__core__bitops_gab9aac42187ea93d7b3d7d1f0c7e45f6a.html</anchorfile>
      <anchor>gab9aac42187ea93d7b3d7d1f0c7e45f6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>round</name>
      <anchorfile>group__core__arithmetic_ga4bdec07dc764fd7a0f883f93ff293bde.html</anchorfile>
      <anchor>ga4bdec07dc764fd7a0f883f93ff293bde</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rshl</name>
      <anchorfile>group__core__bitops_gad18e8c9ab65a31f90fdc12535fca137b.html</anchorfile>
      <anchor>gad18e8c9ab65a31f90fdc12535fca137b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rshr</name>
      <anchorfile>group__core__bitops_ga945a9cad6f4e83840ac6a4e7782af905.html</anchorfile>
      <anchor>ga945a9cad6f4e83840ac6a4e7782af905</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rsqrt</name>
      <anchorfile>group__core__arithmetic_gab38c68359b06e60ef729c35f061aa659.html</anchorfile>
      <anchor>gab38c68359b06e60ef729c35f061aa659</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>safe_scale</name>
      <anchorfile>group__core__accuracy_gad1203df175a5c37630dd175a41b94ae1.html</anchorfile>
      <anchor>gad1203df175a5c37630dd175a41b94ae1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>saturate</name>
      <anchorfile>group__core__arithmetic_ga0a217828149774983e6eb60664ed1330.html</anchorfile>
      <anchor>ga0a217828149774983e6eb60664ed1330</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>scan</name>
      <anchorfile>group__core__simd_gaabc7c256adcf53420136da7f6de66fb7.html</anchorfile>
      <anchor>gaabc7c256adcf53420136da7f6de66fb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>scatter</name>
      <anchorfile>group__core__simd_gaa6b4303cb1ae3c602c51414ba1963161.html</anchorfile>
      <anchor>gaa6b4303cb1ae3c602c51414ba1963161</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>shl</name>
      <anchorfile>group__core__bitops_ga82ed4cebb5bca3c352beda164a91f2e9.html</anchorfile>
      <anchor>ga82ed4cebb5bca3c352beda164a91f2e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>shr</name>
      <anchorfile>group__core__bitops_ga1636e7a14e4a1421521f63cc5d815f8f.html</anchorfile>
      <anchor>ga1636e7a14e4a1421521f63cc5d815f8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sign</name>
      <anchorfile>group__core__arithmetic_ga219d427cb81fa248d0232ef2e91e65e4.html</anchorfile>
      <anchor>ga219d427cb81fa248d0232ef2e91e65e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sign_alternate</name>
      <anchorfile>group__core__arithmetic_ga7bda81fcc77e937ce4bac9801346e574.html</anchorfile>
      <anchor>ga7bda81fcc77e937ce4bac9801346e574</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>signnz</name>
      <anchorfile>group__core__arithmetic_ga58934cd97be4c2c274fdb3965221daa7.html</anchorfile>
      <anchor>ga58934cd97be4c2c274fdb3965221daa7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>simd_cast</name>
      <anchorfile>group__core__conversions_ga4610128f928ca0244050bfdfdf9710c9.html</anchorfile>
      <anchor>ga4610128f928ca0244050bfdfdf9710c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr callable_slide_left_</type>
      <name>slide_left</name>
      <anchorfile>group__core__named__shuffles_ga06f45fd6acf2d0720f511c613fc24ad0.html</anchorfile>
      <anchor>ga06f45fd6acf2d0720f511c613fc24ad0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sort</name>
      <anchorfile>group__core__simd_gafd1cf1dd690536fde5d1a726d437a976.html</anchorfile>
      <anchor>gafd1cf1dd690536fde5d1a726d437a976</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqr</name>
      <anchorfile>group__core__arithmetic_ga044101b90ab7a146067d8cb1f76889eb.html</anchorfile>
      <anchor>ga044101b90ab7a146067d8cb1f76889eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqrt</name>
      <anchorfile>group__core__arithmetic_ga641aa98b8a2c05bf5bfb4907d15faf37.html</anchorfile>
      <anchor>ga641aa98b8a2c05bf5bfb4907d15faf37</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>store</name>
      <anchorfile>group__memory_gad748180639cb9a4e2dbf82e48d986615.html</anchorfile>
      <anchor>gad748180639cb9a4e2dbf82e48d986615</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr callable_store_equivalent_</type>
      <name>store_equivalent</name>
      <anchorfile>group__memory_gad0ad3e63b14261774f8ca2c04503159a.html</anchorfile>
      <anchor>gad0ad3e63b14261774f8ca2c04503159a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sub</name>
      <anchorfile>group__core__arithmetic_ga7392fd608cc6fc3f1626491cd581616d.html</anchorfile>
      <anchor>ga7392fd608cc6fc3f1626491cd581616d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sufp</name>
      <anchorfile>group__core__accuracy_ga86420153c2918b16aee8fa6f4f2d0194.html</anchorfile>
      <anchor>ga86420153c2918b16aee8fa6f4f2d0194</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sulp</name>
      <anchorfile>group__core__accuracy_ga8c7d48b6fe0b1111e63719dc666f9d9c.html</anchorfile>
      <anchor>ga8c7d48b6fe0b1111e63719dc666f9d9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sum_of_prod</name>
      <anchorfile>group__core__accuracy_ga36017626c633cde2a07146d49d9ccbe7.html</anchorfile>
      <anchor>ga36017626c633cde2a07146d49d9ccbe7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sum_of_squares</name>
      <anchorfile>group__core__arithmetic_ga69b984ff64182f743ac046245f284168.html</anchorfile>
      <anchor>ga69b984ff64182f743ac046245f284168</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>swap_pairs</name>
      <anchorfile>group__core__bitops_ga10b54df6fa2ae24f1f0d6334e2c5be1b.html</anchorfile>
      <anchor>ga10b54df6fa2ae24f1f0d6334e2c5be1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>three_fma</name>
      <anchorfile>group__core__accuracy_gabacbafd11abd5e82e49aa6ab394cd10e.html</anchorfile>
      <anchor>gabacbafd11abd5e82e49aa6ab394cd10e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>trunc</name>
      <anchorfile>group__core__arithmetic_ga5ebab1e2407219111f8d3916ad4e6819.html</anchorfile>
      <anchor>ga5ebab1e2407219111f8d3916ad4e6819</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr callable_try_each_group_position_</type>
      <name>try_each_group_position</name>
      <anchorfile>group__core_ga721ccc166a96634b64bb08c83ae7e0ed.html</anchorfile>
      <anchor>ga721ccc166a96634b64bb08c83ae7e0ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>two_add</name>
      <anchorfile>group__core__accuracy_ga3a5c4b16896174afe9e63b05e1f9b011.html</anchorfile>
      <anchor>ga3a5c4b16896174afe9e63b05e1f9b011</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>two_div_approx</name>
      <anchorfile>group__core__accuracy_gadd6ab7f52e4d422e1edddc72e49cda2f.html</anchorfile>
      <anchor>gadd6ab7f52e4d422e1edddc72e49cda2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>two_prod</name>
      <anchorfile>group__core__accuracy_ga255bfbae7d6cf4b43a63d8f834e907b4.html</anchorfile>
      <anchor>ga255bfbae7d6cf4b43a63d8f834e907b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>two_sub</name>
      <anchorfile>group__core__accuracy_ga8e384bfd5e06145bdca49fa9da74cfcd.html</anchorfile>
      <anchor>ga8e384bfd5e06145bdca49fa9da74cfcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ulpdist</name>
      <anchorfile>group__core__internal_ga5b73df953d6c6313eeae28925eb8f19c.html</anchorfile>
      <anchor>ga5b73df953d6c6313eeae28925eb8f19c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>unalign</name>
      <anchorfile>group__memory_ga62462e7b23d8d092781d5561a9d4c90f.html</anchorfile>
      <anchor>ga62462e7b23d8d092781d5561a9d4c90f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>unfold</name>
      <anchorfile>group__core__arithmetic_gab00b0403241b47b4e0a7f3e2d8be4cfd.html</anchorfile>
      <anchor>gab00b0403241b47b4e0a7f3e2d8be4cfd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>variance</name>
      <anchorfile>group__core__arithmetic_ga28cc50956bdc395bb00ecef16bebb59d.html</anchorfile>
      <anchor>ga28cc50956bdc395bb00ecef16bebb59d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>veltkamp</name>
      <anchorfile>group__core__accuracy_ga9234fd48e496db5dd743b5494a4a932d.html</anchorfile>
      <anchor>ga9234fd48e496db5dd743b5494a4a932d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>welford_covariance</name>
      <anchorfile>group__core__arithmetic_ga3fee14a8a396f4ac89e650e0fb0768f7.html</anchorfile>
      <anchor>ga3fee14a8a396f4ac89e650e0fb0768f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>welford_variance</name>
      <anchorfile>group__core__arithmetic_ga6cfd55c36f3ce4f4137aa7b14f74f5ce.html</anchorfile>
      <anchor>ga6cfd55c36f3ce4f4137aa7b14f74f5ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>write</name>
      <anchorfile>group__memory_gad32771ddeb3886065ba659298a50e125.html</anchorfile>
      <anchor>gad32771ddeb3886065ba659298a50e125</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>zip</name>
      <anchorfile>group__core__simd_ga35f397f99a9981ec14e2d162ce530ee9.html</anchorfile>
      <anchor>ga35f397f99a9981ec14e2d162ce530ee9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ellint_1</name>
      <anchorfile>group__elliptic_ga5f26f3d8d4aff93caff34f769d0a598a.html</anchorfile>
      <anchor>ga5f26f3d8d4aff93caff34f769d0a598a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ellint_d</name>
      <anchorfile>group__elliptic_ga865feb1e7d9a99be2bb8d17153606adf.html</anchorfile>
      <anchor>ga865feb1e7d9a99be2bb8d17153606adf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ellint_fe</name>
      <anchorfile>group__elliptic_ga9f3e72aeb0f119dc9cf880628a4b9557.html</anchorfile>
      <anchor>ga9f3e72aeb0f119dc9cf880628a4b9557</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ellint_rc</name>
      <anchorfile>group__elliptic_gacca6a0474300efc2cd1907c70b1d6f67.html</anchorfile>
      <anchor>gacca6a0474300efc2cd1907c70b1d6f67</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ellint_rd</name>
      <anchorfile>group__elliptic_gad55c7d3040b1eb8469a3fa17e79396e1.html</anchorfile>
      <anchor>gad55c7d3040b1eb8469a3fa17e79396e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ellint_rf</name>
      <anchorfile>group__elliptic_ga72b982adb94e9f25bbe3e4badc1dd0ee.html</anchorfile>
      <anchor>ga72b982adb94e9f25bbe3e4badc1dd0ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ellint_rg</name>
      <anchorfile>group__elliptic_ga276983e7975e461a199c32ce5eb97a44.html</anchorfile>
      <anchor>ga276983e7975e461a199c32ce5eb97a44</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ellint_rj</name>
      <anchorfile>group__elliptic_ga65cefaf422775dcd1abbc8929e3f4ed9.html</anchorfile>
      <anchor>ga65cefaf422775dcd1abbc8929e3f4ed9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>heuman_lambda</name>
      <anchorfile>group__elliptic_ga24d1bc66420e69358ebd2eb5ff39bff2.html</anchorfile>
      <anchor>ga24d1bc66420e69358ebd2eb5ff39bff2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>jacobi_elliptic</name>
      <anchorfile>group__elliptic_gaeec8a87b0fc27df584c3ace240a2fda8.html</anchorfile>
      <anchor>gaeec8a87b0fc27df584c3ace240a2fda8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>jacobi_zeta</name>
      <anchorfile>group__elliptic_gaa123505d28500b3ea5216a5b88a5da05.html</anchorfile>
      <anchor>gaa123505d28500b3ea5216a5b88a5da05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>catalan</name>
      <anchorfile>group__math__constants_gac7a7c4180b2ec7b09cf29b961ffe4207.html</anchorfile>
      <anchor>gac7a7c4180b2ec7b09cf29b961ffe4207</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cbrt_pi</name>
      <anchorfile>group__math__constants_gab069af5ddba0ea1f3a03653ba24343db.html</anchorfile>
      <anchor>gab069af5ddba0ea1f3a03653ba24343db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cos_1</name>
      <anchorfile>group__math__constants_gad01a36b3aa434488a6a5dc7497646414.html</anchorfile>
      <anchor>gad01a36b3aa434488a6a5dc7497646414</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cosh_1</name>
      <anchorfile>group__math__constants_ga6589c51da226fced3dad18eb5496d1bd.html</anchorfile>
      <anchor>ga6589c51da226fced3dad18eb5496d1bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>egamma</name>
      <anchorfile>group__math__constants_gaaf04325ae522d9fbd5b8e38fa64093b0.html</anchorfile>
      <anchor>gaaf04325ae522d9fbd5b8e38fa64093b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>egamma_sqr</name>
      <anchorfile>group__math__constants_ga9968fbd2955d1569c6e53ebc59744e72.html</anchorfile>
      <anchor>ga9968fbd2955d1569c6e53ebc59744e72</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>epso_2</name>
      <anchorfile>group__math__constants_gac43f9b9a247aab13dd9cf20b28fc10d8.html</anchorfile>
      <anchor>gac43f9b9a247aab13dd9cf20b28fc10d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>euler</name>
      <anchorfile>group__math__constants_ga7c4605cd6be76809b63a68a1d909a00c.html</anchorfile>
      <anchor>ga7c4605cd6be76809b63a68a1d909a00c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>exp_pi</name>
      <anchorfile>group__math__constants_ga561b96f79786fa99e4e2aaf2e52372e2.html</anchorfile>
      <anchor>ga561b96f79786fa99e4e2aaf2e52372e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>extreme_value_skewness</name>
      <anchorfile>group__math__constants_ga8ba551f79aa6782d07eab6c3d7e0a9db.html</anchorfile>
      <anchor>ga8ba551f79aa6782d07eab6c3d7e0a9db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>four_minus_pi</name>
      <anchorfile>group__math__constants_ga0784bcf60e8fbb5cfb4c3dab0524cb54.html</anchorfile>
      <anchor>ga0784bcf60e8fbb5cfb4c3dab0524cb54</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>four_pio_3</name>
      <anchorfile>group__math__constants_gae304b0433f5cb2914d26d50a4172580b.html</anchorfile>
      <anchor>gae304b0433f5cb2914d26d50a4172580b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>glaisher</name>
      <anchorfile>group__math__constants_ga389fcb593b079afea5381d192593443e.html</anchorfile>
      <anchor>ga389fcb593b079afea5381d192593443e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>inv_2eps</name>
      <anchorfile>group__math__constants_ga1bf4ef37949b047159c2fe76891b2128.html</anchorfile>
      <anchor>ga1bf4ef37949b047159c2fe76891b2128</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>inv_2pi</name>
      <anchorfile>group__math__constants_ga7c2cbb2571a968c8badadff961dad2d6.html</anchorfile>
      <anchor>ga7c2cbb2571a968c8badadff961dad2d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>inv_e</name>
      <anchorfile>group__math__constants_ga60b0ff3b86604d509f59e0ad29e42a21.html</anchorfile>
      <anchor>ga60b0ff3b86604d509f59e0ad29e42a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>inv_egamma</name>
      <anchorfile>group__math__constants_ga0bfad4bd0a9df3a00a657ec8c1127204.html</anchorfile>
      <anchor>ga0bfad4bd0a9df3a00a657ec8c1127204</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>inv_pi</name>
      <anchorfile>group__math__constants_ga031989587324a6dcb910db1cb2f09277.html</anchorfile>
      <anchor>ga031989587324a6dcb910db1cb2f09277</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>invcbrt_pi</name>
      <anchorfile>group__math__constants_gaf3efc2364120e6cfeef1c0ac42f770b7.html</anchorfile>
      <anchor>gaf3efc2364120e6cfeef1c0ac42f770b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>invlog10_2</name>
      <anchorfile>group__math__constants_ga2bee64fb1d01a859a4f5e7fc53f40209.html</anchorfile>
      <anchor>ga2bee64fb1d01a859a4f5e7fc53f40209</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>invlog10_e</name>
      <anchorfile>group__math__constants_ga61bf20009c23f002c671cc0cc455f11d.html</anchorfile>
      <anchor>ga61bf20009c23f002c671cc0cc455f11d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>invlog_10</name>
      <anchorfile>group__math__constants_ga3ec8fc7af4d1061cf26cd3a86fcb2f5b.html</anchorfile>
      <anchor>ga3ec8fc7af4d1061cf26cd3a86fcb2f5b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>invlog_2</name>
      <anchorfile>group__math__constants_ga9ba50324960abc54154061fcdfe2b1cf.html</anchorfile>
      <anchor>ga9ba50324960abc54154061fcdfe2b1cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>invlog_phi</name>
      <anchorfile>group__math__constants_gaefdaed5634b30722880246eded19a349.html</anchorfile>
      <anchor>gaefdaed5634b30722880246eded19a349</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>invsqrt_2</name>
      <anchorfile>group__math__constants_gae881f37b4c6c017454ed2099056e4b75.html</anchorfile>
      <anchor>gae881f37b4c6c017454ed2099056e4b75</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>khinchin</name>
      <anchorfile>group__math__constants_ga0741808f95c071aa804ddb0bd4488558.html</anchorfile>
      <anchor>ga0741808f95c071aa804ddb0bd4488558</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log10_e</name>
      <anchorfile>group__math__constants_ga6572c51acce451620fdfeeb5c450160e.html</anchorfile>
      <anchor>ga6572c51acce451620fdfeeb5c450160e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log2_e</name>
      <anchorfile>group__math__constants_ga78368627f2d3836197ba8e93c320e04e.html</anchorfile>
      <anchor>ga78368627f2d3836197ba8e93c320e04e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log_10</name>
      <anchorfile>group__math__constants_ga67f008299fc82c71284a8b8777d4c13f.html</anchorfile>
      <anchor>ga67f008299fc82c71284a8b8777d4c13f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log_2</name>
      <anchorfile>group__math__constants_gad4e63cd8d3bcf7c4bccf78fc2e902315.html</anchorfile>
      <anchor>gad4e63cd8d3bcf7c4bccf78fc2e902315</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log_phi</name>
      <anchorfile>group__math__constants_ga85165c7097e6135d0804805a856194aa.html</anchorfile>
      <anchor>ga85165c7097e6135d0804805a856194aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>loglog_2</name>
      <anchorfile>group__math__constants_gac03d1d99c5aafd52b88953e5594087ef.html</anchorfile>
      <anchor>gac03d1d99c5aafd52b88953e5594087ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>maxlog</name>
      <anchorfile>group__math__constants_gafa58266d667db8fb77cd37f20c2f2b69.html</anchorfile>
      <anchor>gafa58266d667db8fb77cd37f20c2f2b69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>maxlog10</name>
      <anchorfile>group__math__constants_gab48684a50934f99095f9c4a3ff2d1bdc.html</anchorfile>
      <anchor>gab48684a50934f99095f9c4a3ff2d1bdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>maxlog2</name>
      <anchorfile>group__math__constants_ga93af75df7ea588f88e33d6781acae79c.html</anchorfile>
      <anchor>ga93af75df7ea588f88e33d6781acae79c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minlog</name>
      <anchorfile>group__math__constants_ga6d5d71fa95856c09415f3ae7eefaea69.html</anchorfile>
      <anchor>ga6d5d71fa95856c09415f3ae7eefaea69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minlog10</name>
      <anchorfile>group__math__constants_ga12317003697b491ab0886a8e0ae9bf5b.html</anchorfile>
      <anchor>ga12317003697b491ab0886a8e0ae9bf5b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minlog10denormal</name>
      <anchorfile>group__math__constants_gae0d7fb87d55d1fdfaf3dd7eef0938491.html</anchorfile>
      <anchor>gae0d7fb87d55d1fdfaf3dd7eef0938491</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minlog2</name>
      <anchorfile>group__math__constants_gaef0f85c3c53085c44bc5aebd7b7aa03f.html</anchorfile>
      <anchor>gaef0f85c3c53085c44bc5aebd7b7aa03f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minlog2denormal</name>
      <anchorfile>group__math__constants_ga5854afd87abfbd4c57ccc263b293832c.html</anchorfile>
      <anchor>ga5854afd87abfbd4c57ccc263b293832c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minlogdenormal</name>
      <anchorfile>group__math__constants_ga611180d8bd14d97e4441f754975d31fb.html</anchorfile>
      <anchor>ga611180d8bd14d97e4441f754975d31fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>oneotwoeps</name>
      <anchorfile>group__core__constants_ga32a23889e11125f0d2248d10ba03d936.html</anchorfile>
      <anchor>ga32a23889e11125f0d2248d10ba03d936</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>phi</name>
      <anchorfile>group__math__constants_ga0f8fbe6ec946f1ecfc3e2463ab90db22.html</anchorfile>
      <anchor>ga0f8fbe6ec946f1ecfc3e2463ab90db22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pi</name>
      <anchorfile>group__math__constants_gad32687fc782ada2bb223abb7722ac694.html</anchorfile>
      <anchor>gad32687fc782ada2bb223abb7722ac694</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pi2</name>
      <anchorfile>group__math__constants_gac2e73b089c8b271d073b845856d3052b.html</anchorfile>
      <anchor>gac2e73b089c8b271d073b845856d3052b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pi2o_16</name>
      <anchorfile>group__math__constants_ga87749930f03f4a15467a789f530cbe57.html</anchorfile>
      <anchor>ga87749930f03f4a15467a789f530cbe57</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pi2o_6</name>
      <anchorfile>group__math__constants_gadd155e6b827ca3694423a877b409d135.html</anchorfile>
      <anchor>gadd155e6b827ca3694423a877b409d135</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pi3</name>
      <anchorfile>group__math__constants_gac6703b19d696ecf60c0040bc1012e626.html</anchorfile>
      <anchor>gac6703b19d696ecf60c0040bc1012e626</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pi_minus_3</name>
      <anchorfile>group__math__constants_gabaefb982c5df157545673ba9c903208f.html</anchorfile>
      <anchor>gabaefb982c5df157545673ba9c903208f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pi_pow_e</name>
      <anchorfile>group__math__constants_ga1376aa14dc0d8a08351ebb804b11f793.html</anchorfile>
      <anchor>ga1376aa14dc0d8a08351ebb804b11f793</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pio_2</name>
      <anchorfile>group__math__constants_gabd8e0faaa62af384db4334f953957003.html</anchorfile>
      <anchor>gabd8e0faaa62af384db4334f953957003</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pio_3</name>
      <anchorfile>group__math__constants_gac30b29df2f7d7903ac7e0097a51b22e4.html</anchorfile>
      <anchor>gac30b29df2f7d7903ac7e0097a51b22e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pio_4</name>
      <anchorfile>group__math__constants_ga2a706e8a2c1d95d557f32f1aa54d1ada.html</anchorfile>
      <anchor>ga2a706e8a2c1d95d557f32f1aa54d1ada</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pio_6</name>
      <anchorfile>group__math__constants_ga61628074a13f5a890b80f5338f7ad6c6.html</anchorfile>
      <anchor>ga61628074a13f5a890b80f5338f7ad6c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>quarter</name>
      <anchorfile>group__math__constants_gaac85860bbe1492610ac1caeeb974d662.html</anchorfile>
      <anchor>gaac85860bbe1492610ac1caeeb974d662</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rayleigh_kurtosis</name>
      <anchorfile>group__math__constants_ga230bfcaf73e0c37bc4bc27d57129a049.html</anchorfile>
      <anchor>ga230bfcaf73e0c37bc4bc27d57129a049</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rayleigh_kurtosis_excess</name>
      <anchorfile>group__math__constants_gaec7fc28f375ffcb697a9467b71248a58.html</anchorfile>
      <anchor>gaec7fc28f375ffcb697a9467b71248a58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rayleigh_skewness</name>
      <anchorfile>group__math__constants_gaa4e2225fb86237345c41da2f5a08fd95.html</anchorfile>
      <anchor>gaa4e2225fb86237345c41da2f5a08fd95</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rsqrt_2pi</name>
      <anchorfile>group__math__constants_ga1337a8283c8fca82730d3531f2f3dbfd.html</anchorfile>
      <anchor>ga1337a8283c8fca82730d3531f2f3dbfd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rsqrt_e</name>
      <anchorfile>group__math__constants_ga7fc0e36604c0b1991333ee301ac7fc5a.html</anchorfile>
      <anchor>ga7fc0e36604c0b1991333ee301ac7fc5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rsqrt_pi</name>
      <anchorfile>group__math__constants_gaebae899c8044c16bc129e39cdf810be0.html</anchorfile>
      <anchor>gaebae899c8044c16bc129e39cdf810be0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rsqrt_pio_2</name>
      <anchorfile>group__math__constants_ga1c0ad8a9dcef2a7396e04ae471224d6e.html</anchorfile>
      <anchor>ga1c0ad8a9dcef2a7396e04ae471224d6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sin_1</name>
      <anchorfile>group__math__constants_ga3c80d591964d0c7b6f022c15e8bd20ab.html</anchorfile>
      <anchor>ga3c80d591964d0c7b6f022c15e8bd20ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sinh_1</name>
      <anchorfile>group__math__constants_ga5d9e23b8dba4be11f68af135e984fd3e.html</anchorfile>
      <anchor>ga5d9e23b8dba4be11f68af135e984fd3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sixth</name>
      <anchorfile>group__math__constants_ga34d09c7266d9a9f15cd63151b15778e2.html</anchorfile>
      <anchor>ga34d09c7266d9a9f15cd63151b15778e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqrt_2</name>
      <anchorfile>group__math__constants_ga95a581729f417a842b6fa19d56367e9b.html</anchorfile>
      <anchor>ga95a581729f417a842b6fa19d56367e9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqrt_2pi</name>
      <anchorfile>group__math__constants_gaa25145cc047e71fb561f7504137da7b0.html</anchorfile>
      <anchor>gaa25145cc047e71fb561f7504137da7b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqrt_3</name>
      <anchorfile>group__math__constants_ga08f5fe4d0413da671c65f6a731877cfd.html</anchorfile>
      <anchor>ga08f5fe4d0413da671c65f6a731877cfd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqrt_e</name>
      <anchorfile>group__math__constants_ga7a2f229e61a2c0ac27237c40e79c4db6.html</anchorfile>
      <anchor>ga7a2f229e61a2c0ac27237c40e79c4db6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqrt_pi</name>
      <anchorfile>group__math__constants_ga0418152acbbcccd3839043a19905f3a7.html</anchorfile>
      <anchor>ga0418152acbbcccd3839043a19905f3a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqrt_pio_2</name>
      <anchorfile>group__math__constants_gaf43401e8a277208e868bd1d990dd1e8d.html</anchorfile>
      <anchor>gaf43401e8a277208e868bd1d990dd1e8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqrtlog_4</name>
      <anchorfile>group__math__constants_ga5f32b34733fec39e6cabd220d777d232.html</anchorfile>
      <anchor>ga5f32b34733fec39e6cabd220d777d232</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>third</name>
      <anchorfile>group__math__constants_ga2aa6df7f999fda8b7d9383257d6ad93d.html</anchorfile>
      <anchor>ga2aa6df7f999fda8b7d9383257d6ad93d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>three_o_4</name>
      <anchorfile>group__math__constants_ga62fbd8d516967e29ea1999be485539ec.html</anchorfile>
      <anchor>ga62fbd8d516967e29ea1999be485539ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>three_pio_4</name>
      <anchorfile>group__math__constants_gaeaac995add2aac154468e039c9e5d441.html</anchorfile>
      <anchor>gaeaac995add2aac154468e039c9e5d441</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>two_o_3</name>
      <anchorfile>group__math__constants_ga1e6352f3eb3f929ad1f0d355a2384e0b.html</anchorfile>
      <anchor>ga1e6352f3eb3f929ad1f0d355a2384e0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>two_o_pi</name>
      <anchorfile>group__math__constants_ga6effc6048ec55820a9049f5045625005.html</anchorfile>
      <anchor>ga6effc6048ec55820a9049f5045625005</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>two_o_sqrt_pi</name>
      <anchorfile>group__math__constants_gae38512406479f1c83cc108fa974bd36d.html</anchorfile>
      <anchor>gae38512406479f1c83cc108fa974bd36d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>two_pi</name>
      <anchorfile>group__math__constants_gaeec613ddc8392de0654ab8a1241e0c7a.html</anchorfile>
      <anchor>gaeec613ddc8392de0654ab8a1241e0c7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>two_pio_3</name>
      <anchorfile>group__math__constants_gae00871db0f3b2975fdca381f890123dd.html</anchorfile>
      <anchor>gae00871db0f3b2975fdca381f890123dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>zeta_2</name>
      <anchorfile>group__math__constants_ga257233d84c718b400dae1c6baf71a642.html</anchorfile>
      <anchor>ga257233d84c718b400dae1c6baf71a642</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>zeta_3</name>
      <anchorfile>group__math__constants_ga8d71096cdc12ce0e4c2c139cc244a3bf.html</anchorfile>
      <anchor>ga8d71096cdc12ce0e4c2c139cc244a3bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>acos</name>
      <anchorfile>group__math__invtrig_gad288914ad628b2df2ad07d0d2fbb3462.html</anchorfile>
      <anchor>gad288914ad628b2df2ad07d0d2fbb3462</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>acosh</name>
      <anchorfile>group__math__invhyper_gab23e955be1ff0b427a22c799202e289e.html</anchorfile>
      <anchor>gab23e955be1ff0b427a22c799202e289e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>acot</name>
      <anchorfile>group__math__invtrig_ga37a7ef31cd1a2050afbf744a0ea07095.html</anchorfile>
      <anchor>ga37a7ef31cd1a2050afbf744a0ea07095</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>acoth</name>
      <anchorfile>group__math__invhyper_gadfee8358d1000c96f6e572c7849baf0c.html</anchorfile>
      <anchor>gadfee8358d1000c96f6e572c7849baf0c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>acsc</name>
      <anchorfile>group__math__invtrig_gaa639c90f85170d5b1cd0a717dfc7d785.html</anchorfile>
      <anchor>gaa639c90f85170d5b1cd0a717dfc7d785</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>acsch</name>
      <anchorfile>group__math__invhyper_gacbfc2664a53d2824d2a0d5769f5a19ff.html</anchorfile>
      <anchor>gacbfc2664a53d2824d2a0d5769f5a19ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>agd</name>
      <anchorfile>group__math__invhyper_ga0d95c66d561a5a2a6b18cc920d5069c7.html</anchorfile>
      <anchor>ga0d95c66d561a5a2a6b18cc920d5069c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>arg</name>
      <anchorfile>group__math__trig_ga8d23db8b1e967b99e1425ac6dac47a25.html</anchorfile>
      <anchor>ga8d23db8b1e967b99e1425ac6dac47a25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>asec</name>
      <anchorfile>group__math__invtrig_gaa70504a3df7611b4a9148d3c14b80c9e.html</anchorfile>
      <anchor>gaa70504a3df7611b4a9148d3c14b80c9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>asech</name>
      <anchorfile>group__math__invhyper_ga9c8f737823fb88fd8d671a6cb4a5a3e0.html</anchorfile>
      <anchor>ga9c8f737823fb88fd8d671a6cb4a5a3e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>asin</name>
      <anchorfile>group__math__invtrig_ga91af84e3494079a4a30a285efdf7c775.html</anchorfile>
      <anchor>ga91af84e3494079a4a30a285efdf7c775</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>asinh</name>
      <anchorfile>group__math__invhyper_ga070c564edae696a684655a70f2d5aaa5.html</anchorfile>
      <anchor>ga070c564edae696a684655a70f2d5aaa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>atan</name>
      <anchorfile>group__math__invtrig_ga501388937d24a282aa9450162dc51818.html</anchorfile>
      <anchor>ga501388937d24a282aa9450162dc51818</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>atan2</name>
      <anchorfile>group__math__invtrig_ga4e3cc734432c96af2f4e1bfb576ea504.html</anchorfile>
      <anchor>ga4e3cc734432c96af2f4e1bfb576ea504</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>atanh</name>
      <anchorfile>group__math__invhyper_ga38b26408c813ee8b8705f2f520c760d6.html</anchorfile>
      <anchor>ga38b26408c813ee8b8705f2f520c760d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cbrt</name>
      <anchorfile>group__math__exp_ga13bb6cc57b6512776b1fc0d72c184fd7.html</anchorfile>
      <anchor>ga13bb6cc57b6512776b1fc0d72c184fd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cos</name>
      <anchorfile>group__math__trig_ga36c6472a18a6a22d2af48cd1070c6ab2.html</anchorfile>
      <anchor>ga36c6472a18a6a22d2af48cd1070c6ab2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cosh</name>
      <anchorfile>group__math__hyper_ga984fde6804fbbc4e982bdb5dd7f23dc6.html</anchorfile>
      <anchor>ga984fde6804fbbc4e982bdb5dd7f23dc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cot</name>
      <anchorfile>group__math__trig_ga1f3bad93037c3bed17cfbe954ab0dc79.html</anchorfile>
      <anchor>ga1f3bad93037c3bed17cfbe954ab0dc79</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>coth</name>
      <anchorfile>group__math__hyper_gab23aa4355242b99aae0bcbd1b9190870.html</anchorfile>
      <anchor>gab23aa4355242b99aae0bcbd1b9190870</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>csc</name>
      <anchorfile>group__math__trig_ga58de56369367394561f438e248bb51d7.html</anchorfile>
      <anchor>ga58de56369367394561f438e248bb51d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>csch</name>
      <anchorfile>group__math__hyper_ga0c5b7f148a4cce5c8a2ec8ba6bc2bb8e.html</anchorfile>
      <anchor>ga0c5b7f148a4cce5c8a2ec8ba6bc2bb8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>deginrad</name>
      <anchorfile>group__math__trig_gae9819f646fb28b1a2ff178eecd383eda.html</anchorfile>
      <anchor>gae9819f646fb28b1a2ff178eecd383eda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>div_180</name>
      <anchorfile>group__math__trig_gae38f095b02721ec8d4e23bf613a3ddba.html</anchorfile>
      <anchor>gae38f095b02721ec8d4e23bf613a3ddba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>exp</name>
      <anchorfile>group__math__exp_ga01387edd49b1ff23f210c7105d65839e.html</anchorfile>
      <anchor>ga01387edd49b1ff23f210c7105d65839e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>exp10</name>
      <anchorfile>group__math__exp_gad36941c942d7f200e996734a9b62a092.html</anchorfile>
      <anchor>gad36941c942d7f200e996734a9b62a092</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>exp2</name>
      <anchorfile>group__math__exp_ga0a3642b91604e578b8d4ef6314d39495.html</anchorfile>
      <anchor>ga0a3642b91604e578b8d4ef6314d39495</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>expm1</name>
      <anchorfile>group__math__exp_gaea2fcee0502a2daf2431462972b30001.html</anchorfile>
      <anchor>gaea2fcee0502a2daf2431462972b30001</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>expmx2</name>
      <anchorfile>group__math__exp_ga7596b6ef2b11f4964c424002ebc75769.html</anchorfile>
      <anchor>ga7596b6ef2b11f4964c424002ebc75769</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>expx2</name>
      <anchorfile>group__math__exp_ga9166af39f3533cb7dd7471a25989f636.html</anchorfile>
      <anchor>ga9166af39f3533cb7dd7471a25989f636</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>gd</name>
      <anchorfile>group__math__hyper_gac2f0fbac24a6b4ca2f12dcdd07c054bc.html</anchorfile>
      <anchor>gac2f0fbac24a6b4ca2f12dcdd07c054bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>geommean</name>
      <anchorfile>group__math__exp_ga7871a1e2f6b0faa5834acd8f8f7bddef.html</anchorfile>
      <anchor>ga7871a1e2f6b0faa5834acd8f8f7bddef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>harmmean</name>
      <anchorfile>group__math__exp_ga2873065e807a313ffd23d3a06e2be637.html</anchorfile>
      <anchor>ga2873065e807a313ffd23d3a06e2be637</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>hypot</name>
      <anchorfile>group__math__exp_gaae6d8d8a0ad9d41260c0bbf8f642a370.html</anchorfile>
      <anchor>gaae6d8d8a0ad9d41260c0bbf8f642a370</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kolmmean</name>
      <anchorfile>group__math__exp_gafa20e073c378a3eb096b3b3f3ee37741.html</anchorfile>
      <anchor>gafa20e073c378a3eb096b3b3f3ee37741</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lentz_a</name>
      <anchorfile>group__contfrac_ga00839b4ed589aba86fcb42545c88eaeb.html</anchorfile>
      <anchor>ga00839b4ed589aba86fcb42545c88eaeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lentz_b</name>
      <anchorfile>group__contfrac_gac8fda10393aa09246d2bfe8b309cb909.html</anchorfile>
      <anchor>gac8fda10393aa09246d2bfe8b309cb909</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log</name>
      <anchorfile>group__math__log_ga9b4217fd31e1641227ea37686686d31d.html</anchorfile>
      <anchor>ga9b4217fd31e1641227ea37686686d31d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log10</name>
      <anchorfile>group__math__log_gac249fe99bf31089a24fd212763e94c9e.html</anchorfile>
      <anchor>gac249fe99bf31089a24fd212763e94c9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log1p</name>
      <anchorfile>group__math__log_ga8adec0a7ab1019888308181fc8c7b5dc.html</anchorfile>
      <anchor>ga8adec0a7ab1019888308181fc8c7b5dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log2</name>
      <anchorfile>group__math__log_gaa35d093ac60527a5d5ac6fcfc7fbd4d4.html</anchorfile>
      <anchor>gaa35d093ac60527a5d5ac6fcfc7fbd4d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log_abs</name>
      <anchorfile>group__math__log_ga4dfa083ee26064c6c5256bff56075e5d.html</anchorfile>
      <anchor>ga4dfa083ee26064c6c5256bff56075e5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>logspace_add</name>
      <anchorfile>group__math__log_ga66b8874abdcc6e29c9b4c0c7291ac9db.html</anchorfile>
      <anchor>ga66b8874abdcc6e29c9b4c0c7291ac9db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>logspace_sub</name>
      <anchorfile>group__math__log_gaf5f2a44d3148e9431e1840397b1edd46.html</anchorfile>
      <anchor>gaf5f2a44d3148e9431e1840397b1edd46</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>neville</name>
      <anchorfile>group__core__arithmetic_ga9410b950085a4299478368cdc4864e58.html</anchorfile>
      <anchor>ga9410b950085a4299478368cdc4864e58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>nthroot</name>
      <anchorfile>group__math__exp_ga9cf7e798d0bd35ae16a3588021c871e7.html</anchorfile>
      <anchor>ga9cf7e798d0bd35ae16a3588021c871e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pow</name>
      <anchorfile>group__math__exp_ga67952622d4400abecd8ca1b9986f9648.html</anchorfile>
      <anchor>ga67952622d4400abecd8ca1b9986f9648</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pow1p</name>
      <anchorfile>group__math__exp_ga26151ac8cead2b5ebc679abb9e9c3f9b.html</anchorfile>
      <anchor>ga26151ac8cead2b5ebc679abb9e9c3f9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pow_abs</name>
      <anchorfile>group__math__exp_ga2963a8be3fa9be34ecbb0783084f5456.html</anchorfile>
      <anchor>ga2963a8be3fa9be34ecbb0783084f5456</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>powm1</name>
      <anchorfile>group__math__exp_ga33c7d6d3dd940917f2d926732d21b0d0.html</anchorfile>
      <anchor>ga33c7d6d3dd940917f2d926732d21b0d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>quadrant</name>
      <anchorfile>group__math__trig_gabddb668a3d3a31c888377fc66cb67640.html</anchorfile>
      <anchor>gabddb668a3d3a31c888377fc66cb67640</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>radindeg</name>
      <anchorfile>group__math__trig_gafe1c9782e1c8077e3108775150c5286f.html</anchorfile>
      <anchor>gafe1c9782e1c8077e3108775150c5286f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>radinpi</name>
      <anchorfile>group__math__trig_gad88bed1c31cbbaede5f4f03ff13bbb71.html</anchorfile>
      <anchor>gad88bed1c31cbbaede5f4f03ff13bbb71</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rempio2</name>
      <anchorfile>group__math__trig_gaf499e87cc47529c27dd16d88ed57cd08.html</anchorfile>
      <anchor>gaf499e87cc47529c27dd16d88ed57cd08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>reverse_horner</name>
      <anchorfile>group__math_gadeb757d766fe37f677ad7b883fc9d7f2.html</anchorfile>
      <anchor>gadeb757d766fe37f677ad7b883fc9d7f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sec</name>
      <anchorfile>group__math__trig_ga5fa51e730488c41abb8402a3d1635877.html</anchorfile>
      <anchor>ga5fa51e730488c41abb8402a3d1635877</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sech</name>
      <anchorfile>group__math__hyper_ga268393b3e561e0f65521c56095b4d552.html</anchorfile>
      <anchor>ga268393b3e561e0f65521c56095b4d552</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sigmoid</name>
      <anchorfile>group__math__sigmoid_gac5104eec242c802b49f1376b5b8215df.html</anchorfile>
      <anchor>gac5104eec242c802b49f1376b5b8215df</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>significants</name>
      <anchorfile>group__math__exp_ga800665fde1e25605cbfa89c47dea8f6e.html</anchorfile>
      <anchor>ga800665fde1e25605cbfa89c47dea8f6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sin</name>
      <anchorfile>group__math__trig_ga1ed5ec0a84a4ad7ae88b11033a63d04b.html</anchorfile>
      <anchor>ga1ed5ec0a84a4ad7ae88b11033a63d04b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sincos</name>
      <anchorfile>group__math__trig_gae52069dae490294ee836af9c366bbbac.html</anchorfile>
      <anchor>gae52069dae490294ee836af9c366bbbac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sinh</name>
      <anchorfile>group__math__hyper_ga66b0e9fefb189e70baa9e4bbbe0d96e2.html</anchorfile>
      <anchor>ga66b0e9fefb189e70baa9e4bbbe0d96e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sinhc</name>
      <anchorfile>group__math__hyper_gac3173586c72be203e69c6748c2ef749b.html</anchorfile>
      <anchor>gac3173586c72be203e69c6748c2ef749b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sinhcosh</name>
      <anchorfile>group__math__hyper_ga780fd5136b6d43175ecd6fde88dc0f70.html</anchorfile>
      <anchor>ga780fd5136b6d43175ecd6fde88dc0f70</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>tan</name>
      <anchorfile>group__math__trig_ga4e45e50d570ac3a6e925f7fd39f40c42.html</anchorfile>
      <anchor>ga4e45e50d570ac3a6e925f7fd39f40c42</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>tanh</name>
      <anchorfile>group__math__hyper_gae9a274c4cd3dd6e99bf32cae9dd642bf.html</anchorfile>
      <anchor>gae9a274c4cd3dd6e99bf32cae9dd642bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>abel</name>
      <anchorfile>group__polynomial_ga0a8064a3bf2a0b02a5aab69f12ac48c4.html</anchorfile>
      <anchor>ga0a8064a3bf2a0b02a5aab69f12ac48c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>gegenbauer</name>
      <anchorfile>group__polynomial_ga654af420c26859a9b088461f2b49d336.html</anchorfile>
      <anchor>ga654af420c26859a9b088461f2b49d336</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>hermite</name>
      <anchorfile>group__polynomial_ga6cb61eb743e4ac43c44bd0b330f8a8c9.html</anchorfile>
      <anchor>ga6cb61eb743e4ac43c44bd0b330f8a8c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>jacobi</name>
      <anchorfile>group__polynomial_ga0e8517a2ade493151ddd04defc631971.html</anchorfile>
      <anchor>ga0e8517a2ade493151ddd04defc631971</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>laguerre</name>
      <anchorfile>group__polynomial_ga79168b37417f76520ad0cf3e7cdef489.html</anchorfile>
      <anchor>ga79168b37417f76520ad0cf3e7cdef489</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>legendre</name>
      <anchorfile>group__polynomial_ga669b4f63c4de40bd3712f90a301df477.html</anchorfile>
      <anchor>ga669b4f63c4de40bd3712f90a301df477</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>tchebytchev</name>
      <anchorfile>group__polynomial_ga76ed546859e8fc7ab78c7a998d64faa3.html</anchorfile>
      <anchor>ga76ed546859e8fc7ab78c7a998d64faa3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>beta</name>
      <anchorfile>group__special_ga82b53a249d6073de3db11e4aa3792333.html</anchorfile>
      <anchor>ga82b53a249d6073de3db11e4aa3792333</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>betainc</name>
      <anchorfile>group__special_ga6265a2055297023ecb43dd7b686d071b.html</anchorfile>
      <anchor>ga6265a2055297023ecb43dd7b686d071b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>betainc_inv</name>
      <anchorfile>group__special_gad608f2f150843348a76ac10aac42e81d.html</anchorfile>
      <anchor>gad608f2f150843348a76ac10aac42e81d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cos_int</name>
      <anchorfile>group__special_ga0305432c8d066d530744c297856afc7c.html</anchorfile>
      <anchor>ga0305432c8d066d530744c297856afc7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>dawson</name>
      <anchorfile>group__special_ga984ab215f62e9bed040c35776a18eeac.html</anchorfile>
      <anchor>ga984ab215f62e9bed040c35776a18eeac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>digamma</name>
      <anchorfile>group__special_ga35bd17562d2457033901ba4a6a112808.html</anchorfile>
      <anchor>ga35bd17562d2457033901ba4a6a112808</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>erf</name>
      <anchorfile>group__special_ga1dbce0b509333c811af2c620f07aacc4.html</anchorfile>
      <anchor>ga1dbce0b509333c811af2c620f07aacc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>erf_inv</name>
      <anchorfile>group__special_ga1f15df67386cc4841f9b5b20e6acce50.html</anchorfile>
      <anchor>ga1f15df67386cc4841f9b5b20e6acce50</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>erfc</name>
      <anchorfile>group__special_ga026fdedcb9cf7041cdf7d670d7a095bc.html</anchorfile>
      <anchor>ga026fdedcb9cf7041cdf7d670d7a095bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>erfc_inv</name>
      <anchorfile>group__special_gae47d192b5a13d6a35516de4ae2da273d.html</anchorfile>
      <anchor>gae47d192b5a13d6a35516de4ae2da273d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>erfcx</name>
      <anchorfile>group__special_ga39a32ff65020290d5c0d8975c648a901.html</anchorfile>
      <anchor>ga39a32ff65020290d5c0d8975c648a901</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>exp_int</name>
      <anchorfile>group__special_gac952b61c8134c6d1a20071760ce2749d.html</anchorfile>
      <anchor>gac952b61c8134c6d1a20071760ce2749d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>factorial</name>
      <anchorfile>group__special_gaa985cb92e44034e0b56d51aa7b12a72f.html</anchorfile>
      <anchor>gaa985cb92e44034e0b56d51aa7b12a72f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>gamma_p</name>
      <anchorfile>group__special_gaca2a6730649297012022897eb2b4b549.html</anchorfile>
      <anchor>gaca2a6730649297012022897eb2b4b549</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>gamma_p_inv</name>
      <anchorfile>group__special_ga84e6f5cc6ba688751341a9a2a314363e.html</anchorfile>
      <anchor>ga84e6f5cc6ba688751341a9a2a314363e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>hurwitz</name>
      <anchorfile>group__special_gadf7af0b7e2002701bbdbb8419d6757eb.html</anchorfile>
      <anchor>gadf7af0b7e2002701bbdbb8419d6757eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lambert</name>
      <anchorfile>group__special_ga87ab5feda409075628e3c53c8022ffac.html</anchorfile>
      <anchor>ga87ab5feda409075628e3c53c8022ffac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lbeta</name>
      <anchorfile>group__special_ga340e8bdb903cecc2bf070e6a5c53975c.html</anchorfile>
      <anchor>ga340e8bdb903cecc2bf070e6a5c53975c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lfactorial</name>
      <anchorfile>group__special_gaf0da94be6b92a70b4b5887a1db7cc256.html</anchorfile>
      <anchor>gaf0da94be6b92a70b4b5887a1db7cc256</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log_abs_gamma</name>
      <anchorfile>group__special_ga53390ef1f01ae9ea76542610a2ef6310.html</anchorfile>
      <anchor>ga53390ef1f01ae9ea76542610a2ef6310</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log_gamma</name>
      <anchorfile>group__special_gaab4644340afcf841c6b06e2ab3a8d7fd.html</anchorfile>
      <anchor>gaab4644340afcf841c6b06e2ab3a8d7fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lrising_factorial</name>
      <anchorfile>group__special_gab1b9a2a36db6d1dcaa97a3619eef8e9b.html</anchorfile>
      <anchor>gab1b9a2a36db6d1dcaa97a3619eef8e9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>omega</name>
      <anchorfile>group__special_gab2da346734b5d477afbbc1c91018a940.html</anchorfile>
      <anchor>gab2da346734b5d477afbbc1c91018a940</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>polygamma</name>
      <anchorfile>group__special_ga1e9de30f261edeef4271c47b7683c980.html</anchorfile>
      <anchor>ga1e9de30f261edeef4271c47b7683c980</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rising_factorial</name>
      <anchorfile>group__special_ga3c336080e4c6ee720c464ce4ebe60b75.html</anchorfile>
      <anchor>ga3c336080e4c6ee720c464ce4ebe60b75</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>signgam</name>
      <anchorfile>group__special_ga318d06481af50d48d3f50859fc1cdb18.html</anchorfile>
      <anchor>ga318d06481af50d48d3f50859fc1cdb18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sin_int</name>
      <anchorfile>group__special_ga4851b95d7c353647ea62c8a213827aa3.html</anchorfile>
      <anchor>ga4851b95d7c353647ea62c8a213827aa3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>stirling</name>
      <anchorfile>group__special_gaa331e8a7776d0afb3d6d127152a420d5.html</anchorfile>
      <anchor>gaa331e8a7776d0afb3d6d127152a420d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>tgamma</name>
      <anchorfile>group__special_gaf1cae73e680ecb4fd31f6eb45520d4c5.html</anchorfile>
      <anchor>gaf1cae73e680ecb4fd31f6eb45520d4c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>trigamma</name>
      <anchorfile>group__special_ga07111caf2d86c76136eae323799ef5a9.html</anchorfile>
      <anchor>ga07111caf2d86c76136eae323799ef5a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>zeta</name>
      <anchorfile>group__special_ga0eb86f96b60c52b8ffbe2c64354bbc7f.html</anchorfile>
      <anchor>ga0eb86f96b60c52b8ffbe2c64354bbc7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr std::ptrdiff_t</type>
      <name>na_</name>
      <anchorfile>group__simd__types.html</anchorfile>
      <anchor>ga11b65eff854b205c9f9ef8dbd559bb9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr std::ptrdiff_t</type>
      <name>we_</name>
      <anchorfile>group__simd__types.html</anchorfile>
      <anchor>gab6c3c30138d82ef45b1bbcf9e65145d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pattern</name>
      <anchorfile>group__simd__types.html</anchorfile>
      <anchor>ga61c6484edbe5ceb7f92946bc798802dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr std::size_t</type>
      <name>max_scalar_size_v</name>
      <anchorfile>group__traits_ga6e8aacb30e0e7798a5cf8e30f9ace681.html</anchorfile>
      <anchor>ga6e8aacb30e0e7798a5cf8e30f9ace681</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr bool</type>
      <name>supports_options</name>
      <anchorfile>group__extensions_gaf4a87d02fe2157d5848083b4ff725dc4.html</anchorfile>
      <anchor>gaf4a87d02fe2157d5848083b4ff725dc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>functor</name>
      <anchorfile>group__extensions.html</anchorfile>
      <anchor>ga406269d77123b31f9bc18b38b78c8e25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr _::condition_key_t</type>
      <name>condition_key</name>
      <anchorfile>group__extensions_ga28f160dc16e57390e8d479cc62d89af6.html</anchorfile>
      <anchor>ga28f160dc16e57390e8d479cc62d89af6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>namespaceeve.html</anchorfile>
      <anchor>a69ab9db52c90128a055b0aaf62db8892</anchor>
      <arglist>(S const &amp;) -&gt; wide&lt; S, expected_cardinal_t&lt; S &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wide</name>
      <anchorfile>namespaceeve.html</anchorfile>
      <anchor>ac72f0e04016942948dc0d1bf861296f4</anchor>
      <arglist>(S, Ss...) -&gt; wide&lt; S, fixed&lt; 1+sizeof...(Ss)&gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>eve::_</name>
    <filename>namespaceeve_1_1__.html</filename>
    <class kind="struct">eve::_::wide_storage</class>
    <member kind="function">
      <type>constexpr auto</type>
      <name>ellint_rj_</name>
      <anchorfile>namespaceeve_1_1___aeabc5804d976435a5a0cbe79cec380ff.html</anchorfile>
      <anchor>aeabc5804d976435a5a0cbe79cec380ff</anchor>
      <arglist>(adl_helper_t const &amp;, cpu_ const &amp;, O const &amp;, T x, T y, T z, T p)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core_accuracy</name>
    <title>Accuracy helpers</title>
    <filename>group__core__accuracy.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::diff_of_prod</name>
      <anchorfile>group__core__accuracy_gab21bf1ebf628243f28a10f05ce66f820.html</anchorfile>
      <anchor>gab21bf1ebf628243f28a10f05ce66f820</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::safe_scale</name>
      <anchorfile>group__core__accuracy_gad1203df175a5c37630dd175a41b94ae1.html</anchorfile>
      <anchor>gad1203df175a5c37630dd175a41b94ae1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sufp</name>
      <anchorfile>group__core__accuracy_ga86420153c2918b16aee8fa6f4f2d0194.html</anchorfile>
      <anchor>ga86420153c2918b16aee8fa6f4f2d0194</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sulp</name>
      <anchorfile>group__core__accuracy_ga8c7d48b6fe0b1111e63719dc666f9d9c.html</anchorfile>
      <anchor>ga8c7d48b6fe0b1111e63719dc666f9d9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sum_of_prod</name>
      <anchorfile>group__core__accuracy_ga36017626c633cde2a07146d49d9ccbe7.html</anchorfile>
      <anchor>ga36017626c633cde2a07146d49d9ccbe7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::three_fma</name>
      <anchorfile>group__core__accuracy_gabacbafd11abd5e82e49aa6ab394cd10e.html</anchorfile>
      <anchor>gabacbafd11abd5e82e49aa6ab394cd10e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::two_add</name>
      <anchorfile>group__core__accuracy_ga3a5c4b16896174afe9e63b05e1f9b011.html</anchorfile>
      <anchor>ga3a5c4b16896174afe9e63b05e1f9b011</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::two_div_approx</name>
      <anchorfile>group__core__accuracy_gadd6ab7f52e4d422e1edddc72e49cda2f.html</anchorfile>
      <anchor>gadd6ab7f52e4d422e1edddc72e49cda2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::two_prod</name>
      <anchorfile>group__core__accuracy_ga255bfbae7d6cf4b43a63d8f834e907b4.html</anchorfile>
      <anchor>ga255bfbae7d6cf4b43a63d8f834e907b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::two_sub</name>
      <anchorfile>group__core__accuracy_ga8e384bfd5e06145bdca49fa9da74cfcd.html</anchorfile>
      <anchor>ga8e384bfd5e06145bdca49fa9da74cfcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::veltkamp</name>
      <anchorfile>group__core__accuracy_ga9234fd48e496db5dd743b5494a4a932d.html</anchorfile>
      <anchor>ga9234fd48e496db5dd743b5494a4a932d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>algo_traits</name>
    <title>AlgoTraits</title>
    <filename>group__algo__traits.html</filename>
    <class kind="struct">eve::algo::traits</class>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::unroll</name>
      <anchorfile>group__algo__traits_gaa0edcdf11a934c3303c8dbac175f5340.html</anchorfile>
      <anchor>gaa0edcdf11a934c3303c8dbac175f5340</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::force_cardinal</name>
      <anchorfile>group__algo__traits_ga129b5b6d565ac288ce78eec6ecbb5e0b.html</anchorfile>
      <anchor>ga129b5b6d565ac288ce78eec6ecbb5e0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>auto</type>
      <name>eve::algo::consider_types</name>
      <anchorfile>group__algo__traits_gaf48b5ce3d81ecae9190a95518e66c65d.html</anchorfile>
      <anchor>gaf48b5ce3d81ecae9190a95518e66c65d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>auto</type>
      <name>eve::algo::force_type</name>
      <anchorfile>group__algo__traits_gaa0660d17d33bec0cc2b67123f4e641f5.html</anchorfile>
      <anchor>gaa0660d17d33bec0cc2b67123f4e641f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::common_with_types</name>
      <anchorfile>group__algo__traits_ga6fe08218254b894a318ab2fd1b4b49b7.html</anchorfile>
      <anchor>ga6fe08218254b894a318ab2fd1b4b49b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::common_type</name>
      <anchorfile>group__algo__traits_ga3ea818c89fdbcd6eac686126f73631f2.html</anchorfile>
      <anchor>ga3ea818c89fdbcd6eac686126f73631f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::divisible_by_cardinal</name>
      <anchorfile>group__algo__traits_ga01b72d95d26f28c2c8715af53bef8f53.html</anchorfile>
      <anchor>ga01b72d95d26f28c2c8715af53bef8f53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::no_aligning</name>
      <anchorfile>group__algo__traits_ga07dd1178b2904dc377069bc34452a84e.html</anchorfile>
      <anchor>ga07dd1178b2904dc377069bc34452a84e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::no_unrolling</name>
      <anchorfile>group__algo__traits.html</anchorfile>
      <anchor>ga0d4b9be2485537d9328218378c918107</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::expensive_callable</name>
      <anchorfile>group__algo__traits_ga03487a05ad7b38febedbf22e671dcf93.html</anchorfile>
      <anchor>ga03487a05ad7b38febedbf22e671dcf93</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::single_pass</name>
      <anchorfile>group__algo__traits_ga595b740184ec13567d04b391145f2a19.html</anchorfile>
      <anchor>ga595b740184ec13567d04b391145f2a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::fuse_operations</name>
      <anchorfile>group__algo__traits_gaa737d6973f35568d2eaca9813e07e0e6.html</anchorfile>
      <anchor>gaa737d6973f35568d2eaca9813e07e0e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::expect_smaller_range</name>
      <anchorfile>group__algo__traits_ga2d13212794beb6ffc81d8a0d2f8b1419.html</anchorfile>
      <anchor>ga2d13212794beb6ffc81d8a0d2f8b1419</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::allow_frequency_scaling</name>
      <anchorfile>group__algo__traits_ga31ef5302d899fb36aeff5146a7187cef.html</anchorfile>
      <anchor>ga31ef5302d899fb36aeff5146a7187cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::overflow</name>
      <anchorfile>group__algo__traits.html</anchorfile>
      <anchor>ga988f8c96b378db06d7779187f19499cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::index_type</name>
      <anchorfile>group__algo__traits_ga939cbe71c5d2a082f404882bcd768e55.html</anchorfile>
      <anchor>ga939cbe71c5d2a082f404882bcd768e55</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::sparse_output</name>
      <anchorfile>group__algo__traits_ga20320b3af45c2868e9a4e6c7a5049fa9.html</anchorfile>
      <anchor>ga20320b3af45c2868e9a4e6c7a5049fa9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::dense_output</name>
      <anchorfile>group__algo__traits_gab450c355e4ef74d7473519d8b5bdff24.html</anchorfile>
      <anchor>gab450c355e4ef74d7473519d8b5bdff24</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>algos</name>
    <title>Algorithms</title>
    <filename>group__algos.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::search</name>
      <anchorfile>group__algos_ga854a1b4a431c6ddfde21e97c4188ab73.html</anchorfile>
      <anchor>ga854a1b4a431c6ddfde21e97c4188ab73</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::all_of</name>
      <anchorfile>group__algos_ga2eec655dc13b6817adbe25df7a0416e2.html</anchorfile>
      <anchor>ga2eec655dc13b6817adbe25df7a0416e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::any_of</name>
      <anchorfile>group__algos_ga3cfc49607571a397add051036af9e605.html</anchorfile>
      <anchor>ga3cfc49607571a397add051036af9e605</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::copy</name>
      <anchorfile>group__algos_ga03f85270a9a10ae8ab04c6ca3f211a86.html</anchorfile>
      <anchor>ga03f85270a9a10ae8ab04c6ca3f211a86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::copy_backward</name>
      <anchorfile>group__algos_ga7eba1d00c6c74a7b73af66f1d80b5fc1.html</anchorfile>
      <anchor>ga7eba1d00c6c74a7b73af66f1d80b5fc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::copy_if</name>
      <anchorfile>group__algos_gae38a65f5bbddc152a1e3b36263ab7090.html</anchorfile>
      <anchor>gae38a65f5bbddc152a1e3b36263ab7090</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::fill</name>
      <anchorfile>group__algos.html</anchorfile>
      <anchor>ga014e6897227ef11787cec4e9757eb934</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::find_if</name>
      <anchorfile>group__algos_gadf0762ce0ad64c41ff1eb704a436894d.html</anchorfile>
      <anchor>gadf0762ce0ad64c41ff1eb704a436894d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::find</name>
      <anchorfile>group__algos_ga1a9ca77a585daafa9b1a61f18516a19a.html</anchorfile>
      <anchor>ga1a9ca77a585daafa9b1a61f18516a19a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::find_if_not</name>
      <anchorfile>group__algos_ga5a2aeb104b7cebbe9cec0d9913aa761d.html</anchorfile>
      <anchor>ga5a2aeb104b7cebbe9cec0d9913aa761d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::find_last_if</name>
      <anchorfile>group__algos_ga156545beabe5c608489c1dbd00837605.html</anchorfile>
      <anchor>ga156545beabe5c608489c1dbd00837605</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::find_last</name>
      <anchorfile>group__algos_ga7f8aa6406e8af7b3b656a584144e6fcd.html</anchorfile>
      <anchor>ga7f8aa6406e8af7b3b656a584144e6fcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::find_last_if_not</name>
      <anchorfile>group__algos_gaa81202381cca6665f0c6b16fb95e9305.html</anchorfile>
      <anchor>gaa81202381cca6665f0c6b16fb95e9305</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::for_each</name>
      <anchorfile>group__algos_ga7547375958ed972878636d26b215cf6e.html</anchorfile>
      <anchor>ga7547375958ed972878636d26b215cf6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct eve::algo::@362211322075272167356201327114230177027211051074</type>
      <name>eve::algo::for_each_iteration_with_expensive_optional_part</name>
      <anchorfile>group__algos_ga5aec774601ee35e820c1193a37de6ba8.html</anchorfile>
      <anchor>ga5aec774601ee35e820c1193a37de6ba8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::for_each_selected</name>
      <anchorfile>group__algos_ga88ef9260535144b063fe9b0881c89cef.html</anchorfile>
      <anchor>ga88ef9260535144b063fe9b0881c89cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::iota</name>
      <anchorfile>group__algos_gafcdd857a5e44f0b4e512e22c9dee27c2.html</anchorfile>
      <anchor>gafcdd857a5e44f0b4e512e22c9dee27c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::keep_if</name>
      <anchorfile>group__algos_ga1dfaa1ff5ad47985d1b0a624ba4404b9.html</anchorfile>
      <anchor>ga1dfaa1ff5ad47985d1b0a624ba4404b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::max_value</name>
      <anchorfile>group__algos_gaf81b82c776f35dc63602d6f07d2bb644.html</anchorfile>
      <anchor>gaf81b82c776f35dc63602d6f07d2bb644</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::min_element</name>
      <anchorfile>group__algos_ga49074f455a196a7f40e25fa7dc16ffcc.html</anchorfile>
      <anchor>ga49074f455a196a7f40e25fa7dc16ffcc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::min_value</name>
      <anchorfile>group__algos_ga644058bf8108cda297acc491586b2e95.html</anchorfile>
      <anchor>ga644058bf8108cda297acc491586b2e95</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::none_of</name>
      <anchorfile>group__algos_ga0bd36eeeef22153e10757aae05e6a032.html</anchorfile>
      <anchor>ga0bd36eeeef22153e10757aae05e6a032</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::reduce</name>
      <anchorfile>group__algos_gae0ec30b748c333d63f9cec7ccdd4cc2e.html</anchorfile>
      <anchor>gae0ec30b748c333d63f9cec7ccdd4cc2e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::remove_if</name>
      <anchorfile>group__algos_gadd433852d81668a52c92e3778111e5ac.html</anchorfile>
      <anchor>gadd433852d81668a52c92e3778111e5ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::remove</name>
      <anchorfile>group__algos_ga58eb0d9f9c8dce6526767527a11c1df9.html</anchorfile>
      <anchor>ga58eb0d9f9c8dce6526767527a11c1df9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::reverse</name>
      <anchorfile>group__algos_gaf48bb5b44d97f753ddffcea820609767.html</anchorfile>
      <anchor>gaf48bb5b44d97f753ddffcea820609767</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::reverse_copy</name>
      <anchorfile>group__algos_ga13148bb64f89919ec144e86dc29ec93c.html</anchorfile>
      <anchor>ga13148bb64f89919ec144e86dc29ec93c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::set_intersection</name>
      <anchorfile>group__algos_ga64053b1d816e0128aa2610fe7e066edd.html</anchorfile>
      <anchor>ga64053b1d816e0128aa2610fe7e066edd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::swap_ranges</name>
      <anchorfile>group__algos_ga32ab3292a3a43722ece241c921a73cad.html</anchorfile>
      <anchor>ga32ab3292a3a43722ece241c921a73cad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::transform_inplace</name>
      <anchorfile>group__algos_gaca82a7bc09323d8f0da1e0d3d5b0bcea.html</anchorfile>
      <anchor>gaca82a7bc09323d8f0da1e0d3d5b0bcea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::transform_to</name>
      <anchorfile>group__algos_gafac4ab5cfc7a92076d9fc87346b8180a.html</anchorfile>
      <anchor>gafac4ab5cfc7a92076d9fc87346b8180a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::transform_copy_if</name>
      <anchorfile>group__algos_ga5f04bc8d4ca88114836570cbd5be9562.html</anchorfile>
      <anchor>ga5f04bc8d4ca88114836570cbd5be9562</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::transform_keep_if</name>
      <anchorfile>group__algos_gab70265959ede0dca152e7227f80cf0da.html</anchorfile>
      <anchor>gab70265959ede0dca152e7227f80cf0da</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::algo::transform_reduce</name>
      <anchorfile>group__algos_gabe47d333f5fa9a70ac6836b2c9c01d98.html</anchorfile>
      <anchor>gabe47d333f5fa9a70ac6836b2c9c01d98</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>algo_concepts</name>
    <title>Algorithms Concepts</title>
    <filename>group__algo__concepts.html</filename>
    <class kind="struct">eve::algo::nothing_t</class>
    <class kind="struct">relaxed_iterator</class>
    <class kind="struct">relaxed_sentinel_for</class>
    <class kind="struct">relaxed_range</class>
    <class kind="struct">map_load_op</class>
    <class kind="struct">map_store_op</class>
    <concept>eve::algo::non_owning_range</concept>
    <member kind="typedef">
      <type>decltype(std::declval&lt; R &gt;().begin())</type>
      <name>eve::algo::iterator_t</name>
      <anchorfile>group__algo__concepts_gaa7e8d090b9c040a50269d70444af720a.html</anchorfile>
      <anchor>gaa7e8d090b9c040a50269d70444af720a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>decltype(std::declval&lt; R &gt;().end())</type>
      <name>eve::algo::sentinel_t</name>
      <anchorfile>group__algo__concepts_ga5b4e7bedc3df8b7b9b7a778766ac301a.html</anchorfile>
      <anchor>ga5b4e7bedc3df8b7b9b7a778766ac301a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unaligned_t&lt; iterator_t&lt; R &gt; &gt;</type>
      <name>eve::algo::unaligned_iterator_t</name>
      <anchorfile>group__algo__concepts_gafeacb9463c55a04e05119f27b880b0e5.html</anchorfile>
      <anchor>gafeacb9463c55a04e05119f27b880b0e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr range_ref_</type>
      <name>eve::algo::range_ref</name>
      <anchorfile>group__algo__concepts_gab9087b01917ce8f9ebe656e5a0c0356d.html</anchorfile>
      <anchor>gab9087b01917ce8f9ebe656e5a0c0356d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>algorithms</name>
    <title>Algorithms and Views</title>
    <filename>group__algorithms.html</filename>
    <subgroup>algo_traits</subgroup>
    <subgroup>algos</subgroup>
    <subgroup>algo_concepts</subgroup>
    <subgroup>views</subgroup>
    <class kind="struct">eve::algo::range_ref_wrapper</class>
    <class kind="struct">eve::algo::ptr_iterator</class>
  </compound>
  <compound kind="group">
    <name>arch</name>
    <title>Architecture related Types and Helpers</title>
    <filename>group__arch.html</filename>
    <class kind="struct">eve::fundamental_cardinal</class>
    <class kind="struct">eve::platform</class>
    <member kind="typedef">
      <type>fixed&lt; expected_cardinal_v&lt; Type, ABI &gt; &gt;</type>
      <name>eve::expected_cardinal_t</name>
      <anchorfile>group__arch_gab707570aa2d35678c5cd5c686a994d57.html</anchorfile>
      <anchor>gab707570aa2d35678c5cd5c686a994d57</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr std::ptrdiff_t</type>
      <name>eve::nofs_cardinal_v</name>
      <anchorfile>group__arch_gab4d8e703ad1e3e94918f3a3ff44e1324.html</anchorfile>
      <anchor>gab4d8e703ad1e3e94918f3a3ff44e1324</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core_arithmetic</name>
    <title>Arithmetic operations</title>
    <filename>group__core__arithmetic.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::abs</name>
      <anchorfile>group__core__arithmetic_ga67722c49041abeb17485c8961f961cd7.html</anchorfile>
      <anchor>ga67722c49041abeb17485c8961f961cd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::absmax</name>
      <anchorfile>group__core__arithmetic_gae3871e8b350b047a88488b22a63cf2e0.html</anchorfile>
      <anchor>gae3871e8b350b047a88488b22a63cf2e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::absmin</name>
      <anchorfile>group__core__arithmetic_ga12cb5353ac66eb2bd19b81edaba931ed.html</anchorfile>
      <anchor>ga12cb5353ac66eb2bd19b81edaba931ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::add</name>
      <anchorfile>group__core__arithmetic_gad99c93772514004f757c09fb54ac6b5f.html</anchorfile>
      <anchor>gad99c93772514004f757c09fb54ac6b5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::agm</name>
      <anchorfile>group__core__arithmetic_ga9cde656e2fe72b65fe834806bda0ade5.html</anchorfile>
      <anchor>ga9cde656e2fe72b65fe834806bda0ade5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::average</name>
      <anchorfile>group__core__arithmetic_ga1718ca90633862e1c824380381d05f4f.html</anchorfile>
      <anchor>ga1718ca90633862e1c824380381d05f4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::ceil</name>
      <anchorfile>group__core__arithmetic_gaf450959dd53738dda62b4f4551cd7c11.html</anchorfile>
      <anchor>gaf450959dd53738dda62b4f4551cd7c11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::chi</name>
      <anchorfile>group__core__arithmetic_ga57f7296a0ce7eb3ef1ef0575aee93063.html</anchorfile>
      <anchor>ga57f7296a0ce7eb3ef1ef0575aee93063</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::clamp</name>
      <anchorfile>group__core__arithmetic_ga615259a38bc942276fe618e6621d536b.html</anchorfile>
      <anchor>ga615259a38bc942276fe618e6621d536b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::copysign</name>
      <anchorfile>group__core__arithmetic_ga8e000c8aaa19e94b4dd1f84d5191e8a4.html</anchorfile>
      <anchor>ga8e000c8aaa19e94b4dd1f84d5191e8a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::cosine_similarity</name>
      <anchorfile>group__core__arithmetic_gae42f1e89f46871950b9ec3175b3f0015.html</anchorfile>
      <anchor>gae42f1e89f46871950b9ec3175b3f0015</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::covariance</name>
      <anchorfile>group__core__arithmetic_gad85b8e8aca48a5e1db5ada47d8300950.html</anchorfile>
      <anchor>gad85b8e8aca48a5e1db5ada47d8300950</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::cumfun</name>
      <anchorfile>group__core__arithmetic_ga20f1f4d4503b8bdb9ce9aa854fde697f.html</anchorfile>
      <anchor>ga20f1f4d4503b8bdb9ce9aa854fde697f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::cumprod</name>
      <anchorfile>group__core__arithmetic_ga54ac3f9e05632d33033e149d784627f1.html</anchorfile>
      <anchor>ga54ac3f9e05632d33033e149d784627f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::cumsum</name>
      <anchorfile>group__core__arithmetic_ga6e39a9b0ba3dd0581d60a537c0b09e5e.html</anchorfile>
      <anchor>ga6e39a9b0ba3dd0581d60a537c0b09e5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::cumtrapz</name>
      <anchorfile>group__core__arithmetic_ga7f3104b5fdabcc5a06157c869cb4cfc1.html</anchorfile>
      <anchor>ga7f3104b5fdabcc5a06157c869cb4cfc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::dec</name>
      <anchorfile>group__core__arithmetic_ga44e2186aecde5f17445b39043094d85d.html</anchorfile>
      <anchor>ga44e2186aecde5f17445b39043094d85d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::diff</name>
      <anchorfile>group__core__arithmetic_ga057eabc3676fe1e9370bd201a21e97d7.html</anchorfile>
      <anchor>ga057eabc3676fe1e9370bd201a21e97d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::dist</name>
      <anchorfile>group__core__arithmetic_ga0278a079dfdeb50fcb31e27b3ac191f9.html</anchorfile>
      <anchor>ga0278a079dfdeb50fcb31e27b3ac191f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::div</name>
      <anchorfile>group__core__arithmetic_gaf14eacd69db8a64fecf63346475c37fb.html</anchorfile>
      <anchor>gaf14eacd69db8a64fecf63346475c37fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::dot</name>
      <anchorfile>group__core__arithmetic_ga9629bc8a3ce2a95e45bd49e118605156.html</anchorfile>
      <anchor>ga9629bc8a3ce2a95e45bd49e118605156</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::fdim</name>
      <anchorfile>group__core__arithmetic_ga6771e04ebcea3881df31805cedc97936.html</anchorfile>
      <anchor>ga6771e04ebcea3881df31805cedc97936</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::floor</name>
      <anchorfile>group__core__arithmetic_gad11a9abc8d039fa20ad0b7c1f307133d.html</anchorfile>
      <anchor>gad11a9abc8d039fa20ad0b7c1f307133d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::fmod</name>
      <anchorfile>group__core__arithmetic_ga8708102003ee2323f6bb449cc4f00384.html</anchorfile>
      <anchor>ga8708102003ee2323f6bb449cc4f00384</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::frac</name>
      <anchorfile>group__core__arithmetic_ga853653c494446e7321ec6bcc4e229bef.html</anchorfile>
      <anchor>ga853653c494446e7321ec6bcc4e229bef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::fracscale</name>
      <anchorfile>group__core__arithmetic_ga5c93230a3df7577707f9fbe32e470e37.html</anchorfile>
      <anchor>ga5c93230a3df7577707f9fbe32e470e37</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::heaviside</name>
      <anchorfile>group__core__arithmetic_ga961f3ecc560ee5d2bcabfe4dd63519d6.html</anchorfile>
      <anchor>ga961f3ecc560ee5d2bcabfe4dd63519d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::inc</name>
      <anchorfile>group__core__arithmetic_ga286feea728eff1a17edeb307b2aeab54.html</anchorfile>
      <anchor>ga286feea728eff1a17edeb307b2aeab54</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::lerp</name>
      <anchorfile>group__core__arithmetic_ga251fc4447bfae16b155723a7ba52b7ee.html</anchorfile>
      <anchor>ga251fc4447bfae16b155723a7ba52b7ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::manhattan</name>
      <anchorfile>group__core__arithmetic_ga38a5508b78008f2f5bd66008b5b0a60f.html</anchorfile>
      <anchor>ga38a5508b78008f2f5bd66008b5b0a60f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::max</name>
      <anchorfile>group__core__arithmetic_ga208ca607f968474fa9e4d016e0eb4e5f.html</anchorfile>
      <anchor>ga208ca607f968474fa9e4d016e0eb4e5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::maxabs</name>
      <anchorfile>group__core__arithmetic_ga93a4c90ace3fd4450ac5a3a6fe9004f1.html</anchorfile>
      <anchor>ga93a4c90ace3fd4450ac5a3a6fe9004f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::maxmag</name>
      <anchorfile>group__core__arithmetic_gadebe5f60fa3f0943b1deb3a58cea39f0.html</anchorfile>
      <anchor>gadebe5f60fa3f0943b1deb3a58cea39f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::min</name>
      <anchorfile>group__core__arithmetic_ga11d112beae386b529269a6ba2eb02471.html</anchorfile>
      <anchor>ga11d112beae386b529269a6ba2eb02471</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::minabs</name>
      <anchorfile>group__core__arithmetic_ga73f4a496ba999b5d065a0c21aaad0a04.html</anchorfile>
      <anchor>ga73f4a496ba999b5d065a0c21aaad0a04</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::minmag</name>
      <anchorfile>group__core__arithmetic_ga92cce254fcde7c4d9a7a55d320b6b3e9.html</anchorfile>
      <anchor>ga92cce254fcde7c4d9a7a55d320b6b3e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::minmax</name>
      <anchorfile>group__core__arithmetic_gab5afa8e5630450ad2ab117f96535356e.html</anchorfile>
      <anchor>gab5afa8e5630450ad2ab117f96535356e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::modf</name>
      <anchorfile>group__core__arithmetic_gaec55902ec0dd1ce8ec09bcda822dac81.html</anchorfile>
      <anchor>gaec55902ec0dd1ce8ec09bcda822dac81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::mul</name>
      <anchorfile>group__core__arithmetic_ga19c1e5e8e7a04678ee99fdc2bbff0e7b.html</anchorfile>
      <anchor>ga19c1e5e8e7a04678ee99fdc2bbff0e7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::negabsmax</name>
      <anchorfile>group__core__arithmetic_ga56d748dd6c74b235bc2aaad77391c9ac.html</anchorfile>
      <anchor>ga56d748dd6c74b235bc2aaad77391c9ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::negabsmin</name>
      <anchorfile>group__core__arithmetic_gabe2d9f7bc95472170c85bd1e9437cb45.html</anchorfile>
      <anchor>gabe2d9f7bc95472170c85bd1e9437cb45</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::negate</name>
      <anchorfile>group__core__arithmetic_ga204db0b8c77052a8a3eadc039abb2e73.html</anchorfile>
      <anchor>ga204db0b8c77052a8a3eadc039abb2e73</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::negatenz</name>
      <anchorfile>group__core__arithmetic_ga250e72507a1740ed75af67f72fc47d90.html</anchorfile>
      <anchor>ga250e72507a1740ed75af67f72fc47d90</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::negmaxabs</name>
      <anchorfile>group__core__arithmetic_ga7ab645c942cb4745b4f50947e2526527.html</anchorfile>
      <anchor>ga7ab645c942cb4745b4f50947e2526527</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::negminabs</name>
      <anchorfile>group__core__arithmetic_gabcdcf0169de90c64260492e8d2300bde.html</anchorfile>
      <anchor>gabcdcf0169de90c64260492e8d2300bde</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::oneminus</name>
      <anchorfile>group__core__arithmetic_ga06d1ba16e6d014da9fb540261012ad76.html</anchorfile>
      <anchor>ga06d1ba16e6d014da9fb540261012ad76</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rat</name>
      <anchorfile>group__core__arithmetic_gaaeb43898a1160bf5dd03cb5863075e83.html</anchorfile>
      <anchor>gaaeb43898a1160bf5dd03cb5863075e83</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rec</name>
      <anchorfile>group__core__arithmetic_ga25aad5d506c66c95818e1839a1855b12.html</anchorfile>
      <anchor>ga25aad5d506c66c95818e1839a1855b12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::reldist</name>
      <anchorfile>group__core__arithmetic_ga1f25877c9ddf62e0062c17f10be721b2.html</anchorfile>
      <anchor>ga1f25877c9ddf62e0062c17f10be721b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rem</name>
      <anchorfile>group__core__arithmetic_ga05a5bad217bfe7393357bece8e5ed056.html</anchorfile>
      <anchor>ga05a5bad217bfe7393357bece8e5ed056</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::remainder</name>
      <anchorfile>group__core__arithmetic_ga9c700f632f4d9140adfa0a52f0582629.html</anchorfile>
      <anchor>ga9c700f632f4d9140adfa0a52f0582629</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::round</name>
      <anchorfile>group__core__arithmetic_ga4bdec07dc764fd7a0f883f93ff293bde.html</anchorfile>
      <anchor>ga4bdec07dc764fd7a0f883f93ff293bde</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rsqrt</name>
      <anchorfile>group__core__arithmetic_gab38c68359b06e60ef729c35f061aa659.html</anchorfile>
      <anchor>gab38c68359b06e60ef729c35f061aa659</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::saturate</name>
      <anchorfile>group__core__arithmetic_ga0a217828149774983e6eb60664ed1330.html</anchorfile>
      <anchor>ga0a217828149774983e6eb60664ed1330</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sign</name>
      <anchorfile>group__core__arithmetic_ga219d427cb81fa248d0232ef2e91e65e4.html</anchorfile>
      <anchor>ga219d427cb81fa248d0232ef2e91e65e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sign_alternate</name>
      <anchorfile>group__core__arithmetic_ga7bda81fcc77e937ce4bac9801346e574.html</anchorfile>
      <anchor>ga7bda81fcc77e937ce4bac9801346e574</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::signnz</name>
      <anchorfile>group__core__arithmetic_ga58934cd97be4c2c274fdb3965221daa7.html</anchorfile>
      <anchor>ga58934cd97be4c2c274fdb3965221daa7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sqr</name>
      <anchorfile>group__core__arithmetic_ga044101b90ab7a146067d8cb1f76889eb.html</anchorfile>
      <anchor>ga044101b90ab7a146067d8cb1f76889eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sqrt</name>
      <anchorfile>group__core__arithmetic_ga641aa98b8a2c05bf5bfb4907d15faf37.html</anchorfile>
      <anchor>ga641aa98b8a2c05bf5bfb4907d15faf37</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sub</name>
      <anchorfile>group__core__arithmetic_ga7392fd608cc6fc3f1626491cd581616d.html</anchorfile>
      <anchor>ga7392fd608cc6fc3f1626491cd581616d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sum_of_squares</name>
      <anchorfile>group__core__arithmetic_ga69b984ff64182f743ac046245f284168.html</anchorfile>
      <anchor>ga69b984ff64182f743ac046245f284168</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::trunc</name>
      <anchorfile>group__core__arithmetic_ga5ebab1e2407219111f8d3916ad4e6819.html</anchorfile>
      <anchor>ga5ebab1e2407219111f8d3916ad4e6819</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::unfold</name>
      <anchorfile>group__core__arithmetic_gab00b0403241b47b4e0a7f3e2d8be4cfd.html</anchorfile>
      <anchor>gab00b0403241b47b4e0a7f3e2d8be4cfd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::variance</name>
      <anchorfile>group__core__arithmetic_ga28cc50956bdc395bb00ecef16bebb59d.html</anchorfile>
      <anchor>ga28cc50956bdc395bb00ecef16bebb59d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::welford_covariance</name>
      <anchorfile>group__core__arithmetic_ga3fee14a8a396f4ac89e650e0fb0768f7.html</anchorfile>
      <anchor>ga3fee14a8a396f4ac89e650e0fb0768f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::welford_variance</name>
      <anchorfile>group__core__arithmetic_ga6cfd55c36f3ce4f4137aa7b14f74f5ce.html</anchorfile>
      <anchor>ga6cfd55c36f3ce4f4137aa7b14f74f5ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::neville</name>
      <anchorfile>group__core__arithmetic_ga9410b950085a4299478368cdc4864e58.html</anchorfile>
      <anchor>ga9410b950085a4299478368cdc4864e58</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>bessel</name>
    <title>Bessel function</title>
    <filename>group__bessel.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::airy</name>
      <anchorfile>group__bessel_ga6c4d8609a742264dca4bdc09d023a22c.html</anchorfile>
      <anchor>ga6c4d8609a742264dca4bdc09d023a22c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::airy_ai</name>
      <anchorfile>group__bessel_ga8d4ff73facf4b69dff9df163055aa5f5.html</anchorfile>
      <anchor>ga8d4ff73facf4b69dff9df163055aa5f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::airy_bi</name>
      <anchorfile>group__bessel_gafe57d2b74c8426e5ab7229371b72c6df.html</anchorfile>
      <anchor>gafe57d2b74c8426e5ab7229371b72c6df</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core_bitops</name>
    <title>Bitwise functions</title>
    <filename>group__core__bitops.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_and</name>
      <anchorfile>group__core__bitops_gae3e108a8e508c1fb8b0aab2c4d76d00c.html</anchorfile>
      <anchor>gae3e108a8e508c1fb8b0aab2c4d76d00c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_andnot</name>
      <anchorfile>group__core__bitops_gafb23397d6d6a6c4208e3ea1d236fcbc5.html</anchorfile>
      <anchor>gafb23397d6d6a6c4208e3ea1d236fcbc5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_cast</name>
      <anchorfile>group__core__bitops_gab65bdc36d2fdc7b11cd170358578e744.html</anchorfile>
      <anchor>gab65bdc36d2fdc7b11cd170358578e744</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_ceil</name>
      <anchorfile>group__core__bitops_gaf7fc9d3210aeb2c8077472eded029bd4.html</anchorfile>
      <anchor>gaf7fc9d3210aeb2c8077472eded029bd4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_flip</name>
      <anchorfile>group__core__bitops_ga1f7c7ed9d58b598d960e7299c06d5e75.html</anchorfile>
      <anchor>ga1f7c7ed9d58b598d960e7299c06d5e75</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_floor</name>
      <anchorfile>group__core__bitops_gafc377f8e75a726776f8d9976767a7334.html</anchorfile>
      <anchor>gafc377f8e75a726776f8d9976767a7334</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_mask</name>
      <anchorfile>group__core__bitops_ga7f9fd1df011b15b9c45ea99d9a628386.html</anchorfile>
      <anchor>ga7f9fd1df011b15b9c45ea99d9a628386</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_not</name>
      <anchorfile>group__core__bitops_ga8e445eb95a6a531251dc42c0af01d630.html</anchorfile>
      <anchor>ga8e445eb95a6a531251dc42c0af01d630</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_notand</name>
      <anchorfile>group__core__bitops_ga286a27cb5dcd6b825c07c93b4261f348.html</anchorfile>
      <anchor>ga286a27cb5dcd6b825c07c93b4261f348</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_notor</name>
      <anchorfile>group__core__bitops_gae31ad364665fdbdd1cac042a7a6d86f2.html</anchorfile>
      <anchor>gae31ad364665fdbdd1cac042a7a6d86f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_or</name>
      <anchorfile>group__core__bitops_gae4baca10d3834da1bedb3d6e1a795fd2.html</anchorfile>
      <anchor>gae4baca10d3834da1bedb3d6e1a795fd2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_ornot</name>
      <anchorfile>group__core__bitops_ga853007cb7c7071b4ce7a8512bdf30589.html</anchorfile>
      <anchor>ga853007cb7c7071b4ce7a8512bdf30589</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_reverse</name>
      <anchorfile>group__core__bitops_ga0050537e0c11470348add6553252bcf1.html</anchorfile>
      <anchor>ga0050537e0c11470348add6553252bcf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_select</name>
      <anchorfile>group__core__bitops_ga83c87079ec3aa4037974b9a319aa3c5a.html</anchorfile>
      <anchor>ga83c87079ec3aa4037974b9a319aa3c5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_set</name>
      <anchorfile>group__core__bitops_ga2582766c752f3b2cff7650c511711aaa.html</anchorfile>
      <anchor>ga2582766c752f3b2cff7650c511711aaa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_shl</name>
      <anchorfile>group__core__bitops_gad35ee755a985994eb93b8dde1fac8a09.html</anchorfile>
      <anchor>gad35ee755a985994eb93b8dde1fac8a09</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_shr</name>
      <anchorfile>group__core__bitops_gafca1861f7d0524b057e04d120df08aff.html</anchorfile>
      <anchor>gafca1861f7d0524b057e04d120df08aff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_swap_adjacent</name>
      <anchorfile>group__core__bitops_ga848f5d866de05cbb3c51b2efb8a6d6f5.html</anchorfile>
      <anchor>ga848f5d866de05cbb3c51b2efb8a6d6f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_swap_pairs</name>
      <anchorfile>group__core__bitops_ga4cbb358e89585c3c8d97d0f06871237d.html</anchorfile>
      <anchor>ga4cbb358e89585c3c8d97d0f06871237d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_ternary</name>
      <anchorfile>group__core__bitops_gadbcf7304c34de136c4c62b68ceaa19cb.html</anchorfile>
      <anchor>gadbcf7304c34de136c4c62b68ceaa19cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_unset</name>
      <anchorfile>group__core__bitops_ga597af6519e08a7019c10310ec3c722c2.html</anchorfile>
      <anchor>ga597af6519e08a7019c10310ec3c722c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_width</name>
      <anchorfile>group__core__bitops_ga82d1cef2e8de85d04ae37cca2fe43759.html</anchorfile>
      <anchor>ga82d1cef2e8de85d04ae37cca2fe43759</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bit_xor</name>
      <anchorfile>group__core__bitops_ga6c8a73d644a582b4684e31c5239e4529.html</anchorfile>
      <anchor>ga6c8a73d644a582b4684e31c5239e4529</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::byte_reverse</name>
      <anchorfile>group__core__bitops_gab21caf2aeece0c2486bd80d7e5d9dc2c.html</anchorfile>
      <anchor>gab21caf2aeece0c2486bd80d7e5d9dc2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::byte_swap_adjacent</name>
      <anchorfile>group__core__bitops_ga26b08595fa85a206ed5bd09848338f55.html</anchorfile>
      <anchor>ga26b08595fa85a206ed5bd09848338f55</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::byte_swap_pairs</name>
      <anchorfile>group__core__bitops_ga030e462fe0a8e9815b08326264d106bd.html</anchorfile>
      <anchor>ga030e462fe0a8e9815b08326264d106bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::countl_one</name>
      <anchorfile>group__core__bitops_ga987af1c5145d33608dbbac832278d990.html</anchorfile>
      <anchor>ga987af1c5145d33608dbbac832278d990</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::countl_zero</name>
      <anchorfile>group__core__bitops_ga13f2d665c65670451c8e6b682bbd4430.html</anchorfile>
      <anchor>ga13f2d665c65670451c8e6b682bbd4430</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::countr_one</name>
      <anchorfile>group__core__bitops_ga7e569a2aab386aa1260facc3f91bbaff.html</anchorfile>
      <anchor>ga7e569a2aab386aa1260facc3f91bbaff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::countr_zero</name>
      <anchorfile>group__core__bitops_ga6d1332c0e797bcc8980f62da2b781edb.html</anchorfile>
      <anchor>ga6d1332c0e797bcc8980f62da2b781edb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::firstbitset</name>
      <anchorfile>group__core__bitops_gafd77ecd10dc25572885742db87361954.html</anchorfile>
      <anchor>gafd77ecd10dc25572885742db87361954</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::firstbitunset</name>
      <anchorfile>group__core__bitops_gafbcb9ca39f89d47f3fe847e1f3fdf3fa.html</anchorfile>
      <anchor>gafbcb9ca39f89d47f3fe847e1f3fdf3fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::hi</name>
      <anchorfile>group__core__bitops_gac36375f33a27d2122d4ca0f3a006f7b2.html</anchorfile>
      <anchor>gac36375f33a27d2122d4ca0f3a006f7b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::lo</name>
      <anchorfile>group__core__bitops_ga61fa2a64540198462d0aed12e93967a1.html</anchorfile>
      <anchor>ga61fa2a64540198462d0aed12e93967a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::lohi</name>
      <anchorfile>group__core__bitops_gaaf5061a57a817fcd65de7dc459bd465b.html</anchorfile>
      <anchor>gaaf5061a57a817fcd65de7dc459bd465b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::popcount</name>
      <anchorfile>group__core__bitops_gaae5db78cfc6d7dbce0141f945d1516d7.html</anchorfile>
      <anchor>gaae5db78cfc6d7dbce0141f945d1516d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rotl</name>
      <anchorfile>group__core__bitops_ga4edb8cc8f3593c76c58eb1f5d899ac33.html</anchorfile>
      <anchor>ga4edb8cc8f3593c76c58eb1f5d899ac33</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rotr</name>
      <anchorfile>group__core__bitops_gab9aac42187ea93d7b3d7d1f0c7e45f6a.html</anchorfile>
      <anchor>gab9aac42187ea93d7b3d7d1f0c7e45f6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rshl</name>
      <anchorfile>group__core__bitops_gad18e8c9ab65a31f90fdc12535fca137b.html</anchorfile>
      <anchor>gad18e8c9ab65a31f90fdc12535fca137b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rshr</name>
      <anchorfile>group__core__bitops_ga945a9cad6f4e83840ac6a4e7782af905.html</anchorfile>
      <anchor>ga945a9cad6f4e83840ac6a4e7782af905</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::shl</name>
      <anchorfile>group__core__bitops_ga82ed4cebb5bca3c352beda164a91f2e9.html</anchorfile>
      <anchor>ga82ed4cebb5bca3c352beda164a91f2e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::shr</name>
      <anchorfile>group__core__bitops_ga1636e7a14e4a1421521f63cc5d815f8f.html</anchorfile>
      <anchor>ga1636e7a14e4a1421521f63cc5d815f8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::swap_pairs</name>
      <anchorfile>group__core__bitops_ga10b54df6fa2ae24f1f0d6334e2c5be1b.html</anchorfile>
      <anchor>ga10b54df6fa2ae24f1f0d6334e2c5be1b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>combinatorial</name>
    <title>Combinatorial functions</title>
    <filename>group__combinatorial.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bernouilli</name>
      <anchorfile>group__combinatorial_ga593a2a4580b4130dcfdf334a86a16409.html</anchorfile>
      <anchor>ga593a2a4580b4130dcfdf334a86a16409</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::fibonacci</name>
      <anchorfile>group__combinatorial_ga53fabf7d60ead52b043a80c3733f3567.html</anchorfile>
      <anchor>ga53fabf7d60ead52b043a80c3733f3567</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::gcd</name>
      <anchorfile>group__combinatorial_gadcf37697731fa4c94ebe972425b2dbc3.html</anchorfile>
      <anchor>gadcf37697731fa4c94ebe972425b2dbc3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::lcm</name>
      <anchorfile>group__combinatorial_ga6a5fc60b3c1e87c5f71b5c51f5b664b5.html</anchorfile>
      <anchor>ga6a5fc60b3c1e87c5f71b5c51f5b664b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::nth_prime</name>
      <anchorfile>group__combinatorial_ga07a4c4bd17dd7be0c16010a39d9d9d93.html</anchorfile>
      <anchor>ga07a4c4bd17dd7be0c16010a39d9d9d93</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::prime_ceil</name>
      <anchorfile>group__combinatorial_ga4da0702dc11efa19b527fe8020267bf5.html</anchorfile>
      <anchor>ga4da0702dc11efa19b527fe8020267bf5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::prime_floor</name>
      <anchorfile>group__combinatorial_gab62baf715bca909acd246288c46f68b3.html</anchorfile>
      <anchor>gab62baf715bca909acd246288c46f68b3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core_compress</name>
    <title>Compress functions</title>
    <filename>group__core__compress.html</filename>
    <member kind="variable">
      <type>constexpr callable_compress_</type>
      <name>eve::compress</name>
      <anchorfile>group__core__compress_gafec1baa8724fc7e106d718836053db7c.html</anchorfile>
      <anchor>gafec1baa8724fc7e106d718836053db7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::compress_copy</name>
      <anchorfile>group__core__compress_ga8e545371fd605df1555e4cd0b2f62374.html</anchorfile>
      <anchor>ga8e545371fd605df1555e4cd0b2f62374</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::compress_store</name>
      <anchorfile>group__core__compress_ga621a2ba91bb1c5a07e5a51b87ebd5c06.html</anchorfile>
      <anchor>ga621a2ba91bb1c5a07e5a51b87ebd5c06</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>conditional</name>
    <title>Conditional Expressions</title>
    <filename>group__conditional.html</filename>
    <class kind="struct">eve::or_</class>
    <class kind="struct">eve::if_</class>
    <class kind="struct">eve::ignore_all_</class>
    <class kind="struct">eve::ignore_none_</class>
    <class kind="struct">eve::keep_first</class>
    <class kind="struct">eve::ignore_last</class>
    <class kind="struct">eve::keep_last</class>
    <class kind="struct">eve::ignore_first</class>
    <class kind="struct">eve::keep_between</class>
    <class kind="struct">eve::ignore_extrema</class>
    <member kind="function">
      <type>constexpr auto</type>
      <name>eve::drop_alternative</name>
      <anchorfile>group__conditional_ga8265bd793db77b43d12988c1c297f00b.html</anchorfile>
      <anchor>ga8265bd793db77b43d12988c1c297f00b</anchor>
      <arglist>(C c)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>eve::map_alternative</name>
      <anchorfile>group__conditional_ga6b75905a0b2d6320cadb973c752a8cd1.html</anchorfile>
      <anchor>ga6b75905a0b2d6320cadb973c752a8cd1</anchor>
      <arglist>(C c, auto op)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>eve::bit_cast_alternative</name>
      <anchorfile>group__conditional_gaba39b1743e4775c0c19966dac6342762.html</anchorfile>
      <anchor>gaba39b1743e4775c0c19966dac6342762</anchor>
      <arglist>(C c, as&lt; Tgt &gt; tgt)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>eve::reverse_conditional</name>
      <anchorfile>group__conditional_gab99c14f8c7e6cd5fc693a79c97bc89d8.html</anchorfile>
      <anchor>gab99c14f8c7e6cd5fc693a79c97bc89d8</anchor>
      <arglist>(C c, eve::as&lt; T &gt; tgt)</arglist>
    </member>
    <member kind="variable">
      <type>constexpr ignore_all_</type>
      <name>eve::ignore_all</name>
      <anchorfile>group__conditional.html</anchorfile>
      <anchor>ga6ce7ac450593ee98fe8ca0d9cf65e4b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr ignore_none_</type>
      <name>eve::ignore_none</name>
      <anchorfile>group__conditional.html</anchorfile>
      <anchor>gae234dce7533ecc38fe2c70fd69383633</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core_constants</name>
    <title>Constants</title>
    <filename>group__core__constants.html</filename>
    <namespace>eve::_</namespace>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::allbits</name>
      <anchorfile>group__core__constants_gafec20985737ed747df5f5f3be1469c6a.html</anchorfile>
      <anchor>gafec20985737ed747df5f5f3be1469c6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bitincrement</name>
      <anchorfile>group__core__constants_ga8ac2e1af8d69203e7c682b328de94097.html</anchorfile>
      <anchor>ga8ac2e1af8d69203e7c682b328de94097</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::eps</name>
      <anchorfile>group__core__constants_ga3a08ea3bf1e679ed4ef0576ddffff08a.html</anchorfile>
      <anchor>ga3a08ea3bf1e679ed4ef0576ddffff08a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::exponentmask</name>
      <anchorfile>group__core__constants_ga15630d42e0187a51aa629ecc00dbe7e7.html</anchorfile>
      <anchor>ga15630d42e0187a51aa629ecc00dbe7e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::false_</name>
      <anchorfile>group__core__constants_gae7b8b0fcffea34e1d766e0db525ce223.html</anchorfile>
      <anchor>gae7b8b0fcffea34e1d766e0db525ce223</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::half</name>
      <anchorfile>group__core__constants_ga615c9124768fecc05e04d58ae24f8870.html</anchorfile>
      <anchor>ga615c9124768fecc05e04d58ae24f8870</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::inf</name>
      <anchorfile>group__core__constants_ga8a568ccc9a870bc971851209c836bc63.html</anchorfile>
      <anchor>ga8a568ccc9a870bc971851209c836bc63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::iota</name>
      <anchorfile>group__core__constants_ga45b9b51c21e6aa1d7879dd2b68f886af.html</anchorfile>
      <anchor>ga45b9b51c21e6aa1d7879dd2b68f886af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::logeps</name>
      <anchorfile>group__core__constants_ga9bd28cd479c5b123576e291079c92252.html</anchorfile>
      <anchor>ga9bd28cd479c5b123576e291079c92252</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::majorant</name>
      <anchorfile>group__core__constants_ga2544f12d841d878129a13f0fab8d1d21.html</anchorfile>
      <anchor>ga2544f12d841d878129a13f0fab8d1d21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::mantissamask</name>
      <anchorfile>group__core__constants_gacf720a49d31c18bade023482b9e7c3d7.html</anchorfile>
      <anchor>gacf720a49d31c18bade023482b9e7c3d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::max_safe_integer</name>
      <anchorfile>group__core__constants_gab391c95d967bf4d809e42b77fa21ab1d.html</anchorfile>
      <anchor>gab391c95d967bf4d809e42b77fa21ab1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::maxexponent</name>
      <anchorfile>group__core__constants_ga44e6675c343b28dca02c76705b40f854.html</anchorfile>
      <anchor>ga44e6675c343b28dca02c76705b40f854</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::maxexponentm1</name>
      <anchorfile>group__core__constants_gad11242a44d43460b85f35dc488e60d44.html</anchorfile>
      <anchor>gad11242a44d43460b85f35dc488e60d44</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::maxexponentp1</name>
      <anchorfile>group__core__constants_gad0fab24db7ab730a02c643c3237a7474.html</anchorfile>
      <anchor>gad0fab24db7ab730a02c643c3237a7474</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::maxflint</name>
      <anchorfile>group__core__constants_gaeee06bbd7d417e000d05bd801a3b8c85.html</anchorfile>
      <anchor>gaeee06bbd7d417e000d05bd801a3b8c85</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::maxrepint</name>
      <anchorfile>group__core__constants_gac0365cd157f1c08a778de3876e4e8f77.html</anchorfile>
      <anchor>gac0365cd157f1c08a778de3876e4e8f77</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::mhalf</name>
      <anchorfile>group__core__constants_ga7e79770188ed1bff8006179660157182.html</anchorfile>
      <anchor>ga7e79770188ed1bff8006179660157182</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::minexponent</name>
      <anchorfile>group__core__constants_ga59cbceaa5903da81191784af48fed2c4.html</anchorfile>
      <anchor>ga59cbceaa5903da81191784af48fed2c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::minorant</name>
      <anchorfile>group__core__constants_gaf7260a29fbb85cf0cfd97ad1d130c07c.html</anchorfile>
      <anchor>gaf7260a29fbb85cf0cfd97ad1d130c07c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::mone</name>
      <anchorfile>group__core__constants_ga5628ae5a0568eaa5e4672e3e63b6db35.html</anchorfile>
      <anchor>ga5628ae5a0568eaa5e4672e3e63b6db35</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::mzero</name>
      <anchorfile>group__core__constants_ga5551a5df5e64f90f6c9f498cc34f2b48.html</anchorfile>
      <anchor>ga5551a5df5e64f90f6c9f498cc34f2b48</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::nan</name>
      <anchorfile>group__core__constants_ga34b67924fa53bec83dfc96b51bd8fe56.html</anchorfile>
      <anchor>ga34b67924fa53bec83dfc96b51bd8fe56</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::nbmantissabits</name>
      <anchorfile>group__core__constants_gab41a973941d389c6f72a75c0c67cf0aa.html</anchorfile>
      <anchor>gab41a973941d389c6f72a75c0c67cf0aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::one</name>
      <anchorfile>group__core__constants_gac66f3d66fece21b4454e79500cc56f84.html</anchorfile>
      <anchor>gac66f3d66fece21b4454e79500cc56f84</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::oneosqrteps</name>
      <anchorfile>group__core__constants_gaa4dee4a2fdd3007c7da25099e85ea347.html</anchorfile>
      <anchor>gaa4dee4a2fdd3007c7da25099e85ea347</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::signmask</name>
      <anchorfile>group__core__constants_ga25424bccdc3f3ea6a6b9708532d15b05.html</anchorfile>
      <anchor>ga25424bccdc3f3ea6a6b9708532d15b05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::smallestposval</name>
      <anchorfile>group__core__constants_gadf2de69a7c166758ea2c4643e0fae62e.html</anchorfile>
      <anchor>gadf2de69a7c166758ea2c4643e0fae62e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sqrteps</name>
      <anchorfile>group__core__constants_gaaf00b43c0dea1f135df9d2ac07b740a5.html</anchorfile>
      <anchor>gaaf00b43c0dea1f135df9d2ac07b740a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sqrtsmallestposval</name>
      <anchorfile>group__core__constants_ga7eabdcaa9c3ff3d84982115706c2295b.html</anchorfile>
      <anchor>ga7eabdcaa9c3ff3d84982115706c2295b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sqrtvalmax</name>
      <anchorfile>group__core__constants_gae61c7e9e1fdc501c543f2281a83242af.html</anchorfile>
      <anchor>gae61c7e9e1fdc501c543f2281a83242af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::true_</name>
      <anchorfile>group__core__constants_ga38f80597f70583a4be7fcc9ac558af95.html</anchorfile>
      <anchor>ga38f80597f70583a4be7fcc9ac558af95</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::twotonmb</name>
      <anchorfile>group__core__constants_ga68cec35679af23cec74599650704d4ee.html</anchorfile>
      <anchor>ga68cec35679af23cec74599650704d4ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::valmax</name>
      <anchorfile>group__core__constants_ga85073f11abb76d43faf07742435ea083.html</anchorfile>
      <anchor>ga85073f11abb76d43faf07742435ea083</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::valmin</name>
      <anchorfile>group__core__constants_ga1fd45a655473cde0022e08497eba14c1.html</anchorfile>
      <anchor>ga1fd45a655473cde0022e08497eba14c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::zero</name>
      <anchorfile>group__core__constants_gab4ecebb6ef8d0c73695dee1eb7371e6f.html</anchorfile>
      <anchor>gab4ecebb6ef8d0c73695dee1eb7371e6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::oneotwoeps</name>
      <anchorfile>group__core__constants_ga32a23889e11125f0d2248d10ba03d936.html</anchorfile>
      <anchor>ga32a23889e11125f0d2248d10ba03d936</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>math_constants</name>
    <title>Constants</title>
    <filename>group__math__constants.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::catalan</name>
      <anchorfile>group__math__constants_gac7a7c4180b2ec7b09cf29b961ffe4207.html</anchorfile>
      <anchor>gac7a7c4180b2ec7b09cf29b961ffe4207</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::cbrt_pi</name>
      <anchorfile>group__math__constants_gab069af5ddba0ea1f3a03653ba24343db.html</anchorfile>
      <anchor>gab069af5ddba0ea1f3a03653ba24343db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::cos_1</name>
      <anchorfile>group__math__constants_gad01a36b3aa434488a6a5dc7497646414.html</anchorfile>
      <anchor>gad01a36b3aa434488a6a5dc7497646414</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::cosh_1</name>
      <anchorfile>group__math__constants_ga6589c51da226fced3dad18eb5496d1bd.html</anchorfile>
      <anchor>ga6589c51da226fced3dad18eb5496d1bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::egamma</name>
      <anchorfile>group__math__constants_gaaf04325ae522d9fbd5b8e38fa64093b0.html</anchorfile>
      <anchor>gaaf04325ae522d9fbd5b8e38fa64093b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::egamma_sqr</name>
      <anchorfile>group__math__constants_ga9968fbd2955d1569c6e53ebc59744e72.html</anchorfile>
      <anchor>ga9968fbd2955d1569c6e53ebc59744e72</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::epso_2</name>
      <anchorfile>group__math__constants_gac43f9b9a247aab13dd9cf20b28fc10d8.html</anchorfile>
      <anchor>gac43f9b9a247aab13dd9cf20b28fc10d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::euler</name>
      <anchorfile>group__math__constants_ga7c4605cd6be76809b63a68a1d909a00c.html</anchorfile>
      <anchor>ga7c4605cd6be76809b63a68a1d909a00c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::exp_pi</name>
      <anchorfile>group__math__constants_ga561b96f79786fa99e4e2aaf2e52372e2.html</anchorfile>
      <anchor>ga561b96f79786fa99e4e2aaf2e52372e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::extreme_value_skewness</name>
      <anchorfile>group__math__constants_ga8ba551f79aa6782d07eab6c3d7e0a9db.html</anchorfile>
      <anchor>ga8ba551f79aa6782d07eab6c3d7e0a9db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::four_minus_pi</name>
      <anchorfile>group__math__constants_ga0784bcf60e8fbb5cfb4c3dab0524cb54.html</anchorfile>
      <anchor>ga0784bcf60e8fbb5cfb4c3dab0524cb54</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::four_pio_3</name>
      <anchorfile>group__math__constants_gae304b0433f5cb2914d26d50a4172580b.html</anchorfile>
      <anchor>gae304b0433f5cb2914d26d50a4172580b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::glaisher</name>
      <anchorfile>group__math__constants_ga389fcb593b079afea5381d192593443e.html</anchorfile>
      <anchor>ga389fcb593b079afea5381d192593443e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::inv_2eps</name>
      <anchorfile>group__math__constants_ga1bf4ef37949b047159c2fe76891b2128.html</anchorfile>
      <anchor>ga1bf4ef37949b047159c2fe76891b2128</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::inv_2pi</name>
      <anchorfile>group__math__constants_ga7c2cbb2571a968c8badadff961dad2d6.html</anchorfile>
      <anchor>ga7c2cbb2571a968c8badadff961dad2d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::inv_e</name>
      <anchorfile>group__math__constants_ga60b0ff3b86604d509f59e0ad29e42a21.html</anchorfile>
      <anchor>ga60b0ff3b86604d509f59e0ad29e42a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::inv_egamma</name>
      <anchorfile>group__math__constants_ga0bfad4bd0a9df3a00a657ec8c1127204.html</anchorfile>
      <anchor>ga0bfad4bd0a9df3a00a657ec8c1127204</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::inv_pi</name>
      <anchorfile>group__math__constants_ga031989587324a6dcb910db1cb2f09277.html</anchorfile>
      <anchor>ga031989587324a6dcb910db1cb2f09277</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::invcbrt_pi</name>
      <anchorfile>group__math__constants_gaf3efc2364120e6cfeef1c0ac42f770b7.html</anchorfile>
      <anchor>gaf3efc2364120e6cfeef1c0ac42f770b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::invlog10_2</name>
      <anchorfile>group__math__constants_ga2bee64fb1d01a859a4f5e7fc53f40209.html</anchorfile>
      <anchor>ga2bee64fb1d01a859a4f5e7fc53f40209</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::invlog10_e</name>
      <anchorfile>group__math__constants_ga61bf20009c23f002c671cc0cc455f11d.html</anchorfile>
      <anchor>ga61bf20009c23f002c671cc0cc455f11d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::invlog_10</name>
      <anchorfile>group__math__constants_ga3ec8fc7af4d1061cf26cd3a86fcb2f5b.html</anchorfile>
      <anchor>ga3ec8fc7af4d1061cf26cd3a86fcb2f5b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::invlog_2</name>
      <anchorfile>group__math__constants_ga9ba50324960abc54154061fcdfe2b1cf.html</anchorfile>
      <anchor>ga9ba50324960abc54154061fcdfe2b1cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::invlog_phi</name>
      <anchorfile>group__math__constants_gaefdaed5634b30722880246eded19a349.html</anchorfile>
      <anchor>gaefdaed5634b30722880246eded19a349</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::invsqrt_2</name>
      <anchorfile>group__math__constants_gae881f37b4c6c017454ed2099056e4b75.html</anchorfile>
      <anchor>gae881f37b4c6c017454ed2099056e4b75</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::khinchin</name>
      <anchorfile>group__math__constants_ga0741808f95c071aa804ddb0bd4488558.html</anchorfile>
      <anchor>ga0741808f95c071aa804ddb0bd4488558</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::log10_e</name>
      <anchorfile>group__math__constants_ga6572c51acce451620fdfeeb5c450160e.html</anchorfile>
      <anchor>ga6572c51acce451620fdfeeb5c450160e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::log2_e</name>
      <anchorfile>group__math__constants_ga78368627f2d3836197ba8e93c320e04e.html</anchorfile>
      <anchor>ga78368627f2d3836197ba8e93c320e04e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::log_10</name>
      <anchorfile>group__math__constants_ga67f008299fc82c71284a8b8777d4c13f.html</anchorfile>
      <anchor>ga67f008299fc82c71284a8b8777d4c13f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::log_2</name>
      <anchorfile>group__math__constants_gad4e63cd8d3bcf7c4bccf78fc2e902315.html</anchorfile>
      <anchor>gad4e63cd8d3bcf7c4bccf78fc2e902315</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::log_phi</name>
      <anchorfile>group__math__constants_ga85165c7097e6135d0804805a856194aa.html</anchorfile>
      <anchor>ga85165c7097e6135d0804805a856194aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::loglog_2</name>
      <anchorfile>group__math__constants_gac03d1d99c5aafd52b88953e5594087ef.html</anchorfile>
      <anchor>gac03d1d99c5aafd52b88953e5594087ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::maxlog</name>
      <anchorfile>group__math__constants_gafa58266d667db8fb77cd37f20c2f2b69.html</anchorfile>
      <anchor>gafa58266d667db8fb77cd37f20c2f2b69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::maxlog10</name>
      <anchorfile>group__math__constants_gab48684a50934f99095f9c4a3ff2d1bdc.html</anchorfile>
      <anchor>gab48684a50934f99095f9c4a3ff2d1bdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::maxlog2</name>
      <anchorfile>group__math__constants_ga93af75df7ea588f88e33d6781acae79c.html</anchorfile>
      <anchor>ga93af75df7ea588f88e33d6781acae79c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::minlog</name>
      <anchorfile>group__math__constants_ga6d5d71fa95856c09415f3ae7eefaea69.html</anchorfile>
      <anchor>ga6d5d71fa95856c09415f3ae7eefaea69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::minlog10</name>
      <anchorfile>group__math__constants_ga12317003697b491ab0886a8e0ae9bf5b.html</anchorfile>
      <anchor>ga12317003697b491ab0886a8e0ae9bf5b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::minlog10denormal</name>
      <anchorfile>group__math__constants_gae0d7fb87d55d1fdfaf3dd7eef0938491.html</anchorfile>
      <anchor>gae0d7fb87d55d1fdfaf3dd7eef0938491</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::minlog2</name>
      <anchorfile>group__math__constants_gaef0f85c3c53085c44bc5aebd7b7aa03f.html</anchorfile>
      <anchor>gaef0f85c3c53085c44bc5aebd7b7aa03f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::minlog2denormal</name>
      <anchorfile>group__math__constants_ga5854afd87abfbd4c57ccc263b293832c.html</anchorfile>
      <anchor>ga5854afd87abfbd4c57ccc263b293832c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::minlogdenormal</name>
      <anchorfile>group__math__constants_ga611180d8bd14d97e4441f754975d31fb.html</anchorfile>
      <anchor>ga611180d8bd14d97e4441f754975d31fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::phi</name>
      <anchorfile>group__math__constants_ga0f8fbe6ec946f1ecfc3e2463ab90db22.html</anchorfile>
      <anchor>ga0f8fbe6ec946f1ecfc3e2463ab90db22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pi</name>
      <anchorfile>group__math__constants_gad32687fc782ada2bb223abb7722ac694.html</anchorfile>
      <anchor>gad32687fc782ada2bb223abb7722ac694</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pi2</name>
      <anchorfile>group__math__constants_gac2e73b089c8b271d073b845856d3052b.html</anchorfile>
      <anchor>gac2e73b089c8b271d073b845856d3052b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pi2o_16</name>
      <anchorfile>group__math__constants_ga87749930f03f4a15467a789f530cbe57.html</anchorfile>
      <anchor>ga87749930f03f4a15467a789f530cbe57</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pi2o_6</name>
      <anchorfile>group__math__constants_gadd155e6b827ca3694423a877b409d135.html</anchorfile>
      <anchor>gadd155e6b827ca3694423a877b409d135</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pi3</name>
      <anchorfile>group__math__constants_gac6703b19d696ecf60c0040bc1012e626.html</anchorfile>
      <anchor>gac6703b19d696ecf60c0040bc1012e626</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pi_minus_3</name>
      <anchorfile>group__math__constants_gabaefb982c5df157545673ba9c903208f.html</anchorfile>
      <anchor>gabaefb982c5df157545673ba9c903208f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pi_pow_e</name>
      <anchorfile>group__math__constants_ga1376aa14dc0d8a08351ebb804b11f793.html</anchorfile>
      <anchor>ga1376aa14dc0d8a08351ebb804b11f793</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pio_2</name>
      <anchorfile>group__math__constants_gabd8e0faaa62af384db4334f953957003.html</anchorfile>
      <anchor>gabd8e0faaa62af384db4334f953957003</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pio_3</name>
      <anchorfile>group__math__constants_gac30b29df2f7d7903ac7e0097a51b22e4.html</anchorfile>
      <anchor>gac30b29df2f7d7903ac7e0097a51b22e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pio_4</name>
      <anchorfile>group__math__constants_ga2a706e8a2c1d95d557f32f1aa54d1ada.html</anchorfile>
      <anchor>ga2a706e8a2c1d95d557f32f1aa54d1ada</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pio_6</name>
      <anchorfile>group__math__constants_ga61628074a13f5a890b80f5338f7ad6c6.html</anchorfile>
      <anchor>ga61628074a13f5a890b80f5338f7ad6c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::quarter</name>
      <anchorfile>group__math__constants_gaac85860bbe1492610ac1caeeb974d662.html</anchorfile>
      <anchor>gaac85860bbe1492610ac1caeeb974d662</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rayleigh_kurtosis</name>
      <anchorfile>group__math__constants_ga230bfcaf73e0c37bc4bc27d57129a049.html</anchorfile>
      <anchor>ga230bfcaf73e0c37bc4bc27d57129a049</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rayleigh_kurtosis_excess</name>
      <anchorfile>group__math__constants_gaec7fc28f375ffcb697a9467b71248a58.html</anchorfile>
      <anchor>gaec7fc28f375ffcb697a9467b71248a58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rayleigh_skewness</name>
      <anchorfile>group__math__constants_gaa4e2225fb86237345c41da2f5a08fd95.html</anchorfile>
      <anchor>gaa4e2225fb86237345c41da2f5a08fd95</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rsqrt_2pi</name>
      <anchorfile>group__math__constants_ga1337a8283c8fca82730d3531f2f3dbfd.html</anchorfile>
      <anchor>ga1337a8283c8fca82730d3531f2f3dbfd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rsqrt_e</name>
      <anchorfile>group__math__constants_ga7fc0e36604c0b1991333ee301ac7fc5a.html</anchorfile>
      <anchor>ga7fc0e36604c0b1991333ee301ac7fc5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rsqrt_pi</name>
      <anchorfile>group__math__constants_gaebae899c8044c16bc129e39cdf810be0.html</anchorfile>
      <anchor>gaebae899c8044c16bc129e39cdf810be0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rsqrt_pio_2</name>
      <anchorfile>group__math__constants_ga1c0ad8a9dcef2a7396e04ae471224d6e.html</anchorfile>
      <anchor>ga1c0ad8a9dcef2a7396e04ae471224d6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sin_1</name>
      <anchorfile>group__math__constants_ga3c80d591964d0c7b6f022c15e8bd20ab.html</anchorfile>
      <anchor>ga3c80d591964d0c7b6f022c15e8bd20ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sinh_1</name>
      <anchorfile>group__math__constants_ga5d9e23b8dba4be11f68af135e984fd3e.html</anchorfile>
      <anchor>ga5d9e23b8dba4be11f68af135e984fd3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sixth</name>
      <anchorfile>group__math__constants_ga34d09c7266d9a9f15cd63151b15778e2.html</anchorfile>
      <anchor>ga34d09c7266d9a9f15cd63151b15778e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sqrt_2</name>
      <anchorfile>group__math__constants_ga95a581729f417a842b6fa19d56367e9b.html</anchorfile>
      <anchor>ga95a581729f417a842b6fa19d56367e9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sqrt_2pi</name>
      <anchorfile>group__math__constants_gaa25145cc047e71fb561f7504137da7b0.html</anchorfile>
      <anchor>gaa25145cc047e71fb561f7504137da7b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sqrt_3</name>
      <anchorfile>group__math__constants_ga08f5fe4d0413da671c65f6a731877cfd.html</anchorfile>
      <anchor>ga08f5fe4d0413da671c65f6a731877cfd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sqrt_e</name>
      <anchorfile>group__math__constants_ga7a2f229e61a2c0ac27237c40e79c4db6.html</anchorfile>
      <anchor>ga7a2f229e61a2c0ac27237c40e79c4db6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sqrt_pi</name>
      <anchorfile>group__math__constants_ga0418152acbbcccd3839043a19905f3a7.html</anchorfile>
      <anchor>ga0418152acbbcccd3839043a19905f3a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sqrt_pio_2</name>
      <anchorfile>group__math__constants_gaf43401e8a277208e868bd1d990dd1e8d.html</anchorfile>
      <anchor>gaf43401e8a277208e868bd1d990dd1e8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sqrtlog_4</name>
      <anchorfile>group__math__constants_ga5f32b34733fec39e6cabd220d777d232.html</anchorfile>
      <anchor>ga5f32b34733fec39e6cabd220d777d232</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::third</name>
      <anchorfile>group__math__constants_ga2aa6df7f999fda8b7d9383257d6ad93d.html</anchorfile>
      <anchor>ga2aa6df7f999fda8b7d9383257d6ad93d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::three_o_4</name>
      <anchorfile>group__math__constants_ga62fbd8d516967e29ea1999be485539ec.html</anchorfile>
      <anchor>ga62fbd8d516967e29ea1999be485539ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::three_pio_4</name>
      <anchorfile>group__math__constants_gaeaac995add2aac154468e039c9e5d441.html</anchorfile>
      <anchor>gaeaac995add2aac154468e039c9e5d441</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::two_o_3</name>
      <anchorfile>group__math__constants_ga1e6352f3eb3f929ad1f0d355a2384e0b.html</anchorfile>
      <anchor>ga1e6352f3eb3f929ad1f0d355a2384e0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::two_o_pi</name>
      <anchorfile>group__math__constants_ga6effc6048ec55820a9049f5045625005.html</anchorfile>
      <anchor>ga6effc6048ec55820a9049f5045625005</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::two_o_sqrt_pi</name>
      <anchorfile>group__math__constants_gae38512406479f1c83cc108fa974bd36d.html</anchorfile>
      <anchor>gae38512406479f1c83cc108fa974bd36d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::two_pi</name>
      <anchorfile>group__math__constants_gaeec613ddc8392de0654ab8a1241e0c7a.html</anchorfile>
      <anchor>gaeec613ddc8392de0654ab8a1241e0c7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::two_pio_3</name>
      <anchorfile>group__math__constants_gae00871db0f3b2975fdca381f890123dd.html</anchorfile>
      <anchor>gae00871db0f3b2975fdca381f890123dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::zeta_2</name>
      <anchorfile>group__math__constants_ga257233d84c718b400dae1c6baf71a642.html</anchorfile>
      <anchor>ga257233d84c718b400dae1c6baf71a642</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::zeta_3</name>
      <anchorfile>group__math__constants_ga8d71096cdc12ce0e4c2c139cc244a3bf.html</anchorfile>
      <anchor>ga8d71096cdc12ce0e4c2c139cc244a3bf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>contfrac</name>
    <title>Continued Fractions</title>
    <filename>group__contfrac.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::lentz_a</name>
      <anchorfile>group__contfrac_ga00839b4ed589aba86fcb42545c88eaeb.html</anchorfile>
      <anchor>ga00839b4ed589aba86fcb42545c88eaeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::lentz_b</name>
      <anchorfile>group__contfrac_gac8fda10393aa09246d2bfe8b309cb909.html</anchorfile>
      <anchor>gac8fda10393aa09246d2bfe8b309cb909</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core_conversions</name>
    <title>Conversions</title>
    <filename>group__core__conversions.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::as_value</name>
      <anchorfile>group__core__conversions_gae0215a0e7a791f53d8026ed30cd5c818.html</anchorfile>
      <anchor>gae0215a0e7a791f53d8026ed30cd5c818</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::convert</name>
      <anchorfile>group__core__conversions_gaa346ad56036f22b3571c873b7ae5bebd.html</anchorfile>
      <anchor>gaa346ad56036f22b3571c873b7ae5bebd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::simd_cast</name>
      <anchorfile>group__core__conversions_ga4610128f928ca0244050bfdfdf9710c9.html</anchorfile>
      <anchor>ga4610128f928ca0244050bfdfdf9710c9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core</name>
    <title>Core functions</title>
    <filename>group__core.html</filename>
    <subgroup>core_accuracy</subgroup>
    <subgroup>core_arithmetic</subgroup>
    <subgroup>core_bitops</subgroup>
    <subgroup>core_compress</subgroup>
    <subgroup>core_constants</subgroup>
    <subgroup>core_conversions</subgroup>
    <subgroup>core_decorators</subgroup>
    <subgroup>core_fma_family</subgroup>
    <subgroup>core_internal</subgroup>
    <subgroup>core_logical</subgroup>
    <subgroup>core_named_shuffles</subgroup>
    <subgroup>core_predicates</subgroup>
    <subgroup>core_reduction</subgroup>
    <subgroup>core_simd</subgroup>
    <member kind="variable">
      <type>constexpr callable_deinterleave_groups_</type>
      <name>eve::deinterleave_groups</name>
      <anchorfile>group__core_ga5c2b47962e4523e5ca348a7e3034032b.html</anchorfile>
      <anchor>ga5c2b47962e4523e5ca348a7e3034032b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr callable_rotate_</type>
      <name>eve::rotate</name>
      <anchorfile>group__core_ga2b09f7ec6c1c06462052833c3d08cefb.html</anchorfile>
      <anchor>ga2b09f7ec6c1c06462052833c3d08cefb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr callable_try_each_group_position_</type>
      <name>eve::try_each_group_position</name>
      <anchorfile>group__core_ga721ccc166a96634b64bb08c83ae7e0ed.html</anchorfile>
      <anchor>ga721ccc166a96634b64bb08c83ae7e0ed</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core_fma_internal</name>
    <title>Core_fma_internal</title>
    <filename>group__core__fma__internal.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::epsilon</name>
      <anchorfile>group__core__fma__internal_ga331b89f386f0ee1b5b8fe337383df088.html</anchorfile>
      <anchor>ga331b89f386f0ee1b5b8fe337383df088</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core_decorators</name>
    <title>Decorators</title>
    <filename>group__core__decorators.html</filename>
  </compound>
  <compound kind="group">
    <name>simd</name>
    <title>EVE</title>
    <filename>group__simd.html</filename>
    <subgroup>algorithms</subgroup>
    <subgroup>extensions</subgroup>
    <subgroup>functions</subgroup>
    <subgroup>simd_types</subgroup>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::load</name>
      <anchorfile>group__simd_gac2eed14dbdfb4cf1b36d157e27825cba.html</anchorfile>
      <anchor>gac2eed14dbdfb4cf1b36d157e27825cba</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>elliptic</name>
    <title>Elliptic functions</title>
    <filename>group__elliptic.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::ellint_1</name>
      <anchorfile>group__elliptic_ga5f26f3d8d4aff93caff34f769d0a598a.html</anchorfile>
      <anchor>ga5f26f3d8d4aff93caff34f769d0a598a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::ellint_d</name>
      <anchorfile>group__elliptic_ga865feb1e7d9a99be2bb8d17153606adf.html</anchorfile>
      <anchor>ga865feb1e7d9a99be2bb8d17153606adf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::ellint_fe</name>
      <anchorfile>group__elliptic_ga9f3e72aeb0f119dc9cf880628a4b9557.html</anchorfile>
      <anchor>ga9f3e72aeb0f119dc9cf880628a4b9557</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::ellint_rc</name>
      <anchorfile>group__elliptic_gacca6a0474300efc2cd1907c70b1d6f67.html</anchorfile>
      <anchor>gacca6a0474300efc2cd1907c70b1d6f67</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::ellint_rd</name>
      <anchorfile>group__elliptic_gad55c7d3040b1eb8469a3fa17e79396e1.html</anchorfile>
      <anchor>gad55c7d3040b1eb8469a3fa17e79396e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::ellint_rf</name>
      <anchorfile>group__elliptic_ga72b982adb94e9f25bbe3e4badc1dd0ee.html</anchorfile>
      <anchor>ga72b982adb94e9f25bbe3e4badc1dd0ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::ellint_rg</name>
      <anchorfile>group__elliptic_ga276983e7975e461a199c32ce5eb97a44.html</anchorfile>
      <anchor>ga276983e7975e461a199c32ce5eb97a44</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::ellint_rj</name>
      <anchorfile>group__elliptic_ga65cefaf422775dcd1abbc8929e3f4ed9.html</anchorfile>
      <anchor>ga65cefaf422775dcd1abbc8929e3f4ed9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::heuman_lambda</name>
      <anchorfile>group__elliptic_ga24d1bc66420e69358ebd2eb5ff39bff2.html</anchorfile>
      <anchor>ga24d1bc66420e69358ebd2eb5ff39bff2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::jacobi_elliptic</name>
      <anchorfile>group__elliptic_gaeec8a87b0fc27df584c3ace240a2fda8.html</anchorfile>
      <anchor>gaeec8a87b0fc27df584c3ace240a2fda8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::jacobi_zeta</name>
      <anchorfile>group__elliptic_gaa123505d28500b3ea5216a5b88a5da05.html</anchorfile>
      <anchor>gaa123505d28500b3ea5216a5b88a5da05</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>math_exp</name>
    <title>Exponential</title>
    <filename>group__math__exp.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::cbrt</name>
      <anchorfile>group__math__exp_ga13bb6cc57b6512776b1fc0d72c184fd7.html</anchorfile>
      <anchor>ga13bb6cc57b6512776b1fc0d72c184fd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::exp</name>
      <anchorfile>group__math__exp_ga01387edd49b1ff23f210c7105d65839e.html</anchorfile>
      <anchor>ga01387edd49b1ff23f210c7105d65839e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::exp10</name>
      <anchorfile>group__math__exp_gad36941c942d7f200e996734a9b62a092.html</anchorfile>
      <anchor>gad36941c942d7f200e996734a9b62a092</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::exp2</name>
      <anchorfile>group__math__exp_ga0a3642b91604e578b8d4ef6314d39495.html</anchorfile>
      <anchor>ga0a3642b91604e578b8d4ef6314d39495</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::expm1</name>
      <anchorfile>group__math__exp_gaea2fcee0502a2daf2431462972b30001.html</anchorfile>
      <anchor>gaea2fcee0502a2daf2431462972b30001</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::expmx2</name>
      <anchorfile>group__math__exp_ga7596b6ef2b11f4964c424002ebc75769.html</anchorfile>
      <anchor>ga7596b6ef2b11f4964c424002ebc75769</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::expx2</name>
      <anchorfile>group__math__exp_ga9166af39f3533cb7dd7471a25989f636.html</anchorfile>
      <anchor>ga9166af39f3533cb7dd7471a25989f636</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::geommean</name>
      <anchorfile>group__math__exp_ga7871a1e2f6b0faa5834acd8f8f7bddef.html</anchorfile>
      <anchor>ga7871a1e2f6b0faa5834acd8f8f7bddef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::harmmean</name>
      <anchorfile>group__math__exp_ga2873065e807a313ffd23d3a06e2be637.html</anchorfile>
      <anchor>ga2873065e807a313ffd23d3a06e2be637</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::hypot</name>
      <anchorfile>group__math__exp_gaae6d8d8a0ad9d41260c0bbf8f642a370.html</anchorfile>
      <anchor>gaae6d8d8a0ad9d41260c0bbf8f642a370</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::kolmmean</name>
      <anchorfile>group__math__exp_gafa20e073c378a3eb096b3b3f3ee37741.html</anchorfile>
      <anchor>gafa20e073c378a3eb096b3b3f3ee37741</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::nthroot</name>
      <anchorfile>group__math__exp_ga9cf7e798d0bd35ae16a3588021c871e7.html</anchorfile>
      <anchor>ga9cf7e798d0bd35ae16a3588021c871e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pow</name>
      <anchorfile>group__math__exp_ga67952622d4400abecd8ca1b9986f9648.html</anchorfile>
      <anchor>ga67952622d4400abecd8ca1b9986f9648</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pow1p</name>
      <anchorfile>group__math__exp_ga26151ac8cead2b5ebc679abb9e9c3f9b.html</anchorfile>
      <anchor>ga26151ac8cead2b5ebc679abb9e9c3f9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pow_abs</name>
      <anchorfile>group__math__exp_ga2963a8be3fa9be34ecbb0783084f5456.html</anchorfile>
      <anchor>ga2963a8be3fa9be34ecbb0783084f5456</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::powm1</name>
      <anchorfile>group__math__exp_ga33c7d6d3dd940917f2d926732d21b0d0.html</anchorfile>
      <anchor>ga33c7d6d3dd940917f2d926732d21b0d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::significants</name>
      <anchorfile>group__math__exp_ga800665fde1e25605cbfa89c47dea8f6e.html</anchorfile>
      <anchor>ga800665fde1e25605cbfa89c47dea8f6e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>extensions</name>
    <title>Extensions points</title>
    <filename>group__extensions.html</filename>
    <class kind="struct">eve::callable</class>
    <class kind="struct">eve::constant_callable</class>
    <class kind="struct">eve::elementwise_callable</class>
    <class kind="struct">eve::options</class>
    <class kind="struct">eve::decorated_with</class>
    <class kind="struct">eve::relative_conditional_option</class>
    <class kind="struct">eve::conditional_option</class>
    <member kind="define">
      <type>#define</type>
      <name>EVE_CALLABLE_OBJECT_FROM</name>
      <anchorfile>group__extensions_gafb7ce9baadbb712995f3a9dbef803314.html</anchorfile>
      <anchor>gafb7ce9baadbb712995f3a9dbef803314</anchor>
      <arglist>(NS, TYPE, NAME)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EVE_CALLABLE_OBJECT</name>
      <anchorfile>group__extensions_ga3d0c2dd0a42392476adec67bcd45d3bd.html</anchorfile>
      <anchor>ga3d0c2dd0a42392476adec67bcd45d3bd</anchor>
      <arglist>(TYPE, NAME)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EVE_DISPATCH_CALL</name>
      <anchorfile>group__extensions.html</anchorfile>
      <anchor>gaf0beae174fce698157d30319be9355d0</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EVE_DISPATCH_CALL_NT</name>
      <anchorfile>group__extensions.html</anchorfile>
      <anchor>ga43801cd86f0a52c44b4516722d98aa73</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EVE_CALLABLE_NAMESPACE</name>
      <anchorfile>group__extensions.html</anchorfile>
      <anchor>gad83e12234bfdd5eb87538358c5b1b6b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EVE_REQUIRES</name>
      <anchorfile>group__extensions.html</anchorfile>
      <anchor>gaa3458167ed8a49f4d2bcc308470b0d75</anchor>
      <arglist>(ARCH)</arglist>
    </member>
    <concept>eve::callable_object</concept>
    <member kind="variable">
      <type>constexpr bool</type>
      <name>eve::supports_options</name>
      <anchorfile>group__extensions_gaf4a87d02fe2157d5848083b4ff725dc4.html</anchorfile>
      <anchor>gaf4a87d02fe2157d5848083b4ff725dc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::functor</name>
      <anchorfile>group__extensions.html</anchorfile>
      <anchor>ga406269d77123b31f9bc18b38b78c8e25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr _::condition_key_t</type>
      <name>eve::condition_key</name>
      <anchorfile>group__extensions_ga28f160dc16e57390e8d479cc62d89af6.html</anchorfile>
      <anchor>ga28f160dc16e57390e8d479cc62d89af6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>functions</name>
    <title>Functions</title>
    <filename>group__functions.html</filename>
    <subgroup>bessel</subgroup>
    <subgroup>combinatorial</subgroup>
    <subgroup>core</subgroup>
    <subgroup>elliptic</subgroup>
    <subgroup>math</subgroup>
    <subgroup>polynomial</subgroup>
    <subgroup>special</subgroup>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bessel_i</name>
      <anchorfile>group__functions_ga7452ee5fe3560182c6f4bf00ae2932bb.html</anchorfile>
      <anchor>ga7452ee5fe3560182c6f4bf00ae2932bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bessel_j</name>
      <anchorfile>group__functions_gabb4a644d55742f984dede09b40cc5e4b.html</anchorfile>
      <anchor>gabb4a644d55742f984dede09b40cc5e4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bessel_k</name>
      <anchorfile>group__functions_gacaabaef4d4bb47b01bf39ac76413d44a.html</anchorfile>
      <anchor>gacaabaef4d4bb47b01bf39ac76413d44a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bessel_y</name>
      <anchorfile>group__functions_gae7f2a58376927c82f6a650802d6f6116.html</anchorfile>
      <anchor>gae7f2a58376927c82f6a650802d6f6116</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core_fma_family</name>
    <title>Fused multiply add family</title>
    <filename>group__core__fma__family.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::fam</name>
      <anchorfile>group__core__fma__family_gad4cb975104900d0011e273b1c0cd8015.html</anchorfile>
      <anchor>gad4cb975104900d0011e273b1c0cd8015</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::fanm</name>
      <anchorfile>group__core__fma__family_ga6dae56ba4247691094d46c4451e87012.html</anchorfile>
      <anchor>ga6dae56ba4247691094d46c4451e87012</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::fma</name>
      <anchorfile>group__core__fma__family_gae79b56378eacf4c4f3b3d7e128facb07.html</anchorfile>
      <anchor>gae79b56378eacf4c4f3b3d7e128facb07</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::fms</name>
      <anchorfile>group__core__fma__family_ga92b3e10cb0fda10eec419cb96378a5f5.html</anchorfile>
      <anchor>ga92b3e10cb0fda10eec419cb96378a5f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::fnma</name>
      <anchorfile>group__core__fma__family_ga96c956f8bef9246e2652ca40c3e428d9.html</anchorfile>
      <anchor>ga96c956f8bef9246e2652ca40c3e428d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::fnms</name>
      <anchorfile>group__core__fma__family_gab356e39b49a8aed2b5e5f02a2cc392cc.html</anchorfile>
      <anchor>gab356e39b49a8aed2b5e5f02a2cc392cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::fsm</name>
      <anchorfile>group__core__fma__family_ga6387fe7304980f8112f867f5710af925.html</anchorfile>
      <anchor>ga6387fe7304980f8112f867f5710af925</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::fsnm</name>
      <anchorfile>group__core__fma__family_ga67d686700aac348f3d75484f38c63d4d.html</anchorfile>
      <anchor>ga67d686700aac348f3d75484f38c63d4d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>math_hyper</name>
    <title>Hyperbolic</title>
    <filename>group__math__hyper.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::cosh</name>
      <anchorfile>group__math__hyper_ga984fde6804fbbc4e982bdb5dd7f23dc6.html</anchorfile>
      <anchor>ga984fde6804fbbc4e982bdb5dd7f23dc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::coth</name>
      <anchorfile>group__math__hyper_gab23aa4355242b99aae0bcbd1b9190870.html</anchorfile>
      <anchor>gab23aa4355242b99aae0bcbd1b9190870</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::csch</name>
      <anchorfile>group__math__hyper_ga0c5b7f148a4cce5c8a2ec8ba6bc2bb8e.html</anchorfile>
      <anchor>ga0c5b7f148a4cce5c8a2ec8ba6bc2bb8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::gd</name>
      <anchorfile>group__math__hyper_gac2f0fbac24a6b4ca2f12dcdd07c054bc.html</anchorfile>
      <anchor>gac2f0fbac24a6b4ca2f12dcdd07c054bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sech</name>
      <anchorfile>group__math__hyper_ga268393b3e561e0f65521c56095b4d552.html</anchorfile>
      <anchor>ga268393b3e561e0f65521c56095b4d552</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sinh</name>
      <anchorfile>group__math__hyper_ga66b0e9fefb189e70baa9e4bbbe0d96e2.html</anchorfile>
      <anchor>ga66b0e9fefb189e70baa9e4bbbe0d96e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sinhc</name>
      <anchorfile>group__math__hyper_gac3173586c72be203e69c6748c2ef749b.html</anchorfile>
      <anchor>gac3173586c72be203e69c6748c2ef749b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sinhcosh</name>
      <anchorfile>group__math__hyper_ga780fd5136b6d43175ecd6fde88dc0f70.html</anchorfile>
      <anchor>ga780fd5136b6d43175ecd6fde88dc0f70</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::tanh</name>
      <anchorfile>group__math__hyper_gae9a274c4cd3dd6e99bf32cae9dd642bf.html</anchorfile>
      <anchor>gae9a274c4cd3dd6e99bf32cae9dd642bf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core_internal</name>
    <title>IEEE operations</title>
    <filename>group__core__internal.html</filename>
    <namespace>eve::_</namespace>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::bitofsign</name>
      <anchorfile>group__core__internal_gae174caf55fb3f276410b94f3b7c5dbfb.html</anchorfile>
      <anchor>gae174caf55fb3f276410b94f3b7c5dbfb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::exponent</name>
      <anchorfile>group__core__internal_ga0c0d48cc3ee880fde5b8ec3e874933d0.html</anchorfile>
      <anchor>ga0c0d48cc3ee880fde5b8ec3e874933d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::flush_denormal</name>
      <anchorfile>group__core__internal_ga114b52fbcd864d4005d819c0e1cde554.html</anchorfile>
      <anchor>ga114b52fbcd864d4005d819c0e1cde554</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::ifrexp</name>
      <anchorfile>group__core__internal_ga6b68a3922d5bb6703692878a71fbcba8.html</anchorfile>
      <anchor>ga6b68a3922d5bb6703692878a71fbcba8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::ilogb</name>
      <anchorfile>group__core__internal_ga7f152bb26aee4fe8157db6c9ec25a64c.html</anchorfile>
      <anchor>ga7f152bb26aee4fe8157db6c9ec25a64c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::ldexp</name>
      <anchorfile>group__core__internal_ga9d262f5be47d761c18d548c04cda7c8f.html</anchorfile>
      <anchor>ga9d262f5be47d761c18d548c04cda7c8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::mantissa</name>
      <anchorfile>group__core__internal_ga33c3958f43208dc6ffa54acdd33cf8c0.html</anchorfile>
      <anchor>ga33c3958f43208dc6ffa54acdd33cf8c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::nb_values</name>
      <anchorfile>group__core__internal_ga6a445739414b920ec65978c6bbc5b315.html</anchorfile>
      <anchor>ga6a445739414b920ec65978c6bbc5b315</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::next</name>
      <anchorfile>group__core__internal_gad1c0d7b11ba73f9ea7f39864166d7fb4.html</anchorfile>
      <anchor>gad1c0d7b11ba73f9ea7f39864166d7fb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::nextafter</name>
      <anchorfile>group__core__internal_ga3b419a68a0b99756c3138528b7db9941.html</anchorfile>
      <anchor>ga3b419a68a0b99756c3138528b7db9941</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::nextint</name>
      <anchorfile>group__core__internal_gac2a2df9c3159d70e5e580c008fdeb66c.html</anchorfile>
      <anchor>gac2a2df9c3159d70e5e580c008fdeb66c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::of_class</name>
      <anchorfile>group__core__internal_ga056f305b9a8385ae40ee917d661666f9.html</anchorfile>
      <anchor>ga056f305b9a8385ae40ee917d661666f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::prev</name>
      <anchorfile>group__core__internal_ga5e851835c26e1c3583bf12fe2eea6c23.html</anchorfile>
      <anchor>ga5e851835c26e1c3583bf12fe2eea6c23</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::prevint</name>
      <anchorfile>group__core__internal_ga3ad43aa378eecf62d5b437b320d45d84.html</anchorfile>
      <anchor>ga3ad43aa378eecf62d5b437b320d45d84</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::ulpdist</name>
      <anchorfile>group__core__internal_ga5b73df953d6c6313eeae28925eb8f19c.html</anchorfile>
      <anchor>ga5b73df953d6c6313eeae28925eb8f19c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>math_invhyper</name>
    <title>Inverse hyperbolic</title>
    <filename>group__math__invhyper.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::acosh</name>
      <anchorfile>group__math__invhyper_gab23e955be1ff0b427a22c799202e289e.html</anchorfile>
      <anchor>gab23e955be1ff0b427a22c799202e289e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::acoth</name>
      <anchorfile>group__math__invhyper_gadfee8358d1000c96f6e572c7849baf0c.html</anchorfile>
      <anchor>gadfee8358d1000c96f6e572c7849baf0c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::acsch</name>
      <anchorfile>group__math__invhyper_gacbfc2664a53d2824d2a0d5769f5a19ff.html</anchorfile>
      <anchor>gacbfc2664a53d2824d2a0d5769f5a19ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::agd</name>
      <anchorfile>group__math__invhyper_ga0d95c66d561a5a2a6b18cc920d5069c7.html</anchorfile>
      <anchor>ga0d95c66d561a5a2a6b18cc920d5069c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::asech</name>
      <anchorfile>group__math__invhyper_ga9c8f737823fb88fd8d671a6cb4a5a3e0.html</anchorfile>
      <anchor>ga9c8f737823fb88fd8d671a6cb4a5a3e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::asinh</name>
      <anchorfile>group__math__invhyper_ga070c564edae696a684655a70f2d5aaa5.html</anchorfile>
      <anchor>ga070c564edae696a684655a70f2d5aaa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::atanh</name>
      <anchorfile>group__math__invhyper_ga38b26408c813ee8b8705f2f520c760d6.html</anchorfile>
      <anchor>ga38b26408c813ee8b8705f2f520c760d6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>math_invtrig</name>
    <title>Inverse trigonometric</title>
    <filename>group__math__invtrig.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::acos</name>
      <anchorfile>group__math__invtrig_gad288914ad628b2df2ad07d0d2fbb3462.html</anchorfile>
      <anchor>gad288914ad628b2df2ad07d0d2fbb3462</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::acot</name>
      <anchorfile>group__math__invtrig_ga37a7ef31cd1a2050afbf744a0ea07095.html</anchorfile>
      <anchor>ga37a7ef31cd1a2050afbf744a0ea07095</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::acsc</name>
      <anchorfile>group__math__invtrig_gaa639c90f85170d5b1cd0a717dfc7d785.html</anchorfile>
      <anchor>gaa639c90f85170d5b1cd0a717dfc7d785</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::asec</name>
      <anchorfile>group__math__invtrig_gaa70504a3df7611b4a9148d3c14b80c9e.html</anchorfile>
      <anchor>gaa70504a3df7611b4a9148d3c14b80c9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::asin</name>
      <anchorfile>group__math__invtrig_ga91af84e3494079a4a30a285efdf7c775.html</anchorfile>
      <anchor>ga91af84e3494079a4a30a285efdf7c775</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::atan</name>
      <anchorfile>group__math__invtrig_ga501388937d24a282aa9450162dc51818.html</anchorfile>
      <anchor>ga501388937d24a282aa9450162dc51818</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::atan2</name>
      <anchorfile>group__math__invtrig_ga4e3cc734432c96af2f4e1bfb576ea504.html</anchorfile>
      <anchor>ga4e3cc734432c96af2f4e1bfb576ea504</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>math_log</name>
    <title>Logarithm</title>
    <filename>group__math__log.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::log</name>
      <anchorfile>group__math__log_ga9b4217fd31e1641227ea37686686d31d.html</anchorfile>
      <anchor>ga9b4217fd31e1641227ea37686686d31d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::log10</name>
      <anchorfile>group__math__log_gac249fe99bf31089a24fd212763e94c9e.html</anchorfile>
      <anchor>gac249fe99bf31089a24fd212763e94c9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::log1p</name>
      <anchorfile>group__math__log_ga8adec0a7ab1019888308181fc8c7b5dc.html</anchorfile>
      <anchor>ga8adec0a7ab1019888308181fc8c7b5dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::log2</name>
      <anchorfile>group__math__log_gaa35d093ac60527a5d5ac6fcfc7fbd4d4.html</anchorfile>
      <anchor>gaa35d093ac60527a5d5ac6fcfc7fbd4d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::log_abs</name>
      <anchorfile>group__math__log_ga4dfa083ee26064c6c5256bff56075e5d.html</anchorfile>
      <anchor>ga4dfa083ee26064c6c5256bff56075e5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::logspace_add</name>
      <anchorfile>group__math__log_ga66b8874abdcc6e29c9b4c0c7291ac9db.html</anchorfile>
      <anchor>ga66b8874abdcc6e29c9b4c0c7291ac9db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::logspace_sub</name>
      <anchorfile>group__math__log_gaf5f2a44d3148e9431e1840397b1edd46.html</anchorfile>
      <anchor>gaf5f2a44d3148e9431e1840397b1edd46</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core_logical</name>
    <title>Logical operations</title>
    <filename>group__core__logical.html</filename>
    <member kind="function">
      <type>void</type>
      <name>eve::swap_if</name>
      <anchorfile>group__core__logical_ga2d5530893d21e4e04802f96fd85309df.html</anchorfile>
      <anchor>ga2d5530893d21e4e04802f96fd85309df</anchor>
      <arglist>(Mask const &amp;mask, Value &amp;lhs, Value &amp;rhs) noexcept</arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::if_else</name>
      <anchorfile>group__core__logical_ga4883faa71d1b0e8eaea97fe7cc00b0a8.html</anchorfile>
      <anchor>ga4883faa71d1b0e8eaea97fe7cc00b0a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::logical_and</name>
      <anchorfile>group__core__logical_gac4b0a0de4e227615b5514f739e478a50.html</anchorfile>
      <anchor>gac4b0a0de4e227615b5514f739e478a50</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::logical_andnot</name>
      <anchorfile>group__core__logical_gaa46d435f0a6b06b058e106e37cc1cb29.html</anchorfile>
      <anchor>gaa46d435f0a6b06b058e106e37cc1cb29</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::logical_not</name>
      <anchorfile>group__core__logical_ga5da44a758a10d4d4419fd3df1a4f90e6.html</anchorfile>
      <anchor>ga5da44a758a10d4d4419fd3df1a4f90e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::logical_notand</name>
      <anchorfile>group__core__logical_gadaf632f20d2d6fc4e406459acbf53bb2.html</anchorfile>
      <anchor>gadaf632f20d2d6fc4e406459acbf53bb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::logical_notor</name>
      <anchorfile>group__core__logical_ga0a6fef84dca69e378253433e2b31f647.html</anchorfile>
      <anchor>ga0a6fef84dca69e378253433e2b31f647</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::logical_or</name>
      <anchorfile>group__core__logical_ga4a287385b8f9c1d91c1523bc36ef35a6.html</anchorfile>
      <anchor>ga4a287385b8f9c1d91c1523bc36ef35a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::logical_ornot</name>
      <anchorfile>group__core__logical_gac904b8dce17c980bd3542af1cd6cb875.html</anchorfile>
      <anchor>gac904b8dce17c980bd3542af1cd6cb875</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::logical_xor</name>
      <anchorfile>group__core__logical_ga4681644b17aaa0a3ca3d0f6967d8513e.html</anchorfile>
      <anchor>ga4681644b17aaa0a3ca3d0f6967d8513e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::replace_ignored</name>
      <anchorfile>group__core__logical_ga427432fa10542d6737316973309004e4.html</anchorfile>
      <anchor>ga427432fa10542d6737316973309004e4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>math_sigmoid</name>
    <title>Math_sigmoid</title>
    <filename>group__math__sigmoid.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sigmoid</name>
      <anchorfile>group__math__sigmoid_gac5104eec242c802b49f1376b5b8215df.html</anchorfile>
      <anchor>gac5104eec242c802b49f1376b5b8215df</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>math</name>
    <title>Mathematical functions</title>
    <filename>group__math.html</filename>
    <subgroup>math_constants</subgroup>
    <subgroup>contfrac</subgroup>
    <subgroup>math_exp</subgroup>
    <subgroup>math_hyper</subgroup>
    <subgroup>math_invhyper</subgroup>
    <subgroup>math_invtrig</subgroup>
    <subgroup>math_log</subgroup>
    <subgroup>math_trig</subgroup>
    <member kind="function">
      <type>***constexpr auto</type>
      <name>eve::horner</name>
      <anchorfile>group__math_ga5096faebf5c6aa4322537cf78cfe8e46.html</anchorfile>
      <anchor>ga5096faebf5c6aa4322537cf78cfe8e46</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>***constexpr auto</type>
      <name>eve::tchebsum</name>
      <anchorfile>group__math_ga6e2a171376fb33816873c1b5a0937ceb.html</anchorfile>
      <anchor>ga6e2a171376fb33816873c1b5a0937ceb</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::reverse_horner</name>
      <anchorfile>group__math_gadeb757d766fe37f677ad7b883fc9d7f2.html</anchorfile>
      <anchor>gadeb757d766fe37f677ad7b883fc9d7f2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>memory</name>
    <title>Memory Management</title>
    <filename>group__memory.html</filename>
    <class kind="struct">eve::aligned_allocator</class>
    <class kind="struct">eve::aligned_ptr</class>
    <class kind="struct">eve::stack_buffer</class>
    <class kind="struct">eve::soa_ptr</class>
    <class kind="class">eve::algo::soa_vector</class>
    <concept>eve::has_store_equivalent</concept>
    <member kind="typedef">
      <type>decltype(unalign(std::declval&lt; T &gt;()))</type>
      <name>eve::unaligned_t</name>
      <anchorfile>group__memory_ga54bcb5761211b78d9de3101200a49a9e.html</anchorfile>
      <anchor>ga54bcb5761211b78d9de3101200a49a9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>eve::over</name>
      <anchorfile>group__memory_ga069e9f110c0cb2416812ef8fc5a37555.html</anchorfile>
      <anchor>ga069e9f110c0cb2416812ef8fc5a37555</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>eve::under</name>
      <anchorfile>group__memory_ga664bc5b316e0dd3be42aa4c2fd818047.html</anchorfile>
      <anchor>ga664bc5b316e0dd3be42aa4c2fd818047</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>eve::is_aligned</name>
      <anchorfile>group__memory_gad05ab928f3e9aa972a7e7146f76cce13.html</anchorfile>
      <anchor>gad05ab928f3e9aa972a7e7146f76cce13</anchor>
      <arglist>(aligned_ptr&lt; T, Other &gt; const &amp;ptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>eve::is_aligned</name>
      <anchorfile>group__memory_gab1add731db6f65a080c9ec8b4a125858.html</anchorfile>
      <anchor>gab1add731db6f65a080c9ec8b4a125858</anchor>
      <arglist>(T v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>eve::is_aligned</name>
      <anchorfile>group__memory_ga25228d751afbdd3a2c7d09aea5f2ae74.html</anchorfile>
      <anchor>ga25228d751afbdd3a2c7d09aea5f2ae74</anchor>
      <arglist>(T *ptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>eve::is_aligned</name>
      <anchorfile>group__memory_ga3c06e236e6195d1a36a43e0fcc7c5eca.html</anchorfile>
      <anchor>ga3c06e236e6195d1a36a43e0fcc7c5eca</anchor>
      <arglist>(T *ptr, Lanes lanes) noexcept</arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::read</name>
      <anchorfile>group__memory_ga49de20d14b6d3133b2bc19a95b1af7bd.html</anchorfile>
      <anchor>ga49de20d14b6d3133b2bc19a95b1af7bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::store</name>
      <anchorfile>group__memory_gad748180639cb9a4e2dbf82e48d986615.html</anchorfile>
      <anchor>gad748180639cb9a4e2dbf82e48d986615</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::unalign</name>
      <anchorfile>group__memory_ga62462e7b23d8d092781d5561a9d4c90f.html</anchorfile>
      <anchor>ga62462e7b23d8d092781d5561a9d4c90f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::write</name>
      <anchorfile>group__memory_gad32771ddeb3886065ba659298a50e125.html</anchorfile>
      <anchor>gad32771ddeb3886065ba659298a50e125</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr callable_store_equivalent_</type>
      <name>eve::store_equivalent</name>
      <anchorfile>group__memory_gad0ad3e63b14261774f8ca2c04503159a.html</anchorfile>
      <anchor>gad0ad3e63b14261774f8ca2c04503159a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core_named_shuffles</name>
    <title>Named Shuffles</title>
    <filename>group__core__named__shuffles.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::blend</name>
      <anchorfile>group__core__named__shuffles_ga43d76ccd08cc93ecbf6ebff44ca6321f.html</anchorfile>
      <anchor>ga43d76ccd08cc93ecbf6ebff44ca6321f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::broadcast_lane</name>
      <anchorfile>group__core__named__shuffles_ga9a82942f0d1facc72749788d545576fa.html</anchorfile>
      <anchor>ga9a82942f0d1facc72749788d545576fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::reverse</name>
      <anchorfile>group__core__named__shuffles_ga64933cc646e6b0711efa760eec8a69d9.html</anchorfile>
      <anchor>ga64933cc646e6b0711efa760eec8a69d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::reverse_in_subgroups</name>
      <anchorfile>group__core__named__shuffles_ga67244946cf4cab4f4f2bc19e0c9f9b81.html</anchorfile>
      <anchor>ga67244946cf4cab4f4f2bc19e0c9f9b81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::swap_adjacent</name>
      <anchorfile>group__core__named__shuffles_gadf4386e52fdcc1b41879ce39ee4a518d.html</anchorfile>
      <anchor>gadf4386e52fdcc1b41879ce39ee4a518d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr callable_slide_left_</type>
      <name>eve::slide_left</name>
      <anchorfile>group__core__named__shuffles_ga06f45fd6acf2d0720f511c613fc24ad0.html</anchorfile>
      <anchor>ga06f45fd6acf2d0720f511c613fc24ad0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>polynomial</name>
    <title>Polynomial functions</title>
    <filename>group__polynomial.html</filename>
    <member kind="function">
      <type>***constexpr auto</type>
      <name>eve::newton</name>
      <anchorfile>group__polynomial_ga4293b5bcb8c53576558f6b294fc62a56.html</anchorfile>
      <anchor>ga4293b5bcb8c53576558f6b294fc62a56</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::abel</name>
      <anchorfile>group__polynomial_ga0a8064a3bf2a0b02a5aab69f12ac48c4.html</anchorfile>
      <anchor>ga0a8064a3bf2a0b02a5aab69f12ac48c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::gegenbauer</name>
      <anchorfile>group__polynomial_ga654af420c26859a9b088461f2b49d336.html</anchorfile>
      <anchor>ga654af420c26859a9b088461f2b49d336</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::hermite</name>
      <anchorfile>group__polynomial_ga6cb61eb743e4ac43c44bd0b330f8a8c9.html</anchorfile>
      <anchor>ga6cb61eb743e4ac43c44bd0b330f8a8c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::jacobi</name>
      <anchorfile>group__polynomial_ga0e8517a2ade493151ddd04defc631971.html</anchorfile>
      <anchor>ga0e8517a2ade493151ddd04defc631971</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::laguerre</name>
      <anchorfile>group__polynomial_ga79168b37417f76520ad0cf3e7cdef489.html</anchorfile>
      <anchor>ga79168b37417f76520ad0cf3e7cdef489</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::legendre</name>
      <anchorfile>group__polynomial_ga669b4f63c4de40bd3712f90a301df477.html</anchorfile>
      <anchor>ga669b4f63c4de40bd3712f90a301df477</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::tchebytchev</name>
      <anchorfile>group__polynomial_ga76ed546859e8fc7ab78c7a998d64faa3.html</anchorfile>
      <anchor>ga76ed546859e8fc7ab78c7a998d64faa3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core_predicates</name>
    <title>Predicates</title>
    <filename>group__core__predicates.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::compare_absolute</name>
      <anchorfile>group__core__predicates_ga583d31b3efe53ae6fb8bf505254fe9a6.html</anchorfile>
      <anchor>ga583d31b3efe53ae6fb8bf505254fe9a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_bit_equal</name>
      <anchorfile>group__core__predicates_ga6ec822af7cd03bc7d854a4dad197fda1.html</anchorfile>
      <anchor>ga6ec822af7cd03bc7d854a4dad197fda1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_denormal</name>
      <anchorfile>group__core__predicates_ga514f4eb86f8ab1d6921c9b9ec974c0c4.html</anchorfile>
      <anchor>ga514f4eb86f8ab1d6921c9b9ec974c0c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_eqmz</name>
      <anchorfile>group__core__predicates_ga4c4e922dbc6bdd8e8f9e32eb9d352f76.html</anchorfile>
      <anchor>ga4c4e922dbc6bdd8e8f9e32eb9d352f76</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_eqpz</name>
      <anchorfile>group__core__predicates_ga1f015f87084e3b69efd93498aa2748f1.html</anchorfile>
      <anchor>ga1f015f87084e3b69efd93498aa2748f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_equal</name>
      <anchorfile>group__core__predicates_ga3d2da74d0f6d2327e8dfd4cc109a96b0.html</anchorfile>
      <anchor>ga3d2da74d0f6d2327e8dfd4cc109a96b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_eqz</name>
      <anchorfile>group__core__predicates_gac37d952274c06577a586a75c1f02f33e.html</anchorfile>
      <anchor>gac37d952274c06577a586a75c1f02f33e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_even</name>
      <anchorfile>group__core__predicates_gae52c8a1138e8e9b6da4c0fa568d1d9db.html</anchorfile>
      <anchor>gae52c8a1138e8e9b6da4c0fa568d1d9db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_finite</name>
      <anchorfile>group__core__predicates_ga2caa5fbf925de49ed293175bf493ef9e.html</anchorfile>
      <anchor>ga2caa5fbf925de49ed293175bf493ef9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_flint</name>
      <anchorfile>group__core__predicates_gadd0f931bda75c70a85f70f88c4e4b097.html</anchorfile>
      <anchor>gadd0f931bda75c70a85f70f88c4e4b097</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_gez</name>
      <anchorfile>group__core__predicates_ga580a69727d6d7f6d372eadca43c7f86e.html</anchorfile>
      <anchor>ga580a69727d6d7f6d372eadca43c7f86e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_greater</name>
      <anchorfile>group__core__predicates_ga4506c0d18d8f4bb96a2cc5abaf6a1b5a.html</anchorfile>
      <anchor>ga4506c0d18d8f4bb96a2cc5abaf6a1b5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_greater_equal</name>
      <anchorfile>group__core__predicates_gab91adbe8dd46741068ca460ba873e976.html</anchorfile>
      <anchor>gab91adbe8dd46741068ca460ba873e976</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_gtz</name>
      <anchorfile>group__core__predicates_ga2d321e392856f49b230e9cba211b517d.html</anchorfile>
      <anchor>ga2d321e392856f49b230e9cba211b517d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_infinite</name>
      <anchorfile>group__core__predicates_ga1e2cf3b5bed23375e108126c92ca7ec3.html</anchorfile>
      <anchor>ga1e2cf3b5bed23375e108126c92ca7ec3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_less</name>
      <anchorfile>group__core__predicates_ga7dd417908ae322f8f3ef9a16779ee63f.html</anchorfile>
      <anchor>ga7dd417908ae322f8f3ef9a16779ee63f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_less_equal</name>
      <anchorfile>group__core__predicates_ga9344864ee9268d43aa1e8defdfd292c3.html</anchorfile>
      <anchor>ga9344864ee9268d43aa1e8defdfd292c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_lessgreater</name>
      <anchorfile>group__core__predicates_ga46f7779bc0bc962904db287b4f356f55.html</anchorfile>
      <anchor>ga46f7779bc0bc962904db287b4f356f55</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_lez</name>
      <anchorfile>group__core__predicates_gaceb6deba8172c276ce8444224ef5b7ef.html</anchorfile>
      <anchor>gaceb6deba8172c276ce8444224ef5b7ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_ltz</name>
      <anchorfile>group__core__predicates_ga7671d935e3e1036b64c20aa1e58c9177.html</anchorfile>
      <anchor>ga7671d935e3e1036b64c20aa1e58c9177</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_minf</name>
      <anchorfile>group__core__predicates_ga553ea3bc7c8408ff19b87aec1d03a651.html</anchorfile>
      <anchor>ga553ea3bc7c8408ff19b87aec1d03a651</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_nan</name>
      <anchorfile>group__core__predicates_gaa9f5fcd9c22232d6bef49e308c6df357.html</anchorfile>
      <anchor>gaa9f5fcd9c22232d6bef49e308c6df357</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_negative</name>
      <anchorfile>group__core__predicates_gae28d45c4c5af89e0f3ad48191e63c80e.html</anchorfile>
      <anchor>gae28d45c4c5af89e0f3ad48191e63c80e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_nemz</name>
      <anchorfile>group__core__predicates_ga9b8f733fd01e02e1ff6e47bbc1e17011.html</anchorfile>
      <anchor>ga9b8f733fd01e02e1ff6e47bbc1e17011</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_nepz</name>
      <anchorfile>group__core__predicates_ga978c7ce937b0b6a5e9bd45c19d601928.html</anchorfile>
      <anchor>ga978c7ce937b0b6a5e9bd45c19d601928</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_nez</name>
      <anchorfile>group__core__predicates_gac0b0097d6ffbd2e47b39aae1ac6ca23a.html</anchorfile>
      <anchor>gac0b0097d6ffbd2e47b39aae1ac6ca23a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_ngez</name>
      <anchorfile>group__core__predicates_ga7a8456291e3dc2fe427dbc92a750b706.html</anchorfile>
      <anchor>ga7a8456291e3dc2fe427dbc92a750b706</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_ngtz</name>
      <anchorfile>group__core__predicates_ga972fa009bc9fca501f81d392640e590b.html</anchorfile>
      <anchor>ga972fa009bc9fca501f81d392640e590b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_nlez</name>
      <anchorfile>group__core__predicates_gaf04a54efc3842831e52cbded6ff0dd40.html</anchorfile>
      <anchor>gaf04a54efc3842831e52cbded6ff0dd40</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_nltz</name>
      <anchorfile>group__core__predicates_ga255d9a4c467d32979093166a602b22cb.html</anchorfile>
      <anchor>ga255d9a4c467d32979093166a602b22cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_normal</name>
      <anchorfile>group__core__predicates_ga5e2bc26739efdc174f39bf038e13722e.html</anchorfile>
      <anchor>ga5e2bc26739efdc174f39bf038e13722e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_not_denormal</name>
      <anchorfile>group__core__predicates_ga43711d74c94b96ed6033d864a8941a35.html</anchorfile>
      <anchor>ga43711d74c94b96ed6033d864a8941a35</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_not_equal</name>
      <anchorfile>group__core__predicates_ga005f052be0bb62e30b57c344c3b2fb73.html</anchorfile>
      <anchor>ga005f052be0bb62e30b57c344c3b2fb73</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_not_finite</name>
      <anchorfile>group__core__predicates_ga56235829fa196aeff4b505402e73134a.html</anchorfile>
      <anchor>ga56235829fa196aeff4b505402e73134a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_not_flint</name>
      <anchorfile>group__core__predicates_ga297e673a2c4cfaa8becfa5391cef1653.html</anchorfile>
      <anchor>ga297e673a2c4cfaa8becfa5391cef1653</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_not_greater</name>
      <anchorfile>group__core__predicates_ga65a064e86c209d9dae346b39aa4495da.html</anchorfile>
      <anchor>ga65a064e86c209d9dae346b39aa4495da</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_not_greater_equal</name>
      <anchorfile>group__core__predicates_gad179ebf1cd63eb9b50b27a56a8102977.html</anchorfile>
      <anchor>gad179ebf1cd63eb9b50b27a56a8102977</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_not_infinite</name>
      <anchorfile>group__core__predicates_ga00207423a3f94e5f718e277d3bc1af60.html</anchorfile>
      <anchor>ga00207423a3f94e5f718e277d3bc1af60</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_not_less</name>
      <anchorfile>group__core__predicates_gaccd4f24060de6bb1e4d3f4e3ddb3e2db.html</anchorfile>
      <anchor>gaccd4f24060de6bb1e4d3f4e3ddb3e2db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_not_less_equal</name>
      <anchorfile>group__core__predicates_gad33a8c5bdcad7a64e7cd444382c0a423.html</anchorfile>
      <anchor>gad33a8c5bdcad7a64e7cd444382c0a423</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_not_nan</name>
      <anchorfile>group__core__predicates_ga8a2c95ffd0596f82eed78b2d006eca53.html</anchorfile>
      <anchor>ga8a2c95ffd0596f82eed78b2d006eca53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_odd</name>
      <anchorfile>group__core__predicates_gac4734a17484558619109e9728463636d.html</anchorfile>
      <anchor>gac4734a17484558619109e9728463636d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_ordered</name>
      <anchorfile>group__core__predicates_ga708d743aa5bd73579b85d7cbe23fcb51.html</anchorfile>
      <anchor>ga708d743aa5bd73579b85d7cbe23fcb51</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_pinf</name>
      <anchorfile>group__core__predicates_gaefc265e877011d473280abd9e3874e03.html</anchorfile>
      <anchor>gaefc265e877011d473280abd9e3874e03</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_positive</name>
      <anchorfile>group__core__predicates_ga7f5eb7e1557f2613b3e9691fbdce1c32.html</anchorfile>
      <anchor>ga7f5eb7e1557f2613b3e9691fbdce1c32</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_pow2</name>
      <anchorfile>group__core__predicates_gaa700138e1f2eaf422ccf4e108ad159bb.html</anchorfile>
      <anchor>gaa700138e1f2eaf422ccf4e108ad159bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_unit</name>
      <anchorfile>group__core__predicates_ga55a97aa36ad10be2e0f6f31584df7bb6.html</anchorfile>
      <anchor>ga55a97aa36ad10be2e0f6f31584df7bb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::is_unordered</name>
      <anchorfile>group__core__predicates_gaba27d3ee71282f573b094255e7d24c59.html</anchorfile>
      <anchor>gaba27d3ee71282f573b094255e7d24c59</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>core_reduction</name>
    <title>Reductions</title>
    <filename>group__core__reduction.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::all</name>
      <anchorfile>group__core__reduction_ga5cb8d1d1471423dfa2b00e7da2073169.html</anchorfile>
      <anchor>ga5cb8d1d1471423dfa2b00e7da2073169</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::any</name>
      <anchorfile>group__core__reduction_ga668c3edce7062da8ba1f66504d149f88.html</anchorfile>
      <anchor>ga668c3edce7062da8ba1f66504d149f88</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::count_true</name>
      <anchorfile>group__core__reduction_gaee97bf40ee1dcb8f3cd2477faec994cc.html</anchorfile>
      <anchor>gaee97bf40ee1dcb8f3cd2477faec994cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::first_true</name>
      <anchorfile>group__core__reduction_ga146ea89681f9d926afcc7b3bf968f40d.html</anchorfile>
      <anchor>ga146ea89681f9d926afcc7b3bf968f40d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::last_true</name>
      <anchorfile>group__core__reduction_gabc10fff649535870a897cef2a1e1673e.html</anchorfile>
      <anchor>gabc10fff649535870a897cef2a1e1673e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::maximum</name>
      <anchorfile>group__core__reduction_gaf7f045ef2ed35833e8c3dc0228de48b8.html</anchorfile>
      <anchor>gaf7f045ef2ed35833e8c3dc0228de48b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::minimum</name>
      <anchorfile>group__core__reduction_ga729853eb0b9c9f168dd104b1df7a8ec8.html</anchorfile>
      <anchor>ga729853eb0b9c9f168dd104b1df7a8ec8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::none</name>
      <anchorfile>group__core__reduction_ga6c3f7d70fe96da70a69c2139a7c325ea.html</anchorfile>
      <anchor>ga6c3f7d70fe96da70a69c2139a7c325ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::reduce</name>
      <anchorfile>group__core__reduction_gaa1ec7a1068d9a82ce9b7bb9d1f9d7f37.html</anchorfile>
      <anchor>gaa1ec7a1068d9a82ce9b7bb9d1f9d7f37</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>simd_concepts</name>
    <title>SIMD Concepts</title>
    <filename>group__simd__concepts.html</filename>
    <concept>eve::wide_cardinal</concept>
    <concept>eve::combinable</concept>
    <concept>eve::combinable_to</concept>
    <concept>eve::irregular_predicate</concept>
    <concept>eve::invocable_returning</concept>
    <concept>eve::simd_predicate</concept>
    <concept>eve::abelian_monoid</concept>
    <concept>eve::conditional_expr</concept>
    <concept>eve::relative_conditional_expr</concept>
    <concept>eve::generator</concept>
    <concept>eve::generator_from</concept>
    <concept>eve::plain_scalar_value</concept>
    <concept>eve::logical_scalar_value</concept>
    <concept>eve::product_scalar_value</concept>
    <concept>eve::arithmetic_scalar_value</concept>
    <concept>eve::relaxed_logical_scalar_value</concept>
    <concept>eve::logical_simd_value</concept>
    <concept>eve::substitute_for</concept>
    <concept>eve::value</concept>
    <concept>eve::integral_value</concept>
    <concept>eve::signed_value</concept>
    <concept>eve::unsigned_value</concept>
    <concept>eve::signed_integral_value</concept>
    <concept>eve::floating_value</concept>
    <concept>eve::logical_value</concept>
    <concept>eve::plain_value</concept>
    <concept>eve::arithmetic_value</concept>
    <concept>eve::relaxed_logical_value</concept>
    <concept>eve::integral_scalar_value</concept>
    <concept>eve::signed_scalar_value</concept>
    <concept>eve::unsigned_scalar_value</concept>
    <concept>eve::signed_integral_scalar_value</concept>
    <concept>eve::floating_scalar_value</concept>
    <concept>eve::simd_value</concept>
    <concept>eve::integral_simd_value</concept>
    <concept>eve::signed_simd_value</concept>
    <concept>eve::unsigned_simd_value</concept>
    <concept>eve::signed_integral_simd_value</concept>
    <concept>eve::floating_simd_value</concept>
  </compound>
  <compound kind="group">
    <name>core_simd</name>
    <title>SIMD Specific Operations</title>
    <filename>group__core__simd.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::broadcast</name>
      <anchorfile>group__core__simd_ga0f764f21419f124e1e29c15718520a16.html</anchorfile>
      <anchor>ga0f764f21419f124e1e29c15718520a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::combine</name>
      <anchorfile>group__core__simd_gaa40b2ed752ac083e7336bfcfb216545a.html</anchorfile>
      <anchor>gaa40b2ed752ac083e7336bfcfb216545a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::gather</name>
      <anchorfile>group__core__simd_ga3cbe6596b8e7ca4d4d0611ac642fcf39.html</anchorfile>
      <anchor>ga3cbe6596b8e7ca4d4d0611ac642fcf39</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::has_equal_in</name>
      <anchorfile>group__core__simd_ga517f6b01fca5124ed352087830a713d4.html</anchorfile>
      <anchor>ga517f6b01fca5124ed352087830a713d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::iterate_selected</name>
      <anchorfile>group__core__simd_ga48cbc739f85673ad20ccc29debcb2183.html</anchorfile>
      <anchor>ga48cbc739f85673ad20ccc29debcb2183</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::scan</name>
      <anchorfile>group__core__simd_gaabc7c256adcf53420136da7f6de66fb7.html</anchorfile>
      <anchor>gaabc7c256adcf53420136da7f6de66fb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::scatter</name>
      <anchorfile>group__core__simd_gaa6b4303cb1ae3c602c51414ba1963161.html</anchorfile>
      <anchor>gaa6b4303cb1ae3c602c51414ba1963161</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sort</name>
      <anchorfile>group__core__simd_gafd1cf1dd690536fde5d1a726d437a976.html</anchorfile>
      <anchor>gafd1cf1dd690536fde5d1a726d437a976</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::zip</name>
      <anchorfile>group__core__simd_ga35f397f99a9981ec14e2d162ce530ee9.html</anchorfile>
      <anchor>ga35f397f99a9981ec14e2d162ce530ee9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr callable_broadcast_group_</type>
      <name>eve::broadcast_group</name>
      <anchorfile>group__core__simd_ga843fbb36980a16f585f8e727da3a8f96.html</anchorfile>
      <anchor>ga843fbb36980a16f585f8e727da3a8f96</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr callable_deinterleave_groups_shuffle_</type>
      <name>eve::deinterleave_groups_shuffle</name>
      <anchorfile>group__core__simd_ga275315d7cc9b3cd8f5e063136d4990d1.html</anchorfile>
      <anchor>ga275315d7cc9b3cd8f5e063136d4990d1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>simd_types</name>
    <title>SIMD related types</title>
    <filename>group__simd__types.html</filename>
    <namespace>eve::_</namespace>
    <class kind="struct">eve::fixed</class>
    <class kind="struct">eve::logical&lt; T &gt;</class>
    <class kind="struct">eve::logical&lt; wide&lt; Type, Cardinal &gt; &gt;</class>
    <class kind="struct">eve::wide</class>
    <class kind="struct">eve::top_bits</class>
    <class kind="struct">eve::pattern_t</class>
    <member kind="function">
      <type>auto</type>
      <name>eve::operator==</name>
      <anchorfile>group__simd__types.html</anchorfile>
      <anchor>ga8a5020911faf4ccefcfb1d2a8b718719</anchor>
      <arglist>(logical&lt; wide&lt; T, Cardinal &gt; &gt; a, logical&lt; wide&lt; U, Cardinal &gt; &gt; b) noexcept -&gt; decltype(is_equal(a, b))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>eve::operator!=</name>
      <anchorfile>group__simd__types.html</anchorfile>
      <anchor>gaa3dfaa4cfdde3a9e71e878d8fe9dce3a</anchor>
      <arglist>(logical&lt; wide&lt; T, Cardinal &gt; &gt; a, logical&lt; wide&lt; U, Cardinal &gt; &gt; b) noexcept -&gt; decltype(is_not_equal(a, b))</arglist>
    </member>
    <member kind="variable">
      <type>constexpr std::ptrdiff_t</type>
      <name>eve::na_</name>
      <anchorfile>group__simd__types.html</anchorfile>
      <anchor>ga11b65eff854b205c9f9ef8dbd559bb9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr std::ptrdiff_t</type>
      <name>eve::we_</name>
      <anchorfile>group__simd__types.html</anchorfile>
      <anchor>gab6c3c30138d82ef45b1bbcf9e65145d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::pattern</name>
      <anchorfile>group__simd__types.html</anchorfile>
      <anchor>ga61c6484edbe5ceb7f92946bc798802dd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>special</name>
    <title>Special functions</title>
    <filename>group__special.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::beta</name>
      <anchorfile>group__special_ga82b53a249d6073de3db11e4aa3792333.html</anchorfile>
      <anchor>ga82b53a249d6073de3db11e4aa3792333</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::betainc</name>
      <anchorfile>group__special_ga6265a2055297023ecb43dd7b686d071b.html</anchorfile>
      <anchor>ga6265a2055297023ecb43dd7b686d071b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::betainc_inv</name>
      <anchorfile>group__special_gad608f2f150843348a76ac10aac42e81d.html</anchorfile>
      <anchor>gad608f2f150843348a76ac10aac42e81d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::cos_int</name>
      <anchorfile>group__special_ga0305432c8d066d530744c297856afc7c.html</anchorfile>
      <anchor>ga0305432c8d066d530744c297856afc7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::dawson</name>
      <anchorfile>group__special_ga984ab215f62e9bed040c35776a18eeac.html</anchorfile>
      <anchor>ga984ab215f62e9bed040c35776a18eeac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::digamma</name>
      <anchorfile>group__special_ga35bd17562d2457033901ba4a6a112808.html</anchorfile>
      <anchor>ga35bd17562d2457033901ba4a6a112808</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::erf</name>
      <anchorfile>group__special_ga1dbce0b509333c811af2c620f07aacc4.html</anchorfile>
      <anchor>ga1dbce0b509333c811af2c620f07aacc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::erf_inv</name>
      <anchorfile>group__special_ga1f15df67386cc4841f9b5b20e6acce50.html</anchorfile>
      <anchor>ga1f15df67386cc4841f9b5b20e6acce50</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::erfc</name>
      <anchorfile>group__special_ga026fdedcb9cf7041cdf7d670d7a095bc.html</anchorfile>
      <anchor>ga026fdedcb9cf7041cdf7d670d7a095bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::erfc_inv</name>
      <anchorfile>group__special_gae47d192b5a13d6a35516de4ae2da273d.html</anchorfile>
      <anchor>gae47d192b5a13d6a35516de4ae2da273d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::erfcx</name>
      <anchorfile>group__special_ga39a32ff65020290d5c0d8975c648a901.html</anchorfile>
      <anchor>ga39a32ff65020290d5c0d8975c648a901</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::exp_int</name>
      <anchorfile>group__special_gac952b61c8134c6d1a20071760ce2749d.html</anchorfile>
      <anchor>gac952b61c8134c6d1a20071760ce2749d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::factorial</name>
      <anchorfile>group__special_gaa985cb92e44034e0b56d51aa7b12a72f.html</anchorfile>
      <anchor>gaa985cb92e44034e0b56d51aa7b12a72f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::gamma_p</name>
      <anchorfile>group__special_gaca2a6730649297012022897eb2b4b549.html</anchorfile>
      <anchor>gaca2a6730649297012022897eb2b4b549</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::gamma_p_inv</name>
      <anchorfile>group__special_ga84e6f5cc6ba688751341a9a2a314363e.html</anchorfile>
      <anchor>ga84e6f5cc6ba688751341a9a2a314363e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::hurwitz</name>
      <anchorfile>group__special_gadf7af0b7e2002701bbdbb8419d6757eb.html</anchorfile>
      <anchor>gadf7af0b7e2002701bbdbb8419d6757eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::lambert</name>
      <anchorfile>group__special_ga87ab5feda409075628e3c53c8022ffac.html</anchorfile>
      <anchor>ga87ab5feda409075628e3c53c8022ffac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::lbeta</name>
      <anchorfile>group__special_ga340e8bdb903cecc2bf070e6a5c53975c.html</anchorfile>
      <anchor>ga340e8bdb903cecc2bf070e6a5c53975c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::lfactorial</name>
      <anchorfile>group__special_gaf0da94be6b92a70b4b5887a1db7cc256.html</anchorfile>
      <anchor>gaf0da94be6b92a70b4b5887a1db7cc256</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::log_abs_gamma</name>
      <anchorfile>group__special_ga53390ef1f01ae9ea76542610a2ef6310.html</anchorfile>
      <anchor>ga53390ef1f01ae9ea76542610a2ef6310</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::log_gamma</name>
      <anchorfile>group__special_gaab4644340afcf841c6b06e2ab3a8d7fd.html</anchorfile>
      <anchor>gaab4644340afcf841c6b06e2ab3a8d7fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::lrising_factorial</name>
      <anchorfile>group__special_gab1b9a2a36db6d1dcaa97a3619eef8e9b.html</anchorfile>
      <anchor>gab1b9a2a36db6d1dcaa97a3619eef8e9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::omega</name>
      <anchorfile>group__special_gab2da346734b5d477afbbc1c91018a940.html</anchorfile>
      <anchor>gab2da346734b5d477afbbc1c91018a940</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::polygamma</name>
      <anchorfile>group__special_ga1e9de30f261edeef4271c47b7683c980.html</anchorfile>
      <anchor>ga1e9de30f261edeef4271c47b7683c980</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rising_factorial</name>
      <anchorfile>group__special_ga3c336080e4c6ee720c464ce4ebe60b75.html</anchorfile>
      <anchor>ga3c336080e4c6ee720c464ce4ebe60b75</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::signgam</name>
      <anchorfile>group__special_ga318d06481af50d48d3f50859fc1cdb18.html</anchorfile>
      <anchor>ga318d06481af50d48d3f50859fc1cdb18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sin_int</name>
      <anchorfile>group__special_ga4851b95d7c353647ea62c8a213827aa3.html</anchorfile>
      <anchor>ga4851b95d7c353647ea62c8a213827aa3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::stirling</name>
      <anchorfile>group__special_gaa331e8a7776d0afb3d6d127152a420d5.html</anchorfile>
      <anchor>gaa331e8a7776d0afb3d6d127152a420d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::tgamma</name>
      <anchorfile>group__special_gaf1cae73e680ecb4fd31f6eb45520d4c5.html</anchorfile>
      <anchor>gaf1cae73e680ecb4fd31f6eb45520d4c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::trigamma</name>
      <anchorfile>group__special_ga07111caf2d86c76136eae323799ef5a9.html</anchorfile>
      <anchor>ga07111caf2d86c76136eae323799ef5a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::zeta</name>
      <anchorfile>group__special_ga0eb86f96b60c52b8ffbe2c64354bbc7f.html</anchorfile>
      <anchor>ga0eb86f96b60c52b8ffbe2c64354bbc7f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>struct</name>
    <title>Structured Types Management</title>
    <filename>group__struct.html</filename>
    <namespace>eve::_</namespace>
    <class kind="struct">eve::supports_ordering</class>
    <class kind="struct">eve::supports_like</class>
    <class kind="struct">eve::struct_support</class>
    <concept>eve::like</concept>
  </compound>
  <compound kind="group">
    <name>math_trig</name>
    <title>Trigonometric</title>
    <filename>group__math__trig.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::arg</name>
      <anchorfile>group__math__trig_ga8d23db8b1e967b99e1425ac6dac47a25.html</anchorfile>
      <anchor>ga8d23db8b1e967b99e1425ac6dac47a25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::cos</name>
      <anchorfile>group__math__trig_ga36c6472a18a6a22d2af48cd1070c6ab2.html</anchorfile>
      <anchor>ga36c6472a18a6a22d2af48cd1070c6ab2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::cot</name>
      <anchorfile>group__math__trig_ga1f3bad93037c3bed17cfbe954ab0dc79.html</anchorfile>
      <anchor>ga1f3bad93037c3bed17cfbe954ab0dc79</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::csc</name>
      <anchorfile>group__math__trig_ga58de56369367394561f438e248bb51d7.html</anchorfile>
      <anchor>ga58de56369367394561f438e248bb51d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::deginrad</name>
      <anchorfile>group__math__trig_gae9819f646fb28b1a2ff178eecd383eda.html</anchorfile>
      <anchor>gae9819f646fb28b1a2ff178eecd383eda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::div_180</name>
      <anchorfile>group__math__trig_gae38f095b02721ec8d4e23bf613a3ddba.html</anchorfile>
      <anchor>gae38f095b02721ec8d4e23bf613a3ddba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::quadrant</name>
      <anchorfile>group__math__trig_gabddb668a3d3a31c888377fc66cb67640.html</anchorfile>
      <anchor>gabddb668a3d3a31c888377fc66cb67640</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::radindeg</name>
      <anchorfile>group__math__trig_gafe1c9782e1c8077e3108775150c5286f.html</anchorfile>
      <anchor>gafe1c9782e1c8077e3108775150c5286f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::radinpi</name>
      <anchorfile>group__math__trig_gad88bed1c31cbbaede5f4f03ff13bbb71.html</anchorfile>
      <anchor>gad88bed1c31cbbaede5f4f03ff13bbb71</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::rempio2</name>
      <anchorfile>group__math__trig_gaf499e87cc47529c27dd16d88ed57cd08.html</anchorfile>
      <anchor>gaf499e87cc47529c27dd16d88ed57cd08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sec</name>
      <anchorfile>group__math__trig_ga5fa51e730488c41abb8402a3d1635877.html</anchorfile>
      <anchor>ga5fa51e730488c41abb8402a3d1635877</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sin</name>
      <anchorfile>group__math__trig_ga1ed5ec0a84a4ad7ae88b11033a63d04b.html</anchorfile>
      <anchor>ga1ed5ec0a84a4ad7ae88b11033a63d04b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::sincos</name>
      <anchorfile>group__math__trig_gae52069dae490294ee836af9c366bbbac.html</anchorfile>
      <anchor>gae52069dae490294ee836af9c366bbbac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eve::tan</name>
      <anchorfile>group__math__trig_ga4e45e50d570ac3a6e925f7fd39f40c42.html</anchorfile>
      <anchor>ga4e45e50d570ac3a6e925f7fd39f40c42</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>traits</name>
    <title>Type traits</title>
    <filename>group__traits.html</filename>
    <class kind="struct">eve::abi</class>
    <class kind="struct">eve::as</class>
    <class kind="struct">eve::as_element</class>
    <class kind="struct">eve::cardinal</class>
    <class kind="struct">eve::common_compatible</class>
    <class kind="struct">eve::common_type</class>
    <class kind="struct">eve::comparisons</class>
    <class kind="struct">eve::element_type</class>
    <class kind="struct">eve::underlying_type</class>
    <member kind="typedef">
      <type>decltype(_::iterator_cardinal_impl&lt; T &gt;())</type>
      <name>eve::iterator_cardinal_t</name>
      <anchorfile>group__traits_ga331d84fa4b64e5deb329b1a09d60c747.html</anchorfile>
      <anchor>ga331d84fa4b64e5deb329b1a09d60c747</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename decltype(_::value_type_impl&lt; T &gt;())::type</type>
      <name>eve::value_type_t</name>
      <anchorfile>group__traits_gaae6fbba5b56b9fab940a05b444c15e6f.html</anchorfile>
      <anchor>gaae6fbba5b56b9fab940a05b444c15e6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>as_wide_t&lt; value_type_t&lt; T &gt;, iterator_cardinal_t&lt; T &gt; &gt;</type>
      <name>eve::wide_value_type_t</name>
      <anchorfile>group__traits_ga55234286d380ec9a9baef96a65649356.html</anchorfile>
      <anchor>ga55234286d380ec9a9baef96a65649356</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr std::size_t</type>
      <name>eve::max_scalar_size_v</name>
      <anchorfile>group__traits_ga6e8aacb30e0e7798a5cf8e30f9ace681.html</anchorfile>
      <anchor>ga6e8aacb30e0e7798a5cf8e30f9ace681</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>views</name>
    <title>Views</title>
    <filename>group__views.html</filename>
    <class kind="struct">eve::algo::views::backward_iterator</class>
    <class kind="struct">eve::algo::views::backward_range</class>
    <class kind="struct">eve::algo::views::converting_iterator</class>
    <class kind="struct">eve::algo::views::converting_range</class>
    <class kind="struct">eve::algo::views::iota_with_step_iterator</class>
    <class kind="struct">eve::algo::views::map_iterator</class>
    <class kind="struct">eve::algo::views::map_range</class>
    <class kind="struct">eve::algo::views::reverse_iterator</class>
    <class kind="struct">eve::algo::views::reverse_range</class>
    <class kind="struct">eve::algo::views::zip_range</class>
    <class kind="struct">eve::algo::views::zip_iterator</class>
    <class kind="struct">backward_iterator</class>
    <class kind="struct">backward_range</class>
    <class kind="struct">converting_iterator</class>
    <class kind="struct">converting_range</class>
    <class kind="struct">iota_with_step_iterator</class>
    <class kind="struct">reverse_iterator</class>
    <class kind="struct">reverse_range</class>
    <class kind="struct">zip_iterator</class>
    <class kind="struct">zip_range</class>
    <member kind="variable">
      <type>struct eve::algo::views::backward_</type>
      <name>eve::algo::views::backward</name>
      <anchorfile>group__views_ga2db9579a29e8320cea16f25c549af1dc.html</anchorfile>
      <anchor>ga2db9579a29e8320cea16f25c549af1dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct eve::algo::views::convert_</type>
      <name>eve::algo::views::convert</name>
      <anchorfile>group__views_ga1d67fe0e91df8539083585c6e096789a.html</anchorfile>
      <anchor>ga1d67fe0e91df8539083585c6e096789a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct eve::algo::views::@322272220212015245067346236112242054366143140171</type>
      <name>eve::algo::views::iota_with_step</name>
      <anchorfile>group__views_gac2613080675f010cddeaed9159910c8e.html</anchorfile>
      <anchor>gac2613080675f010cddeaed9159910c8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct eve::algo::views::@210325115252346307006063377161320362040266047301</type>
      <name>eve::algo::views::iota</name>
      <anchorfile>group__views_gaa4c24e44fd616a31d3bd46ad947a6187.html</anchorfile>
      <anchor>gaa4c24e44fd616a31d3bd46ad947a6187</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct eve::algo::views::@323343333121305126230027065263077141140132352020</type>
      <name>eve::algo::views::map_convert</name>
      <anchorfile>group__views_ga8fc21d6f2794c2b2581b8692e19fa530.html</anchorfile>
      <anchor>ga8fc21d6f2794c2b2581b8692e19fa530</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct eve::algo::views::@237367333220374116042140171311261045047321245302</type>
      <name>eve::algo::views::map</name>
      <anchorfile>group__views_gac1d09efe17a29359a933614ec4a63d1e.html</anchorfile>
      <anchor>gac1d09efe17a29359a933614ec4a63d1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct eve::algo::views::reverse_</type>
      <name>eve::algo::views::reverse</name>
      <anchorfile>group__views_ga99cbdbcd28d1967761946207eaaffa25.html</anchorfile>
      <anchor>ga99cbdbcd28d1967761946207eaaffa25</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>changelog</name>
    <title>Change Log</title>
    <filename>changelog.html</filename>
    <docanchor file="changelog.html" title="/__w/eve/eve/doc/changelog.md">md__2____w_2eve_2eve_2doc_2changelog</docanchor>
  </compound>
  <compound kind="page">
    <name>algo_rationale</name>
    <title>SIMD Algorithms</title>
    <filename>algo_rationale.html</filename>
    <docanchor file="algo_rationale.html" title="/__w/eve/eve/doc/internals/algo.md">md__2____w_2eve_2eve_2doc_2internals_2algo</docanchor>
  </compound>
  <compound kind="page">
    <name>design_rationale</name>
    <title>Design Decisions</title>
    <filename>design_rationale.html</filename>
    <docanchor file="design_rationale.html" title="/__w/eve/eve/doc/internals/design.md">md__2____w_2eve_2eve_2doc_2internals_2design</docanchor>
    <docanchor file="design_rationale.html" title="SIMD registers as Type x Cardinal">rationale-simd</docanchor>
    <docanchor file="design_rationale.html" title="Callable Function Objects as main API">rationale-callable</docanchor>
    <docanchor file="design_rationale.html" title="Function customization via higher-order decorator">rationale-decorator</docanchor>
    <docanchor file="design_rationale.html" title="Masked operations support">rationale-mask</docanchor>
  </compound>
  <compound kind="page">
    <name>dev_cmake</name>
    <title>Building for Testing</title>
    <filename>dev_cmake.html</filename>
    <docanchor file="dev_cmake.html" title="/__w/eve/eve/doc/internals/dev_cmake.md">md__2____w_2eve_2eve_2doc_2internals_2dev__cmake</docanchor>
  </compound>
  <compound kind="page">
    <name>dev_environment</name>
    <title>Development Environment</title>
    <filename>dev_environment.html</filename>
    <docanchor file="dev_environment.html" title="/__w/eve/eve/doc/internals/dev_environment.md">md__2____w_2eve_2eve_2doc_2internals_2dev__environment</docanchor>
    <docanchor file="dev_environment.html" title="Docker setup">dev_docker_setup</docanchor>
    <docanchor file="dev_environment.html" title="Running EVE docker">dev_docker_helper</docanchor>
    <docanchor file="dev_environment.html" title="Trying EVE without building it">dev_docker_eve</docanchor>
  </compound>
  <compound kind="page">
    <name>glossary_semantic</name>
    <title>Components Semantic</title>
    <filename>glossary_semantic.html</filename>
    <docanchor file="glossary_semantic.html" title="/__w/eve/eve/doc/internals/semantic.md">md__2____w_2eve_2eve_2doc_2internals_2semantic</docanchor>
    <docanchor file="glossary_semantic.html" title="Element-wise Operations">glossary_elementwise</docanchor>
    <docanchor file="glossary_semantic.html" title="Reductions">glossary_reduction</docanchor>
    <docanchor file="glossary_semantic.html" title="Arithmetic Functions">glossary_arithmetic</docanchor>
    <docanchor file="glossary_semantic.html" title="Bitwise Functions">glossary_bitwise</docanchor>
    <docanchor file="glossary_semantic.html" title="Logical Functions">glossary_logical</docanchor>
    <docanchor file="glossary_semantic.html" title="Constant Functions">glossary_constant</docanchor>
  </compound>
  <compound kind="page">
    <name>licence</name>
    <title>Licence</title>
    <filename>licence.html</filename>
    <docanchor file="licence.html" title="/__w/eve/eve/doc/licence.md">md__2____w_2eve_2eve_2doc_2licence</docanchor>
  </compound>
  <compound kind="page">
    <name>setup</name>
    <title>Installation &amp; Quick Start</title>
    <filename>setup.html</filename>
    <docanchor file="setup.html" title="/__w/eve/eve/doc/setup.md">md__2____w_2eve_2eve_2doc_2setup</docanchor>
  </compound>
  <compound kind="page">
    <name>conditional</name>
    <title>Conditional operations</title>
    <filename>conditional.html</filename>
  </compound>
  <compound kind="page">
    <name>freqscale</name>
    <title>Frequency Scaling.</title>
    <filename>freqscale.html</filename>
  </compound>
  <compound kind="page">
    <name>inter-with-native</name>
    <title>Interaction with native code.</title>
    <filename>inter-with-native.html</filename>
  </compound>
  <compound kind="page">
    <name>intro-01</name>
    <title>Basic Operations</title>
    <filename>intro-01.html</filename>
  </compound>
  <compound kind="page">
    <name>intro-02</name>
    <title>Algorithms</title>
    <filename>intro-02.html</filename>
  </compound>
  <compound kind="page">
    <name>intro-03</name>
    <title>Tuples</title>
    <filename>intro-03.html</filename>
  </compound>
  <compound kind="page">
    <name>intro-04</name>
    <title>Data Structures</title>
    <filename>intro-04.html</filename>
  </compound>
  <compound kind="page">
    <name>intro-05</name>
    <title>Solving quadratic equations</title>
    <filename>intro-05.html</filename>
  </compound>
  <compound kind="page">
    <name>multiarch</name>
    <title>Handling Multiple Architecture Targets</title>
    <filename>multiarch.html</filename>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>The Expressive Vector Engine</title>
    <filename>index.html</filename>
    <docanchor file="index.html" title="The Expressive Vector Engine">md__2____w_2eve_2eve_2doc_2index</docanchor>
  </compound>
</tagfile>
