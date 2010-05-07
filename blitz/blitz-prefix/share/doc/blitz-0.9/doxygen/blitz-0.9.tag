<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>array-impl.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>array-impl_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <includes id="memblock_8h" name="memblock.h" local="no" imported="no">blitz/memblock.h</includes>
    <includes id="range_8h" name="range.h" local="no" imported="no">blitz/range.h</includes>
    <includes id="tinyvec_8h" name="tinyvec.h" local="no" imported="no">blitz/tinyvec.h</includes>
    <includes id="indexexpr_8h" name="indexexpr.h" local="no" imported="no">blitz/indexexpr.h</includes>
    <includes id="prettyprint_8h" name="prettyprint.h" local="no" imported="no">blitz/prettyprint.h</includes>
    <class kind="class">Array</class>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>e6fb9f5c58463056415cf46528a93234</anchor>
      <arglist>(Array&lt; P_numtype, N_rank &gt; &amp;, Array&lt; P_numtype, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>find</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>3b27bed4ba706e91c322cf00ea6d8641</anchor>
      <arglist>(Array&lt; TinyVector&lt; int, N_rank &gt;, 1 &gt; &amp;, const Array&lt; P_numtype, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>65333efa13414268473596afc1e30607</anchor>
      <arglist>(ostream &amp;, const Array&lt; T_numtype, 1 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>46b0406082da92521fc4ca739c722c95</anchor>
      <arglist>(ostream &amp;, const Array&lt; T_numtype, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>istream &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>35d32bb0623074ffe9e0bdfc553a13a5</anchor>
      <arglist>(istream &amp;is, Array&lt; T_numtype, N_rank &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>find</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>6fd2c50536a1b5dd28c2ad7149fa6b0b</anchor>
      <arglist>(Array&lt; TinyVector&lt; int, P_expr::rank &gt;, 1 &gt; &amp;indices, const _bz_ArrayExpr&lt; P_expr &gt; &amp;expr)</arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>firstRank</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>10fa77141b2ccb1987020012c8968060</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>secondRank</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>80b19521ce0cdc6058a6e74f4ec23fe1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>thirdRank</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>6234d233c51516b8ac4efd55bceebab0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>fourthRank</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>444c9890bbff4c24a863f016eb5807cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>fifthRank</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>4cda495bd162d9be12babd19baa9a556</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>sixthRank</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>946e32a6eb593958f7c32a28a153ce40</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>seventhRank</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>3fca1df55adbfa8251489da219ce6e14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>eighthRank</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>4fb3e6a5e3db7aeeed58909a47787c59</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>ninthRank</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>591b69aa0470434d784665524a551be8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>tenthRank</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>8606511c19df3f5f3c01d5ba22c9226a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>eleventhRank</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>5065eea386c808e4500600470240708a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>firstDim</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>0e33e8837ee6b8867d978fe9c3efe885</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>secondDim</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>518ffae5f2f550d35ec0e2fe7b9856ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>thirdDim</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>014c5cae0a66ed35b79c8d1e5e8aa309</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>fourthDim</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>88ddcd456cba203025b1ebce201b2ae5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>fifthDim</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>afec8739c9efb7ba33a9d73d754ca901</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>sixthDim</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>09e286be77fa9fa73a5849629e5d33b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>seventhDim</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>e82f35cbc334ff8aa239b73df4a56814</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>eighthDim</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>71fc90c01b3db3416638e71925c3038a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>ninthDim</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>1d015c7d42fc317a351bac33a1c9aee2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>tenthDim</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>33946040ebca5971e44f2abaa2bdc27f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>eleventhDim</name>
      <anchorfile>array-impl_8h.html</anchorfile>
      <anchor>0bac07dc8580219fe495290cb12a0e94</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>array.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>array_8h</filename>
    <includes id="array-impl_8h" name="array-impl.h" local="no" imported="no">blitz/array-impl.h</includes>
  </compound>
  <compound kind="file">
    <name>blitz.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>blitz_8h</filename>
    <includes id="compiler_8h" name="compiler.h" local="no" imported="no">blitz/compiler.h</includes>
    <includes id="tuning_8h" name="tuning.h" local="no" imported="no">blitz/tuning.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>BZ_THROW</name>
      <anchorfile>blitz_8h.html</anchorfile>
      <anchor>e1d6c9e19be8639a6f026ec5bca50226</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_bz_global</name>
      <anchorfile>blitz_8h.html</anchorfile>
      <anchor>8b3d2e1b6b9e77b6b6e0689694dfc40b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_GLOBAL_INIT</name>
      <anchorfile>blitz_8h.html</anchorfile>
      <anchor>60ba6df9a593bc8dc9dd46c2be4dbb87</anchor>
      <arglist>(X)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_MUTEX_DECLARE</name>
      <anchorfile>blitz_8h.html</anchorfile>
      <anchor>f5dd9b0fd31b05737ce1f96487047ac3</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_MUTEX_INIT</name>
      <anchorfile>blitz_8h.html</anchorfile>
      <anchor>d00babbd4548e4409898a9495a9698f1</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_MUTEX_LOCK</name>
      <anchorfile>blitz_8h.html</anchorfile>
      <anchor>ca7f42e6944911662ecd87f408157172</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_MUTEX_UNLOCK</name>
      <anchorfile>blitz_8h.html</anchorfile>
      <anchor>8eb7e680570483c4dacda9338aabf1be</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_MUTEX_DESTROY</name>
      <anchorfile>blitz_8h.html</anchorfile>
      <anchor>27b54aa7bb9e7bd7c6ea1cad76eab7fc</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>indexType</name>
      <anchorfile>blitz_8h.html</anchorfile>
      <anchor>15b6d72b5de39b768482af271e79da41</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>size_t</type>
      <name>sizeType</name>
      <anchorfile>blitz_8h.html</anchorfile>
      <anchor>60e2a69c63bd2cbc53071302b450bdd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ptrdiff_t</type>
      <name>diffType</name>
      <anchorfile>blitz_8h.html</anchorfile>
      <anchor>3ce371c85fd39b38e43e66ad449d61b0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bzconfig.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>bzconfig_8h</filename>
  </compound>
  <compound kind="file">
    <name>bzconfig.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/gnu/</path>
    <filename>gnu_2bzconfig_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>_BLITZ_GNU_BZCONFIG_H</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>e406cd8ac000f94003025edcf37cc152</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_BOOL</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>1aacaddc56b60571f9840850e20ba2b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_CLIMITS</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>ba9efce8338d102801613947e6214083</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_COMPLEX</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>7af5b8f6c6f1c3bece074e31e65ac91b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_COMPLEX_FCNS</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>2cc2032429f56027838578c9ef72a06c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_COMPLEX_MATH1</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>d841ef59417358946239b75c6775ba0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_COMPLEX_MATH_IN_NAMESPACE_STD</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>80073b30b58ac002c397de745e218d84</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_CONST_CAST</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>d8161672c865f2036cef46f85c8c49c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_CSTRING</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>a8fbe21d9aff3e6e57f6dc55d1937a85</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_DEFAULT_TEMPLATE_PARAMETERS</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>ebe7d8cbc622e4d515fa3c8c0b2c6fbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_DLFCN_H</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>9473e9508f0197639808b202c15be1c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_DYNAMIC_CAST</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>5796034b05f310892e082339f12f72f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_ENUM_COMPUTATIONS</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>f6c1570ea711ca022147bc796e3ea373</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_ENUM_COMPUTATIONS_WITH_CAST</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>f5a991dec3e98c97177671d601b12063</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_EXCEPTIONS</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>9b6a404844582953547f97015463a2fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_EXPLICIT</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>f6c36c127c9400c25a6184840263bfcb</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_EXPLICIT_TEMPLATE_FUNCTION_QUALIFICATION</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>3895ff54829ea275f2c896da934ebea0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_FULL_SPECIALIZATION_SYNTAX</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>074f81ba493ad481362bc30eb6af71bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_FUNCTION_NONTYPE_PARAMETERS</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>dcf44075db482cc6dc9608a5e5ed1f33</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_IEEE_MATH</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>a55eaa193567fd6981afc38e262cdcb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_INTTYPES_H</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>6e7d25d7113f865bbeaf545728a058cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_MEMBER_CONSTANTS</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>9213201f47c7f949547571192ade4f99</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_MEMBER_TEMPLATES</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>2cf64d53c5a39f6c81630d32bcc91a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_MEMBER_TEMPLATES_OUTSIDE_CLASS</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>39fc6a50a2c1d9729324b97ecba56d88</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_MEMORY_H</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>39da683079910876642155b7439b73bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_MUTABLE</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>838baaec43d54cb9a5b4b865d1fa2458</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_NAMESPACES</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>f7fae949b473acf7d54effac2a55413f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_NCEG_RESTRICT_EGCS</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>3735b51a43ba07812d3fd303f4243dc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_NUMERIC_LIMITS</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>acf9597d9d3c288edeac765705d684b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_PARTIAL_ORDERING</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>00dde097a4bbfe3129574611d23680e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_PARTIAL_SPECIALIZATION</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>ba3d8935689dfbcc4a2c0649b11bad70</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_REINTERPRET_CAST</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>a98fd0b97551e15c0615b670ebc70d43</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_RTTI</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>2a44a29698f81a024e009dfe4d5e5ae5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_RUSAGE</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>ec12bc5328113139f678dbcae7527d98</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_STATIC_CAST</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>d01b20a15f9114152cec3a6eee2becc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_STD</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>9b702d4e1fe80c053ba6c1eb7bcecdc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_STDINT_H</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>98bd6e5303fa34bbc1999dc4bd0e670f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_STDLIB_H</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>443876d8f3fdfd14ff70ba3a12c9c78d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_STL</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>bb232d94bebe2ceeac2e77c8dc2bd718</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_STRINGS_H</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>083667cff81ecf53457a3f3722b44f2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_STRING_H</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>ee2c1d380ea99a9476889165305ce7b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_SYS_STAT_H</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>a6b322b9ec071c7e857085b128f9e6d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_SYS_TYPES_H</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>14d8fc2e80d26db5465b99ffe929c9c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_TEMPLATES</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>a2e516cb9a88eafe07a06f3b4a88d72b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_TEMPLATES_AS_TEMPLATE_ARGUMENTS</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>c71e4b44b0d51a56085f1e38ce3b3810</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_TEMPLATE_KEYWORD_QUALIFIER</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>7f175d79f1bf0e9c0859b9a3093e6308</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_TEMPLATE_QUALIFIED_BASE_CLASS</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>68a6f4744cf71b3b765aa32d87de9814</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_TEMPLATE_QUALIFIED_RETURN_TYPE</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>e80c9bba376017ac412159a85a5b82f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_TEMPLATE_SCOPED_ARGUMENT_MATCHING</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>1166240bc9d81d976e78792423f9fa95</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_TYPENAME</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>1f8a3c3815a902ba25c14efe3d5735a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_TYPE_PROMOTION</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>2a14049d87c1b15c6f7002b1d9bfefc8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_UNISTD_H</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>03c72ec02d4f7f4991e5872764884b3b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_USE_NUMTRAIT</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>9b65d568eb81f986fd8c77b7a6e45632</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_HAVE_VALARRAY</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>b2f3bafa985fa8341b972572ec302f9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_ISNAN_IN_NAMESPACE_STD</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>7d83f412a8169b8b89bec97d7e2e5d33</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_LT_OBJDIR</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>7461ea0ac328610c0a6de30ac0864529</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_MATH_ABSINT_IN_NAMESPACE_STD</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>44fab7011e6780a347c9240c96479bdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_MATH_FN_IN_NAMESPACE_STD</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>440004309d8d3532baf96c53b8e36283</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_PACKAGE</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>2227d8a265780fa61618b35c061e9789</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_PACKAGE_BUGREPORT</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>fece2c39106fc586beb3d48aaf222fdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_PACKAGE_NAME</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>9063697955f52ef31c2848cb2268ca79</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_PACKAGE_STRING</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>9ca184ee796e1ba2b07802193137453c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_PACKAGE_TARNAME</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>fb42072ec24696a44140ae483e2713e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_PACKAGE_VERSION</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>0e7f18b9a850fbb2864daa9e326d0b4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_STDC_HEADERS</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>69060f18c817603cc42d1bca436626c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_VERSION</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>74566e71cda38928f249b6d32429042a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ__compiler_name</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>18a3c4bc42339a9712b3827dec6f40f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ__compiler_options</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>92f3373867a106f4e8c55cc4008fab78</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ__config_date</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>fb4c91f4f617bc866d9d438e25dff97c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ__os_name</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>aa798e0632430c9e6f04b0cd39692538</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ__platform</name>
      <anchorfile>gnu_2bzconfig_8h.html</anchorfile>
      <anchor>42b11f0b852491ce062f587e97d7a43b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>compiler.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>compiler_8h</filename>
    <includes id="bzconfig_8h" name="bzconfig.h" local="no" imported="no">blitz/bzconfig.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>BZ_NAMESPACE</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>e33e5c1c3d6992d17224c49fd80df9ef</anchor>
      <arglist>(X)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_NAMESPACE_END</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>3a5f9cf1b4e49ac69a95f142bd2d0c43</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_USING_NAMESPACE</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>f6152ee545d8d50d9ff263a9319004ab</anchor>
      <arglist>(X)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_TEMPLATE_DEFAULT</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>a44e5094bd662895dc5d25b1d870a7f8</anchor>
      <arglist>(X)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>explicit</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>a3d8ce7e244e1597fab629118fbf9e5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_bz_typename</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>1bc40add3e72effc9cf69dbe445cbdfd</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>mutable</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>ee7b7b89e01250b8e73ed0eb3ebe1e10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>restrict</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>080abdcb9c02438f1cd2bb707af25af8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>bool</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>bb452686968e48b67397da5f97445f5b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>true</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>41f9c5fb8b08eb5dc3edce4dcb37fee7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>false</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>65e9886d74aaee76545e83dd09011727</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_MATHFN_SCOPE</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>12f8b3c0d5e7961501a40a1897b0551a</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_MATHABSINT_SCOPE</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>d72579a3acec4ab75cf06a921cbe181b</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_CMATHFN_SCOPE</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>66cc980b2c69248085eef1ec4b66ec1e</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_IEEEMATHFN_SCOPE</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>a7ef006f4e7d6945c7d63472e691bd02</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_BLITZ_SCOPE</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>c2335d5f319cb7e8f510bb6a444ef5fb</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_STD_SCOPE</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>532d4d8bc0b5328fed97495c3921c463</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_LIKELY</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>7d5e71afb3a61dee7bb9ccc1495cdcbe</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_UNLIKELY</name>
      <anchorfile>compiler_8h.html</anchorfile>
      <anchor>c886c7b3cdacf4ef81b175fb6bf5bba9</anchor>
      <arglist>(x)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>config.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>config_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_BOOL</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>e561d533c7d87c4f1e9a7714e5490c39</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_CLIMITS</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>e5407437a28c0931efcd74f4f300972c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_COMPLEX</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>3bd951e5f1fd77c6be6a6a0443df7196</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_COMPLEX_FCNS</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>a50dd8a5054cb4bb0921974fb4f2c367</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_COMPLEX_MATH1</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>3fc91b3c326a9b2ec3307b5caeeaa5bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_COMPLEX_MATH_IN_NAMESPACE_STD</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>fca7eb3f32b59f8a9e4d0a9db69c4736</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_CONST_CAST</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>c8272a04c8884265ada4b0300f0596ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_CSTRING</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>2a3bf31daa768a230d4fb36ce26316c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_DEFAULT_TEMPLATE_PARAMETERS</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>d60ae0ebd007f7012e04222170152b60</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_DLFCN_H</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>0ee1617ff2f6885ef384a3dd46f9b9d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_DYNAMIC_CAST</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>5ca4f7129421ca551dfa2ab48002fab4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_ENUM_COMPUTATIONS</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>547069940825181fb37db339d42c2440</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_ENUM_COMPUTATIONS_WITH_CAST</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>cb63fa9be779516f7a041a7fb4e950ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_EXCEPTIONS</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>d5d48fb0f30c59cd93c66356aa8158e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_EXPLICIT</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>a45d7aa7ecd0e3428a51a024aba59fea</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_EXPLICIT_TEMPLATE_FUNCTION_QUALIFICATION</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>7e4e44b7bef23b4171a34202292b595f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_FULL_SPECIALIZATION_SYNTAX</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>0f6ff74567e3843f40335e30db2d2839</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_FUNCTION_NONTYPE_PARAMETERS</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>5a423951e42638fe19dd8ae180824658</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_IEEE_MATH</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>a3b8e06bd57f65da61acdbd1b8d980c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_INTTYPES_H</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>b90a030ff2790ebdc176660a6dd2a478</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_MEMBER_CONSTANTS</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>ce8f778f8ed22181d54211e9ecba4473</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_MEMBER_TEMPLATES</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>969fff35b6374580244a2d48a8d58022</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_MEMBER_TEMPLATES_OUTSIDE_CLASS</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>50a91f5140a26a4e26ba65dd2eff1818</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_MEMORY_H</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>e93a78f9d076138897af441c9f86f285</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_MUTABLE</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>154e42e1b3b0a0f92fb91f0ae17274f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_NAMESPACES</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>52abc142ac9ffc42c8010c43c513c2c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_NCEG_RESTRICT_EGCS</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>0b9864c0b30a0177fc8a1449cee82929</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_NUMERIC_LIMITS</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>07bf128bdab075c35c31e6e41f0e2cfc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_PARTIAL_ORDERING</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>ecebe0340b35f37e5365c7fc6f437400</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_PARTIAL_SPECIALIZATION</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>9728ec8b35c91a87b52ae6039f7522df</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_REINTERPRET_CAST</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>744de235b47c0671c48fe2cdf73e3617</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_RTTI</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>6ae31d896aee649413cd4bf5d14b77ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_RUSAGE</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>406bd2d2830afd9f03a5d22c3396fe45</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_STATIC_CAST</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>4bce230d20ba245cb0ab8d37d401f067</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_STD</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>b04deb9bf9b0a6c4efb83ebae5ccd551</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_STDINT_H</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>b6cd6d1c63c1e26ea2d4537b77148354</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_STDLIB_H</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>9e0e434ec1a6ddbd97db12b5a32905e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_STL</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>eb7cf69a6123c8b2160d3032daaa4442</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_STRINGS_H</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>405d10d46190bcb0320524c54eafc850</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_STRING_H</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>d4c234dd1625255dc626a15886306e7d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_SYS_STAT_H</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>ce156430ba007d19b4348a950d0c692b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_SYS_TYPES_H</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>69dc70bea5d1f8bd2be9740e974fa666</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_TEMPLATES</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>0bb07637b0b11bf36f64f0d4bdeb5b18</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_TEMPLATES_AS_TEMPLATE_ARGUMENTS</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>830bab14f96eb822dbc5fc6730c36ea1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_TEMPLATE_KEYWORD_QUALIFIER</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>30f38c23e4d7020f212dfe9b06a4554d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_TEMPLATE_QUALIFIED_BASE_CLASS</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>aa0ab6b15f1f2dd99245198b92a94e14</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_TEMPLATE_QUALIFIED_RETURN_TYPE</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>080583ed5998223ede0e24080950e1c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_TEMPLATE_SCOPED_ARGUMENT_MATCHING</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>ed8b621bb0c9a8aad89a393ec5610b0c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_TYPENAME</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>161f181f9b227a439bf82dfe4599e0bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_TYPE_PROMOTION</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>6771169182ee5d75d5bbf0a3d7870ac0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_UNISTD_H</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>219b06937831d0da94d801ab13987639</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_USE_NUMTRAIT</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>89aae0110f6e239bb9d65e7caa5033d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HAVE_VALARRAY</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>1a8ebcee64c49731809cfb1858d41fb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISNAN_IN_NAMESPACE_STD</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>08e9d0f217d1a4aa3580cb5e3a226fbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LT_OBJDIR</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>c2d5925d76379847dd9fc4747b061659</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MATH_ABSINT_IN_NAMESPACE_STD</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>e7007b35b8e059ba6d05c7f9d814becb</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MATH_FN_IN_NAMESPACE_STD</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>1e777f47cfaf6103fa38c5f2aaaa4bc8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PACKAGE</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>ca8570fb706c81df371b7f9bc454ae03</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PACKAGE_BUGREPORT</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>1d1d2d7f8d2f95b376954d649ab03233</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PACKAGE_NAME</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>1c0439e4355794c09b64274849eb0279</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PACKAGE_STRING</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>c73e6f903c16eca7710f92e36e1c6fbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PACKAGE_TARNAME</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>f415af6bfede0e8d5453708afe68651c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PACKAGE_VERSION</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>a326a05d5e30f9e9a4bb0b4469d5d0c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>STDC_HEADERS</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>550e5c272cc3cf3814651721167dcd23</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VERSION</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>1c6d5de492ac61ad29aec7aa9a436bbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_compiler_name</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>e771ca79675e51c57ae498919aea5258</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_compiler_options</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>4d7585385e520d66c1c78c1e57afe491</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_config_date</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>794a1b3d702bf38b3c7b206b718dc4b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_os_name</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>c650e072604f480b535d7ff4a50be889</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_platform</name>
      <anchorfile>config_8h.html</anchorfile>
      <anchor>c1dedfc8524291a072e20082464a5c36</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>etbase.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>etbase_8h</filename>
    <class kind="class">ETBase</class>
  </compound>
  <compound kind="file">
    <name>extremum.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>extremum_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <class kind="class">Extremum</class>
  </compound>
  <compound kind="file">
    <name>indexexpr.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>indexexpr_8h</filename>
    <includes id="tinyvec_8h" name="tinyvec.h" local="no" imported="no">blitz/tinyvec.h</includes>
    <includes id="prettyprint_8h" name="prettyprint.h" local="no" imported="no">blitz/prettyprint.h</includes>
    <includes id="etbase_8h" name="etbase.h" local="no" imported="no">blitz/etbase.h</includes>
    <class kind="class">IndexPlaceholder</class>
    <class kind="class">IndexPlaceholder::SliceInfo</class>
    <member kind="typedef">
      <type>IndexPlaceholder&lt; 0 &gt;</type>
      <name>firstIndex</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>f779cec5695ec4647a01d4c74138ba72</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IndexPlaceholder&lt; 1 &gt;</type>
      <name>secondIndex</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>b3273886a8e7e6f2f0b381021ec2c1da</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IndexPlaceholder&lt; 2 &gt;</type>
      <name>thirdIndex</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>325c9074b7cc4554f71957e05bdfa55e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IndexPlaceholder&lt; 3 &gt;</type>
      <name>fourthIndex</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>035f0a297d093a1e251f5e9daebb26be</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IndexPlaceholder&lt; 4 &gt;</type>
      <name>fifthIndex</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>9c6a82dd0c204d7ee251f2cfc1499882</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IndexPlaceholder&lt; 5 &gt;</type>
      <name>sixthIndex</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>cb5a5816ac402972d38f5e91d5b00e71</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IndexPlaceholder&lt; 6 &gt;</type>
      <name>seventhIndex</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>a1c4604e286d2c4fbc59773229c73a1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IndexPlaceholder&lt; 7 &gt;</type>
      <name>eighthIndex</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>bf7cb0668f90a7b4954bed8ad6a085c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IndexPlaceholder&lt; 8 &gt;</type>
      <name>ninthIndex</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>403e6aa66e31cd6a141c19a2cd68d402</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IndexPlaceholder&lt; 9 &gt;</type>
      <name>tenthIndex</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>991b018bf0d6c2e1daed5a84d3ac8820</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IndexPlaceholder&lt; 10 &gt;</type>
      <name>eleventhIndex</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>2d615c40225fc3da83b5862cc01841bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>_bz_global blitz::IndexPlaceholder&lt; 0 &gt;</type>
      <name>i</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>abd77643995707c185e95c8cb2782c81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>_bz_global blitz::IndexPlaceholder&lt; 1 &gt;</type>
      <name>j</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>a1f3325d66516548e69238097857fa98</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>_bz_global blitz::IndexPlaceholder&lt; 2 &gt;</type>
      <name>k</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>bb72938a198351550846b37a84588b63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>_bz_global blitz::IndexPlaceholder&lt; 3 &gt;</type>
      <name>l</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>88aacdaa46b76729743ee33ef8b95a58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>_bz_global blitz::IndexPlaceholder&lt; 4 &gt;</type>
      <name>m</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>b72fdb4031d47b75ab26dd18a437bcdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>_bz_global blitz::IndexPlaceholder&lt; 5 &gt;</type>
      <name>n</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>b427e2e2b4d6cec55fa088ea2a692ace</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>_bz_global blitz::IndexPlaceholder&lt; 6 &gt;</type>
      <name>o</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>e4770fe31e4de70bda45529bf7f7eab0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>_bz_global blitz::IndexPlaceholder&lt; 7 &gt;</type>
      <name>p</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>2b8c103eb5bfc196fbc3d29923e28ac1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>_bz_global blitz::IndexPlaceholder&lt; 8 &gt;</type>
      <name>q</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>c886c3584e464b5533390d7440c9dd98</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>_bz_global blitz::IndexPlaceholder&lt; 9 &gt;</type>
      <name>r</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>c434fd11cc2493608d8d91424d60c17e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>_bz_global blitz::IndexPlaceholder&lt; 10 &gt;</type>
      <name>s</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>e024b0db549122b44c349ae28ec990dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>_bz_global blitz::IndexPlaceholder&lt; 11 &gt;</type>
      <name>t</name>
      <anchorfile>indexexpr_8h.html</anchorfile>
      <anchor>01709998b82be3f34e0412206618d09d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>listinit.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>listinit_8h</filename>
    <class kind="class">ListInitializer</class>
    <class kind="class">ListInitializationSwitch</class>
  </compound>
  <compound kind="file">
    <name>matdiag.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>matdiag_8h</filename>
    <class kind="class">DiagonalIterator</class>
    <class kind="class">Diagonal</class>
  </compound>
  <compound kind="file">
    <name>matgen.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>matgen_8h</filename>
    <class kind="class">GeneralMatrix</class>
    <class kind="class">GeneralIterator</class>
    <class kind="class">RowMajorIterator</class>
    <class kind="class">RowMajor</class>
    <class kind="class">ColumnMajorIterator</class>
    <class kind="class">ColumnMajor</class>
  </compound>
  <compound kind="file">
    <name>matltri.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>matltri_8h</filename>
    <class kind="class">LowerTriangularIterator</class>
    <class kind="class">LowerTriangular</class>
  </compound>
  <compound kind="file">
    <name>matrix.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>matrix_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <includes id="memblock_8h" name="memblock.h" local="no" imported="no">blitz/memblock.h</includes>
    <includes id="mstruct_8h" name="mstruct.h" local="no" imported="no">blitz/mstruct.h</includes>
    <class kind="class">Matrix</class>
    <member kind="function">
      <type>ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>matrix_8h.html</anchorfile>
      <anchor>3c35a23cfa49cbe8f17d29f148060119</anchor>
      <arglist>(ostream &amp;os, const Matrix&lt; P_numtype, P_structure &gt; &amp;matrix)</arglist>
    </member>
    <member kind="function">
      <type>istream &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>matrix_8h.html</anchorfile>
      <anchor>26c0ae430a788a95f90fc1d4cc339a92</anchor>
      <arglist>(istream &amp;is, Matrix&lt; P_numtype, P_structure &gt; &amp;matrix)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>matsymm.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>matsymm_8h</filename>
    <class kind="class">SymmetricIterator</class>
    <class kind="class">Symmetric</class>
  </compound>
  <compound kind="file">
    <name>mattoep.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>mattoep_8h</filename>
    <class kind="class">ToeplitzIterator</class>
    <class kind="class">Toeplitz</class>
  </compound>
  <compound kind="file">
    <name>matutri.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>matutri_8h</filename>
    <class kind="class">UpperTriangularIterator</class>
    <class kind="class">UpperTriangular</class>
  </compound>
  <compound kind="file">
    <name>memblock.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>memblock_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <class kind="class">MemoryBlock</class>
    <class kind="class">MemoryBlockReference</class>
    <member kind="enumeration">
      <name>preexistingMemoryPolicy</name>
      <anchorfile>memblock_8h.html</anchorfile>
      <anchor>e9323b8f2afbf31c869a1610053247db</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>duplicateData</name>
      <anchorfile>memblock_8h.html</anchorfile>
      <anchor>e9323b8f2afbf31c869a1610053247db5972eefe046fc8e5108da90580911256</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>deleteDataWhenDone</name>
      <anchorfile>memblock_8h.html</anchorfile>
      <anchor>e9323b8f2afbf31c869a1610053247dbc48eb789c04e58438925c438c85039a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>neverDeleteData</name>
      <anchorfile>memblock_8h.html</anchorfile>
      <anchor>e9323b8f2afbf31c869a1610053247db27b676f7e018fbf0868e085a3b91c9f5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>minmax.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>minmax_8h</filename>
    <member kind="function">
      <type></type>
      <name>BZ_PROMOTE</name>
      <anchorfile>minmax_8h.html</anchorfile>
      <anchor>443065e92639c8f43abd1ffa6e47f4f6</anchor>
      <arglist>(T1, T2)(min)(const T1 &amp;a</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>mstruct.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>mstruct_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <includes id="zero_8h" name="zero.h" local="no" imported="no">blitz/zero.h</includes>
    <includes id="matgen_8h" name="matgen.h" local="no" imported="no">blitz/matgen.h</includes>
    <includes id="matsymm_8h" name="matsymm.h" local="no" imported="no">blitz/matsymm.h</includes>
    <includes id="matdiag_8h" name="matdiag.h" local="no" imported="no">blitz/matdiag.h</includes>
    <includes id="mattoep_8h" name="mattoep.h" local="no" imported="no">blitz/mattoep.h</includes>
    <includes id="matltri_8h" name="matltri.h" local="no" imported="no">blitz/matltri.h</includes>
    <includes id="matutri_8h" name="matutri.h" local="no" imported="no">blitz/matutri.h</includes>
    <class kind="class">MatrixStructure</class>
    <class kind="class">AsymmetricMatrix</class>
  </compound>
  <compound kind="file">
    <name>numtrait.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>numtrait_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>BZ_SUMTYPE</name>
      <anchorfile>numtrait_8h.html</anchorfile>
      <anchor>c9261751d112f72c6698a3c2667dfe4a</anchor>
      <arglist>(X)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_DIFFTYPE</name>
      <anchorfile>numtrait_8h.html</anchorfile>
      <anchor>717162c7768a1204cc8f48d9a526e334</anchor>
      <arglist>(X)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_FLOATTYPE</name>
      <anchorfile>numtrait_8h.html</anchorfile>
      <anchor>5103d741ae777d1de61a77151fe09e36</anchor>
      <arglist>(X)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_SIGNEDTYPE</name>
      <anchorfile>numtrait_8h.html</anchorfile>
      <anchor>782e361bf2ab1598f25c240ba6c28125</anchor>
      <arglist>(X)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ops.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>ops_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <includes id="prettyprint_8h" name="prettyprint.h" local="no" imported="no">blitz/prettyprint.h</includes>
    <class kind="struct">BitwiseNot</class>
    <class kind="struct">UnaryPlus</class>
    <class kind="struct">UnaryMinus</class>
    <class kind="struct">LogicalNot</class>
    <class kind="struct">Add</class>
    <class kind="struct">Subtract</class>
    <class kind="struct">Multiply</class>
    <class kind="struct">Divide</class>
    <class kind="struct">Modulo</class>
    <class kind="struct">BitwiseXor</class>
    <class kind="struct">BitwiseAnd</class>
    <class kind="struct">BitwiseOr</class>
    <class kind="struct">ShiftRight</class>
    <class kind="struct">ShiftLeft</class>
    <class kind="struct">Greater</class>
    <class kind="struct">Less</class>
    <class kind="struct">GreaterOrEqual</class>
    <class kind="struct">LessOrEqual</class>
    <class kind="struct">Equal</class>
    <class kind="struct">NotEqual</class>
    <class kind="struct">LogicalAnd</class>
    <class kind="struct">LogicalOr</class>
    <member kind="define">
      <type>#define</type>
      <name>BZ_DEFINE_UNARY_OP</name>
      <anchorfile>ops_8h.html</anchorfile>
      <anchor>1c068a58b52163e1ab8e9c68d40753f2</anchor>
      <arglist>(name, op)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_DEFINE_UNARY_OP_RET</name>
      <anchorfile>ops_8h.html</anchorfile>
      <anchor>5eabd37a47ae9b401f489204dd247fa4</anchor>
      <arglist>(name, op, ret)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_DEFINE_BINARY_OP</name>
      <anchorfile>ops_8h.html</anchorfile>
      <anchor>cffd9d354c53c7f9c9d6c5b58fcec75a</anchor>
      <arglist>(name, op)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_DEFINE_BINARY_OP_RET</name>
      <anchorfile>ops_8h.html</anchorfile>
      <anchor>d23bf6adf1ab809d98276fb8fadebd51</anchor>
      <arglist>(name, op, ret)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>prettyprint.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>prettyprint_8h</filename>
    <class kind="class">prettyPrintFormat</class>
  </compound>
  <compound kind="file">
    <name>rand-dunif.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>rand-dunif_8h</filename>
    <includes id="random_8h" name="random.h" local="no" imported="no">blitz/random.h</includes>
    <includes id="rand-uniform_8h" name="rand-uniform.h" local="no" imported="no">blitz/rand-uniform.h</includes>
    <class kind="class">DiscreteUniform</class>
  </compound>
  <compound kind="file">
    <name>rand-mt.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>rand-mt_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <class kind="class">MersenneTwister</class>
    <class kind="struct">MersenneTwister::BitMixer</class>
    <class kind="class">MersenneTwisterDouble</class>
  </compound>
  <compound kind="file">
    <name>rand-normal.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>rand-normal_8h</filename>
    <includes id="random_8h" name="random.h" local="no" imported="no">blitz/random.h</includes>
    <includes id="rand-uniform_8h" name="rand-uniform.h" local="no" imported="no">blitz/rand-uniform.h</includes>
    <class kind="class">Normal</class>
    <member kind="define">
      <type>#define</type>
      <name>M_PI</name>
      <anchorfile>rand-normal_8h.html</anchorfile>
      <anchor>e71449b1cc6e6250b91f539153a7a0d3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>rand-tt800.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>rand-tt800_8h</filename>
    <includes id="random_8h" name="random.h" local="no" imported="no">blitz/random.h</includes>
    <class kind="class">TT800</class>
  </compound>
  <compound kind="file">
    <name>rand-uniform.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>rand-uniform_8h</filename>
    <includes id="random_8h" name="random.h" local="no" imported="no">blitz/random.h</includes>
    <class kind="class">Uniform</class>
  </compound>
  <compound kind="file">
    <name>random.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>random_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <class kind="class">Random</class>
  </compound>
  <compound kind="file">
    <name>range.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>range_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <class kind="class">Range</class>
    <member kind="variable">
      <type>const int</type>
      <name>fromStart</name>
      <anchorfile>range_8h.html</anchorfile>
      <anchor>85395ca25f333b35f2a6eed9aaf60d9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>toEnd</name>
      <anchorfile>range_8h.html</anchorfile>
      <anchor>5f0ea38522aa21e66aba47d17a6cf2d6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>reduce.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>reduce_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <includes id="numtrait_8h" name="numtrait.h" local="no" imported="no">blitz/numtrait.h</includes>
    <class kind="class">ReduceSum</class>
    <class kind="class">ReduceMean</class>
    <class kind="class">ReduceMin</class>
    <class kind="class">ReduceMax</class>
    <class kind="struct">MinMaxValue</class>
    <class kind="class">ReduceMinMax</class>
    <class kind="class">ReduceMinIndex</class>
    <class kind="class">ReduceMinIndexVector</class>
    <class kind="class">ReduceMaxIndex</class>
    <class kind="class">ReduceMaxIndexVector</class>
    <class kind="class">ReduceFirst</class>
    <class kind="class">ReduceLast</class>
    <class kind="class">ReduceProduct</class>
    <class kind="class">ReduceCount</class>
    <class kind="class">ReduceAny</class>
    <class kind="class">ReduceAll</class>
  </compound>
  <compound kind="file">
    <name>shapecheck.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>shapecheck_8h</filename>
    <member kind="function">
      <type>bool</type>
      <name>areShapesConformable</name>
      <anchorfile>shapecheck_8h.html</anchorfile>
      <anchor>94e40fddcc9906fd9596d37e39429a14</anchor>
      <arglist>(const T_shape1 &amp;, const T_shape2 &amp;)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>areShapesConformable</name>
      <anchorfile>shapecheck_8h.html</anchorfile>
      <anchor>c6fff3b3a190f4fcc25f8c84a9fcc39c</anchor>
      <arglist>(const T_shape &amp;a, const T_shape &amp;b)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tinyvec-et.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>tinyvec-et_8h</filename>
    <includes id="tinyvec_8h" name="tinyvec.h" local="no" imported="no">blitz/tinyvec.h</includes>
    <includes id="vector-et_8h" name="vector-et.h" local="no" imported="no">blitz/vector-et.h</includes>
  </compound>
  <compound kind="file">
    <name>tinyvec.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>tinyvec_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <includes id="range_8h" name="range.h" local="no" imported="no">blitz/range.h</includes>
    <includes id="listinit_8h" name="listinit.h" local="no" imported="no">blitz/listinit.h</includes>
    <includes id="tinyveciter_8h" name="tinyveciter.h" local="no" imported="no">blitz/tinyveciter.h</includes>
    <includes id="tvecglobs_8h" name="tvecglobs.h" local="no" imported="no">blitz/tvecglobs.h</includes>
    <includes id="vector_8h" name="vector.h" local="no" imported="no">blitz/vector.h</includes>
    <class kind="class">TinyVector</class>
    <class kind="class">TinyVector&lt; T, 0 &gt;</class>
  </compound>
  <compound kind="file">
    <name>tinyveciter.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>tinyveciter_8h</filename>
    <includes id="tinyvec_8h" name="tinyvec.h" local="no" imported="no">blitz/tinyvec.h</includes>
    <class kind="class">TinyVectorIter</class>
    <class kind="class">TinyVectorIterConst</class>
  </compound>
  <compound kind="file">
    <name>traversal.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>traversal_8h</filename>
  </compound>
  <compound kind="file">
    <name>tuning.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>tuning_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>BZ_L1_CACHE_ESTIMATED_SIZE</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>4a93f94463bf886f155b0629ec2b4e27</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_L2_CACHE_ESTIMATED_SIZE</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>b8c2c1bd723e471d8c4677e302c9b18a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_PASS_EXPR_BY_VALUE</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>64847e826e82e05e67e31474aee154ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_MANUAL_VECEXPR_COPY_CONSTRUCTOR</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>c67bd59f72fd06d2e135daa752330833</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_INLINE_GROUP1</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>e378112b51e8f07fa82746d9dbe38dd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_INLINE_GROUP2</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>c3c269c45c92cef0e8f12d60bd1e003d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_COLLAPSE_LOOPS</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>6487654c2eed2d09ffe83c4c5698c196</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_USE_FAST_READ_ARRAY_EXPR</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>8789615e6a948d5637c0cc552b89d5b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_ARRAY_EXPR_USE_COMMON_STRIDE</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>a7d4560dcd05a710822105d84f559017</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_ARRAY_2D_STENCIL_TILING</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>32716ec3eedb16d52d41f756a6be49ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_ARRAY_2D_STENCIL_TILE_SIZE</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>1baa835a93ad64b8367aa607a77102da</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_FAST_COMPILE</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>2947d3517333d6921379ce30cc6c87f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_NEW_EXPRESSION_TEMPLATES</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>dd1e5fe1f6fdaa16086b46a12dbca7af</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_ETPARMS_CONSTREF</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>75848966586751a749481f6d97ac7a56</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_NO_INLINE_ET</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>66dd87cce7293377783496148cf6a1a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_bz_inline1</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>3378a9caa79efbf77660a18471f4f2e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_bz_inline2</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>6848dd8288da8ca7c75f65e75d3ec302</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_bz_inline_et</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>31026bac941bf7709da55dccf45eb3dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_ETPARM</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>92a6f3aa8f4cd5ac9b4239c449892bb7</anchor>
      <arglist>(X)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BZ_NO_PROPAGATE</name>
      <anchorfile>tuning_8h.html</anchorfile>
      <anchor>4c1b0ef53204ec1e49d2dd3032f392b1</anchor>
      <arglist>(X)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tvcross.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>tvcross_8h</filename>
    <member kind="function">
      <type>TinyVector&lt; T_numtype, 3 &gt;</type>
      <name>cross</name>
      <anchorfile>tvcross_8h.html</anchorfile>
      <anchor>e47fb100a352427f0d783cdb87d3e27f</anchor>
      <arglist>(const TinyVector&lt; T_numtype, 3 &gt; &amp;x, const TinyVector&lt; T_numtype, 3 &gt; &amp;y)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tvecglobs.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>tvecglobs_8h</filename>
    <includes id="numtrait_8h" name="numtrait.h" local="no" imported="no">blitz/numtrait.h</includes>
    <includes id="tvcross_8h" name="tvcross.h" local="no" imported="no">blitz/tvcross.h</includes>
    <member kind="function">
      <type></type>
      <name>BZ_PROMOTE</name>
      <anchorfile>tvecglobs_8h.html</anchorfile>
      <anchor>902c05772cf5305c8f91a22127effabb</anchor>
      <arglist>(T_numtype1, T_numtype2) dot(const TinyVector&lt; T_numtype1</arglist>
    </member>
    <member kind="function">
      <type>int N_length</type>
      <name>BZ_PROMOTE</name>
      <anchorfile>tvecglobs_8h.html</anchorfile>
      <anchor>aa600945b8657841ce439e557f9ffcef</anchor>
      <arglist>(_bz_typename T_expr1::T_numtype, T_numtype2) dot(_bz_VecExpr&lt; T_expr1 &gt; a</arglist>
    </member>
    <member kind="function">
      <type>int N_length</type>
      <name>BZ_PROMOTE</name>
      <anchorfile>tvecglobs_8h.html</anchorfile>
      <anchor>efc19321965f948bda2b39697ac83493</anchor>
      <arglist>(T_numtype1, _bz_typename T_expr2::T_numtype) dot(const TinyVector&lt; T_numtype1</arglist>
    </member>
    <member kind="function">
      <type>int N_length</type>
      <name>BZ_SUMTYPE</name>
      <anchorfile>tvecglobs_8h.html</anchorfile>
      <anchor>91c7827a28251b81b53e7276cec3520c</anchor>
      <arglist>(T_numtype1) product(const TinyVector&lt; T_numtype1</arglist>
    </member>
    <member kind="function">
      <type>int N_length</type>
      <name>BZ_SUMTYPE</name>
      <anchorfile>tvecglobs_8h.html</anchorfile>
      <anchor>2c0f26b4a72b6a6ff32f3a0f5ac6fe38</anchor>
      <arglist>(T_numtype) sum(const TinyVector&lt; T_numtype</arglist>
    </member>
    <member kind="variable">
      <type>N_length &amp;</type>
      <name>a</name>
      <anchorfile>tvecglobs_8h.html</anchorfile>
      <anchor>216f1b12926358fe13133cae1db0458e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>T_numtype2</name>
      <anchorfile>tvecglobs_8h.html</anchorfile>
      <anchor>da0e78d3c976fcd1ea31d7f8c8848c51</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>T_expr2</name>
      <anchorfile>tvecglobs_8h.html</anchorfile>
      <anchor>dee3fc2533b660a712f3f01d4ea40c85</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>vecglobs.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>vecglobs_8h</filename>
    <includes id="vector_8h" name="vector.h" local="no" imported="no">blitz/vector.h</includes>
    <includes id="numtrait_8h" name="numtrait.h" local="no" imported="no">blitz/numtrait.h</includes>
    <includes id="extremum_8h" name="extremum.h" local="no" imported="no">blitz/extremum.h</includes>
  </compound>
  <compound kind="file">
    <name>veciter.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>veciter_8h</filename>
    <class kind="class">VectorIter</class>
    <class kind="class">VectorIterConst</class>
  </compound>
  <compound kind="file">
    <name>vecpick.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>vecpick_8h</filename>
    <includes id="vector_8h" name="vector.h" local="no" imported="no">blitz/vector.h</includes>
    <includes id="vecpickiter_8h" name="vecpickiter.h" local="no" imported="no">blitz/vecpickiter.h</includes>
    <class kind="class">VectorPick</class>
  </compound>
  <compound kind="file">
    <name>vecpickiter.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>vecpickiter_8h</filename>
    <includes id="vecpick_8h" name="vecpick.h" local="no" imported="no">blitz/vecpick.h</includes>
    <class kind="class">VectorPickIter</class>
    <class kind="class">VectorPickIterConst</class>
  </compound>
  <compound kind="file">
    <name>vector-et.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>vector-et_8h</filename>
    <includes id="vector_8h" name="vector.h" local="no" imported="no">blitz/vector.h</includes>
  </compound>
  <compound kind="file">
    <name>vector.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>vector_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <includes id="memblock_8h" name="memblock.h" local="no" imported="no">blitz/memblock.h</includes>
    <includes id="range_8h" name="range.h" local="no" imported="no">blitz/range.h</includes>
    <includes id="listinit_8h" name="listinit.h" local="no" imported="no">blitz/listinit.h</includes>
    <includes id="veciter_8h" name="veciter.h" local="no" imported="no">blitz/veciter.h</includes>
    <includes id="vecpick_8h" name="vecpick.h" local="no" imported="no">blitz/vecpick.h</includes>
    <includes id="vecglobs_8h" name="vecglobs.h" local="no" imported="no">blitz/vecglobs.h</includes>
    <class kind="class">Vector</class>
    <member kind="function">
      <type>ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>vector_8h.html</anchorfile>
      <anchor>cc0350bd424b50d5a25ddaf42966d0b5</anchor>
      <arglist>(ostream &amp;os, const Vector&lt; P_numtype &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>vector_8h.html</anchorfile>
      <anchor>5f3331fc409ee32619aa9f1b44b56df4</anchor>
      <arglist>(ostream &amp;os, _bz_VecExpr&lt; P_expr &gt; expr)</arglist>
    </member>
    <member kind="function">
      <type>istream &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>vector_8h.html</anchorfile>
      <anchor>3d18d1293f1223854fefa0ece2c1f78b</anchor>
      <arglist>(istream &amp;is, Vector&lt; P_numtype &gt; &amp;x)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>wrap-climits.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>wrap-climits_8h</filename>
  </compound>
  <compound kind="file">
    <name>zero.h</name>
    <path>/scratch/work/sph-blitz/blitz/blitz/</path>
    <filename>zero_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <class kind="class">ZeroElement</class>
    <member kind="define">
      <type>#define</type>
      <name>BZZERO_DECLARE</name>
      <anchorfile>zero_8h.html</anchorfile>
      <anchor>dccc21a65e503b5d0b3cee18f1089432</anchor>
      <arglist>(T)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>beta.h</name>
    <path>/scratch/work/sph-blitz/blitz/random/</path>
    <filename>beta_8h</filename>
    <includes id="uniform_8h" name="uniform.h" local="no" imported="no">random/uniform.h</includes>
    <class kind="class">Beta</class>
  </compound>
  <compound kind="file">
    <name>chisquare.h</name>
    <path>/scratch/work/sph-blitz/blitz/random/</path>
    <filename>chisquare_8h</filename>
    <includes id="gamma_8h" name="gamma.h" local="no" imported="no">random/gamma.h</includes>
    <class kind="class">ChiSquare</class>
  </compound>
  <compound kind="file">
    <name>default.h</name>
    <path>/scratch/work/sph-blitz/blitz/random/</path>
    <filename>default_8h</filename>
    <includes id="mt_8h" name="mt.h" local="no" imported="no">random/mt.h</includes>
    <class kind="struct">sharedState</class>
    <class kind="struct">independentState</class>
    <class kind="class">IRNGWrapper</class>
    <class kind="class">IRNGWrapper&lt; IRNG, sharedState &gt;</class>
    <class kind="class">IRNGWrapper&lt; IRNG, independentState &gt;</class>
    <member kind="typedef">
      <type>float</type>
      <name>defaultType</name>
      <anchorfile>default_8h.html</anchorfile>
      <anchor>502e9908e4f520c2cc1dddb53ec4bfb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>sharedState</type>
      <name>defaultState</name>
      <anchorfile>default_8h.html</anchorfile>
      <anchor>67c90e38f3537daeb0adf42aed03f5f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned int</type>
      <name>IRNG_int</name>
      <anchorfile>default_8h.html</anchorfile>
      <anchor>e26ac46cfebfb159183665501f5fe31a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>MersenneTwister</type>
      <name>defaultIRNG</name>
      <anchorfile>default_8h.html</anchorfile>
      <anchor>e00f1b48a265f0db933db81cd395a13c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>discrete-uniform.h</name>
    <path>/scratch/work/sph-blitz/blitz/random/</path>
    <filename>discrete-uniform_8h</filename>
    <includes id="default_8h" name="default.h" local="no" imported="no">random/default.h</includes>
    <class kind="class">DiscreteUniform</class>
  </compound>
  <compound kind="file">
    <name>exponential.h</name>
    <path>/scratch/work/sph-blitz/blitz/random/</path>
    <filename>exponential_8h</filename>
    <includes id="uniform_8h" name="uniform.h" local="no" imported="no">random/uniform.h</includes>
    <class kind="class">ExponentialUnit</class>
    <class kind="class">Exponential</class>
  </compound>
  <compound kind="file">
    <name>F.h</name>
    <path>/scratch/work/sph-blitz/blitz/random/</path>
    <filename>F_8h</filename>
    <includes id="gamma_8h" name="gamma.h" local="no" imported="no">random/gamma.h</includes>
    <class kind="class">F</class>
  </compound>
  <compound kind="file">
    <name>gamma.h</name>
    <path>/scratch/work/sph-blitz/blitz/random/</path>
    <filename>gamma_8h</filename>
    <includes id="uniform_8h" name="uniform.h" local="no" imported="no">random/uniform.h</includes>
    <includes id="normal_8h" name="normal.h" local="no" imported="no">random/normal.h</includes>
    <includes id="exponential_8h" name="exponential.h" local="no" imported="no">random/exponential.h</includes>
    <class kind="class">Gamma</class>
  </compound>
  <compound kind="file">
    <name>mt.h</name>
    <path>/scratch/work/sph-blitz/blitz/random/</path>
    <filename>mt_8h</filename>
    <includes id="blitz_8h" name="blitz.h" local="no" imported="no">blitz/blitz.h</includes>
    <class kind="class">MersenneTwister</class>
    <class kind="struct">MersenneTwister::BitMixer</class>
    <class kind="class">MersenneTwister::mt_state</class>
    <class kind="class">MersenneTwisterCreator</class>
    <member kind="typedef">
      <type>unsigned long</type>
      <name>twist_int</name>
      <anchorfile>mt_8h.html</anchorfile>
      <anchor>93bbc97d43027ac5ed42fc8950ac6179</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>normal.h</name>
    <path>/scratch/work/sph-blitz/blitz/random/</path>
    <filename>normal_8h</filename>
    <includes id="uniform_8h" name="uniform.h" local="no" imported="no">random/uniform.h</includes>
    <class kind="class">NormalUnit</class>
    <class kind="class">Normal</class>
  </compound>
  <compound kind="file">
    <name>uniform.h</name>
    <path>/scratch/work/sph-blitz/blitz/random/</path>
    <filename>uniform_8h</filename>
    <includes id="default_8h" name="default.h" local="no" imported="no">random/default.h</includes>
    <class kind="class">UniformClosedOpen</class>
    <class kind="class">UniformClosedOpen&lt; float, IRNG, stateTag &gt;</class>
    <class kind="class">UniformClosedOpen&lt; double, IRNG, stateTag &gt;</class>
    <class kind="class">UniformClosedOpen&lt; long double, IRNG, stateTag &gt;</class>
    <class kind="class">Uniform</class>
    <class kind="class">UniformClosed</class>
    <class kind="class">UniformClosed&lt; float, IRNG, stateTag &gt;</class>
    <class kind="class">UniformClosed&lt; double, IRNG, stateTag &gt;</class>
    <class kind="class">UniformClosed&lt; long double, IRNG, stateTag &gt;</class>
    <class kind="class">UniformOpen</class>
    <class kind="class">UniformOpenClosed</class>
    <member kind="variable">
      <type>const long double</type>
      <name>norm32open</name>
      <anchorfile>uniform_8h.html</anchorfile>
      <anchor>d0218c6128f9c9eb41935b8d294d69ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const long double</type>
      <name>norm64open</name>
      <anchorfile>uniform_8h.html</anchorfile>
      <anchor>9a3e5c4a3845a46eb81d34e2a876b8b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const long double</type>
      <name>norm96open</name>
      <anchorfile>uniform_8h.html</anchorfile>
      <anchor>18d21227ed4ccec6943fe31526fa8c98</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const long double</type>
      <name>norm128open</name>
      <anchorfile>uniform_8h.html</anchorfile>
      <anchor>7c74976cfa181bbeea25a059e2619d90</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const long double</type>
      <name>norm32closed</name>
      <anchorfile>uniform_8h.html</anchorfile>
      <anchor>b98ac6b9805ac42c4e76b6e4f7da23ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const long double</type>
      <name>norm64closed1</name>
      <anchorfile>uniform_8h.html</anchorfile>
      <anchor>ca3c2cdd39ecfa7971c98afb668d4041</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const long double</type>
      <name>norm64closed2</name>
      <anchorfile>uniform_8h.html</anchorfile>
      <anchor>e81cbbec5102db6bc3ee563f136bb5e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const long double</type>
      <name>norm96closed1</name>
      <anchorfile>uniform_8h.html</anchorfile>
      <anchor>2b6111a39588d8f74918fa08bc3d1f31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const long double</type>
      <name>norm96closed2</name>
      <anchorfile>uniform_8h.html</anchorfile>
      <anchor>ebde60f12db062150d6ff6c1cbbe422b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const long double</type>
      <name>norm96closed3</name>
      <anchorfile>uniform_8h.html</anchorfile>
      <anchor>74edf793a3d854cb462261d687608862</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const long double</type>
      <name>norm128clos1</name>
      <anchorfile>uniform_8h.html</anchorfile>
      <anchor>6059e6384ad3533e736e82b677486507</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const long double</type>
      <name>norm128clos2</name>
      <anchorfile>uniform_8h.html</anchorfile>
      <anchor>d5ac08a77012b3acff3f8b80c92fdcf7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const long double</type>
      <name>norm128clos3</name>
      <anchorfile>uniform_8h.html</anchorfile>
      <anchor>ed5dcd0cb259e5e5523cc1f27c964337</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const long double</type>
      <name>norm128clos4</name>
      <anchorfile>uniform_8h.html</anchorfile>
      <anchor>f39d213f9d069af841e564aea5808271</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Add</name>
    <filename>structAdd.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type>typedef</type>
      <name>BZ_PROMOTE</name>
      <anchorfile>structAdd.html</anchorfile>
      <anchor>1b988ee2b2a89a3255e191e3b02ba2be</anchor>
      <arglist>(T_numtype1, T_numtype2) T_numtype</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structAdd.html</anchorfile>
      <anchor>ef2e8b0b0110a53c5d04f08c0b5ce0b0</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structAdd.html</anchorfile>
      <anchor>5afa3a15f6bee783898080ac9404156d</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Array</name>
    <filename>classArray.html</filename>
    <templarg>P_numtype</templarg>
    <templarg>N_rank</templarg>
    <base>MemoryBlockReference&lt; P_numtype &gt;</base>
    <member kind="typedef">
      <type>P_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>e72770f4a1d2f8b7193badafc320f008</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TinyVector&lt; int, N_rank &gt;</type>
      <name>T_index</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f3e455aedb140b84cee777ecdf2e846e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Array&lt; T_numtype, N_rank &gt;</type>
      <name>T_array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>6a3d9b6a214107a10df219091801f1e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FastArrayIterator&lt; T_numtype, N_rank &gt;</type>
      <name>T_iterator</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>6975ccd49584b470e7b952b8acd598f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ArrayIterator&lt; T_numtype, N_rank &gt;</type>
      <name>iterator</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>3c33a296e6b0d7290b3f2221660f70f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ConstArrayIterator&lt; T_numtype, N_rank &gt;</type>
      <name>const_iterator</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>d00ebe258c5672331aad96dc6d7299ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>927055ca8c0136ec48f77b89f2533c02</anchor>
      <arglist>(_bz_ArrayExpr&lt; T_expr &gt; expr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f10c516fbc0c99761b4a1493f1431126</anchor>
      <arglist>(GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>bc50cddb9eada342bccd0b87e9df35d9</anchor>
      <arglist>(int length0, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>e639e151d7e76875d12290f28ac1873f</anchor>
      <arglist>(int length0, int length1, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>d3094229384e53e54ab674f269232961</anchor>
      <arglist>(int length0, int length1, int length2, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>afeae20c60c1ddb68b95f17769d2f4df</anchor>
      <arglist>(int length0, int length1, int length2, int length3, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>a80b196ce2441a38d5622dabfb239090</anchor>
      <arglist>(int length0, int length1, int length2, int length3, int length4, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>e7f870270cc5b8f5b8f85e6aba08bdf2</anchor>
      <arglist>(int length0, int length1, int length2, int length3, int length4, int length5, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>ac77f0608a2e3076073f4167a136cc49</anchor>
      <arglist>(int length0, int length1, int length2, int length3, int length4, int length5, int length6, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f9409843b5a233a9b43e85e4b7b55ce8</anchor>
      <arglist>(int length0, int length1, int length2, int length3, int length4, int length5, int length6, int length7, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>7ee46ec1e7c70e46b81aca4740ad2ee7</anchor>
      <arglist>(int length0, int length1, int length2, int length3, int length4, int length5, int length6, int length7, int length8, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>9cdece0c22b465d48b178d8d34b48b90</anchor>
      <arglist>(int length0, int length1, int length2, int length3, int length4, int length5, int length6, int length7, int length8, int length9, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f64c44993c0e2aa414254d507d919db5</anchor>
      <arglist>(int length0, int length1, int length2, int length3, int length4, int length5, int length6, int length7, int length8, int length9, int length10, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>219a4aaab73ed4978400823ebd09e78e</anchor>
      <arglist>(T_numtype *restrict dataFirst, TinyVector&lt; int, N_rank &gt; shape, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>2c8b979a920c79da5da56371f2d0c8fa</anchor>
      <arglist>(T_numtype *restrict dataFirst, TinyVector&lt; int, N_rank &gt; shape, TinyVector&lt; diffType, N_rank &gt; stride, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>5a9cc589b8ebfbdb4346ee6d8d0a2c0d</anchor>
      <arglist>(T_numtype *restrict dataFirst, TinyVector&lt; int, N_rank &gt; shape, preexistingMemoryPolicy deletionPolicy, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>79bc92a4c7937d19403e3d9c95fd86c8</anchor>
      <arglist>(T_numtype *restrict dataFirst, TinyVector&lt; int, N_rank &gt; shape, TinyVector&lt; diffType, N_rank &gt; stride, preexistingMemoryPolicy deletionPolicy, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c0d72e6c28d65dd26c943bf2bc43a475</anchor>
      <arglist>(const TinyVector&lt; int, N_rank &gt; &amp;extent, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>00f1792ac9d4f8b56959d2778e83ed3c</anchor>
      <arglist>(const TinyVector&lt; int, N_rank &gt; &amp;lbounds, const TinyVector&lt; int, N_rank &gt; &amp;extent, const GeneralArrayStorage&lt; N_rank &gt; &amp;storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>41920fea594ff80d74e4501c4c2ce7c7</anchor>
      <arglist>(Range r0, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>d2cdb01aa8562b2e66d4035f5c17859f</anchor>
      <arglist>(Range r0, Range r1, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>8ef721482e73258e9efab67bf0ccc24e</anchor>
      <arglist>(Range r0, Range r1, Range r2, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b24a1bbedcdb2512b7446502e60ab265</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>85363956915d2a24f7c840d5db6cf524</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, Range r4, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>6ec1fb88fac78b338b527d77a0cfaf1e</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>1e8aaad12df193ef81b1b9eb25ccb61a</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>3bee2faf05539d9eb7e279c4e83e3272</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f626ea7167781de7907bad490fdf1c74</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>14b17c0bb12d622128f65a6466c1e838</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8, Range r9, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f0f46e946511589d826f875efe8fab8f</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8, Range r9, Range r10, GeneralArrayStorage&lt; N_rank &gt; storage=GeneralArrayStorage&lt; N_rank &gt;())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>ae3f503c4e24baf1e34676fb2051ebdc</anchor>
      <arglist>(const Array&lt; T_numtype, N_rank &gt; &amp;array)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>1a4bfc463ae3ec6e66f8db5eacae42b7</anchor>
      <arglist>(const TinyVector&lt; int, N_rank-1 &gt; &amp;shape, int lastExtent, const GeneralArrayStorage&lt; N_rank &gt; &amp;storage)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>23685ffa9c88e01d44e57bff381c8eea</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>deb9d3d9688c1991f7e6de60c24072f6</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>a715fe702709fb8bf943ea36391c25a7</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>5ed992128a3321bbf63c84453e4c7379</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>8267a048ca4ac2d83c8a12639ff7e77b</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3, Range r4)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>56c9149e233fa8e70c8766da66afde43</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>2845c57182d32e786b2be49b887b2a7d</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>6d92e3e7d8efe7343f44659b77bcfcfa</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c246270b9040a13168fac24db54a35dc</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>9813f50a7920f623e3e190145347d1a2</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8, Range r9)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>919bc6fe9f1c4bb8f623b0b2a58873e0</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8, Range r9, Range r10)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>9bf897f3f05a46549b72c52768e73c2e</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, const RectDomain&lt; N_rank &gt; &amp;subdomain)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>83539a81cc6b318b517cbd8af6bd5ea9</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, const StridedDomain&lt; N_rank &gt; &amp;subdomain)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>e60ec91262a2561412fb86c359b47a0b</anchor>
      <arglist>(Array&lt; T_numtype, N_rank2 &gt; &amp;array, R0 r0, R1 r1, R2 r2, R3 r3, R4 r4, R5 r5, R6 r6, R7 r7, R8 r8, R9 r9, R10 r10)</arglist>
    </member>
    <member kind="function">
      <type>const TinyVector&lt; int, N_rank &gt; &amp;</type>
      <name>base</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>979034b77c884359d3022eb773301c47</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>base</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>011a44e3e6e97990198aa621d3fe054c</anchor>
      <arglist>(int rank) const </arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>fef13d900474b924dca8dd2f401f8bda</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>2054b0a114c5f320babdf2260513e67f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_iterator</type>
      <name>beginFast</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>fd7ebedba352bafaf360826b551585d0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Array&lt; P_numtype2, N_rank &gt;</type>
      <name>chopComponent</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>5982c184cbce1ac69ce3bdddeca64c48</anchor>
      <arglist>(P_numtype2 a, int compNum, int numComponents) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>cols</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>553797ddb83a9067e6bdcdeafe16207f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>columns</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>e940de0329ca6515a808165d3407ee35</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>copy</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>4f3e75405a8382c97b4aa19bb23cc104</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>diffType</type>
      <name>dataOffset</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>0af9d56ba4dff19a1eb16d703082a7c9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const T_numtype *restrict</type>
      <name>data</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>3a274253c2e3b391777f9e10542b8322</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype *restrict</type>
      <name>data</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>5bface1d3609ecf211265bd7b23a881b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype *restrict</type>
      <name>dataZero</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>04566dfbb67a5547cf85f398f681d589</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype *restrict</type>
      <name>dataZero</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>9a31a58f9c9962663982b083540a673b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>diffType</type>
      <name>dataFirstOffset</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>59ca10f1780a672dfaf1ebc798678a49</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const T_numtype *restrict</type>
      <name>dataFirst</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>11659c9e06ad710292be467d337adc0f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype *restrict</type>
      <name>dataFirst</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b8997d7b06c92fa8cf8a6d5db6f84aaf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>depth</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>efb89a7b950cd164199ba6a95feb3389</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dimensions</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>284bc99bd70755aff7fabf81105a7fe8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RectDomain&lt; N_rank &gt;</type>
      <name>domain</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>cdc2828fb8f40c142359e43910d5873a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dumpStructureInformation</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>36728606d550899621cd180cd5ef08df</anchor>
      <arglist>(ostream &amp;os=cout) const </arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>end</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b7821a48f66e2e75ebdff82395bd7095</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>end</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>a609b8698ccad3e8940533dec11d201a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>extent</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>0e366d6568c6f976ea3657fea13794b7</anchor>
      <arglist>(int rank) const </arglist>
    </member>
    <member kind="function">
      <type>const TinyVector&lt; int, N_rank &gt; &amp;</type>
      <name>extent</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>3c4295ecd7768bac320585eb3eb06c0d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Array&lt; P_numtype2, N_rank &gt;</type>
      <name>extractComponent</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>bdb130ded970927647b424c003dfa5e5</anchor>
      <arglist>(P_numtype2, int compNum, int numComponents) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>free</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>dee40224d813e0b6a4cb630a79cd9245</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isMajorRank</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>0747ff0953c663e28e1f854bafb74c4b</anchor>
      <arglist>(int rank) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isMinorRank</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c4d39efdbef1a1bdfef9ddb9e935b890</anchor>
      <arglist>(int rank) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isRankStoredAscending</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>a95744e1a65d959532be79597300cbcf</anchor>
      <arglist>(int rank) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isStorageContiguous</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>8531b2babb2fd35de4b78a0cec697e3a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>lbound</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>bd6504340a3749bd72c81e9eafb66df6</anchor>
      <arglist>(int rank) const </arglist>
    </member>
    <member kind="function">
      <type>TinyVector&lt; int, N_rank &gt;</type>
      <name>lbound</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>155ceb0f9cc12e4c8e0dad380607f522</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>length</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>11c4ec818e48dfdc79a9ee9c58a17ed3</anchor>
      <arglist>(int rank) const </arglist>
    </member>
    <member kind="function">
      <type>const TinyVector&lt; int, N_rank &gt; &amp;</type>
      <name>length</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>3fb4906eee4cc7dd70a36b91ca0d6e62</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>makeUnique</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c81798775d9c34b90101510cfddf1643</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>sizeType</type>
      <name>numElements</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>1fd17bab48da66e05d4696fe0689b14b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ordering</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>7ed8835e2688a94d66a2ca953ae0b1cf</anchor>
      <arglist>(int storageRankIndex) const </arglist>
    </member>
    <member kind="function">
      <type>const TinyVector&lt; int, N_rank &gt; &amp;</type>
      <name>ordering</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>4698d990150249236c503cd17f54a3e9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transposeSelf</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>21add749c176f45a5a8e14d5e5067936</anchor>
      <arglist>(int r0, int r1, int r2=0, int r3=0, int r4=0, int r5=0, int r6=0, int r7=0, int r8=0, int r9=0, int r10=0)</arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>transpose</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>5f451c032755441026d65075c78c0708</anchor>
      <arglist>(int r0, int r1, int r2=0, int r3=0, int r4=0, int r5=0, int r6=0, int r7=0, int r8=0, int r9=0, int r10=0) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>rank</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>1563c492c1be9d9b95a3f53d9cd89fae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reference</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>29647009b556bbddaa71c10ad2256f4c</anchor>
      <arglist>(const T_array &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>weakReference</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>49ff4f9d7b82fb7f423107987e9709e6</anchor>
      <arglist>(const T_array &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>reindex</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>d368b8b5e786d6d84ff8c21087283a5e</anchor>
      <arglist>(const TinyVector&lt; int, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reindexSelf</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b28ed685bca2bf700bf694e494539bbe</anchor>
      <arglist>(const TinyVector&lt; int, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>0424fd6f39f538181c81e4e88d00ca06</anchor>
      <arglist>(int extent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>87b0a62ead0e9f5b9301c136f84cd905</anchor>
      <arglist>(int extent1, int extent2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>d9645f153b9cb813a48921218ab98d56</anchor>
      <arglist>(int extent1, int extent2, int extent3)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>9064c917ba0bbfe654fbc5f15cd4f10d</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>d5f4f5d5dd60695d44fa7fd89dcae1f6</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4, int extent5)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>75b45780cf8fa23529efe8919267d64c</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>e73a1aba093cb7b2b1e55c93a6cd6e16</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6, int extent7)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>10a80555b4803195f5a3af36e8eb67c2</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6, int extent7, int extent8)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>e84f84322b8a5c6548a1e5129749bd59</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6, int extent7, int extent8, int extent9)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>7e131cc801b01b56151e470a9efa1f32</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6, int extent7, int extent8, int extent9, int extent10)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>a61eabd09786a151e4da0852105bd0d0</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6, int extent7, int extent8, int extent9, int extent10, int extent11)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>4522b1267ad81224a7290c6ba2d995ec</anchor>
      <arglist>(Range r1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>1c139020b6659b6ed5ae94ce54a11168</anchor>
      <arglist>(Range r1, Range r2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>de35a5046e18b7214e8a20c7537e278e</anchor>
      <arglist>(Range r1, Range r2, Range r3)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>3bb8ef7913bed965d2be42d122958a8a</anchor>
      <arglist>(Range r1, Range r2, Range r3, Range r4)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>81d3a34ab367c298b2b1f0278acb561b</anchor>
      <arglist>(Range r1, Range r2, Range r3, Range r4, Range r5)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>ede426d3052e5ee1c447ac88db108985</anchor>
      <arglist>(Range r1, Range r2, Range r3, Range r4, Range r5, Range r6)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>8219bd262073a8829bef568e838875f3</anchor>
      <arglist>(Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>554f2ad144a05d64f8e4edcb74c9f483</anchor>
      <arglist>(Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>dba6b3b9526e8f1ca38cf0d9318267d0</anchor>
      <arglist>(Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8, Range r9)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>a55c2bcd27e5a61d368d5314d29f4a73</anchor>
      <arglist>(Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8, Range r9, Range r10)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>60b65afca568282720f4137d608fa956</anchor>
      <arglist>(Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8, Range r9, Range r10, Range r11)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>263735ac141c67cfb77fd27b8989504c</anchor>
      <arglist>(const TinyVector&lt; int, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resizeAndPreserve</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>2423ec5bd415b4445622af8f55df6c5e</anchor>
      <arglist>(const TinyVector&lt; int, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resizeAndPreserve</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>de1025d35d5f90e0753b2810964d722e</anchor>
      <arglist>(int extent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resizeAndPreserve</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>3641a81c23bb5a3a329264093433f703</anchor>
      <arglist>(int extent1, int extent2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resizeAndPreserve</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>ff1de2e7b62e66a7b8e935a91ab99de1</anchor>
      <arglist>(int extent1, int extent2, int extent3)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resizeAndPreserve</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>463e37f0eda165111a461d2e6d71df28</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resizeAndPreserve</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f53fad58b5426946fb0c247b61a9e130</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4, int extent5)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resizeAndPreserve</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>9590e881fb1a6ef74fa2979a863e275f</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resizeAndPreserve</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f48202c44a9a834320f2544bb44392e6</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6, int extent7)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resizeAndPreserve</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>67f8b078e2e9c71002c00c554a3d0400</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6, int extent7, int extent8)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resizeAndPreserve</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>6f165a5193f1c123e90e82ddf29daa81</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6, int extent7, int extent8, int extent9)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resizeAndPreserve</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>488c1b7ef9e12c5e4dc10aabad310234</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6, int extent7, int extent8, int extent9, int extent10)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resizeAndPreserve</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>54b0c4651fbde1aa3c04a2be87abcbda</anchor>
      <arglist>(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6, int extent7, int extent8, int extent9, int extent10, int extent11)</arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>reverse</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>5c78cf4ba4772493d615fb5d3099cb3b</anchor>
      <arglist>(int rank)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reverseSelf</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>7bc91c4e6b2e77e846ad72f190218a19</anchor>
      <arglist>(int rank)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>rows</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>aae7a86f1c37f1ad4c53fc399a52e9ee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStorage</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>338c42b0e31221626c6691aa3754f8d2</anchor>
      <arglist>(GeneralArrayStorage&lt; N_rank &gt;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>slice</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>d0d4f12effc963adb6806e426c144d32</anchor>
      <arglist>(int rank, Range r)</arglist>
    </member>
    <member kind="function">
      <type>const TinyVector&lt; int, N_rank &gt; &amp;</type>
      <name>shape</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>ab2fe0a092fc7acfcdbac8e24dfc1252</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>sizeType</type>
      <name>size</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>4fe7ad40e688858f794f774eaa3c64c2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const TinyVector&lt; diffType, N_rank &gt; &amp;</type>
      <name>stride</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f76fe7a0837cf39e20d13c2ecbf81403</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>diffType</type>
      <name>stride</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>964ed6dbd4a5cc127ac98f2ee2f048bb</anchor>
      <arglist>(int rank) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>threadLocal</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>8afdcc7bddb00b4d1d251c25db549c2f</anchor>
      <arglist>(bool disableLock=true) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ubound</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>799c0842a3880e9bdb9bff8982a160d4</anchor>
      <arglist>(int rank) const </arglist>
    </member>
    <member kind="function">
      <type>TinyVector&lt; int, N_rank &gt;</type>
      <name>ubound</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>84ea6af8156a3b36e10f1fa33df50256</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>zeroOffset</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f3fa33b513aea465f6ce63da56443d46</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRangeForDim</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>682cb0bb827cf05338782479591a651f</anchor>
      <arglist>(int i, int d) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>245c73e8d90b746d4b91aa943be1043f</anchor>
      <arglist>(int i0) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>d00bdc689557a020bb9ccb44a5f629bd</anchor>
      <arglist>(int i0, int i1) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>89d93d7807d693a6897c91c4f1ad6d43</anchor>
      <arglist>(int i0, int i1, int i2) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>bbd656747a51ffa3dcaf3671ad5c2c54</anchor>
      <arglist>(int i0, int i1, int i2, int i3) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>72584ead99ac458995622a0143924c0c</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>fcf6f542300b7941583ad07c34252efd</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c887b928fc20eabcc722801e4981c0b8</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>8f4c45c9856d0df38fc44bfa858ef163</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>2266f1badf3bdbb3da86484c95be000d</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>9044150868f7dae5ed3b7cc6fbde99e6</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>4487c6055a182af2fbcb172e70301731</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>1abdd56e997951cbbca3a7a92934adf0</anchor>
      <arglist>(const T_index &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>assertInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>110673aa7e2c6530fc72fa33112ebb63</anchor>
      <arglist>(const T_index &amp;BZ_DEBUG_PARAM(index)) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>assertInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f03f904e949df8e6575a433e8a0d1ddf</anchor>
      <arglist>(int BZ_DEBUG_PARAM(i0)) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>assertInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>9a3b768c9fd3ca9af1787334d56514e6</anchor>
      <arglist>(int BZ_DEBUG_PARAM(i0), int BZ_DEBUG_PARAM(i1)) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>assertInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>803193739d6a69fce9ce508c7fbf8bcf</anchor>
      <arglist>(int BZ_DEBUG_PARAM(i0), int BZ_DEBUG_PARAM(i1), int BZ_DEBUG_PARAM(i2)) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>assertInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b65cb740e180b3b7eb55d89cefd71cd6</anchor>
      <arglist>(int BZ_DEBUG_PARAM(i0), int BZ_DEBUG_PARAM(i1), int BZ_DEBUG_PARAM(i2), int BZ_DEBUG_PARAM(i3)) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>assertInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>bbd9f6fab1024bd8f097f4fe311f3705</anchor>
      <arglist>(int BZ_DEBUG_PARAM(i0), int BZ_DEBUG_PARAM(i1), int BZ_DEBUG_PARAM(i2), int BZ_DEBUG_PARAM(i3), int BZ_DEBUG_PARAM(i4)) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>assertInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>18a47a652c9c11daf90dadb840eb0778</anchor>
      <arglist>(int BZ_DEBUG_PARAM(i0), int BZ_DEBUG_PARAM(i1), int BZ_DEBUG_PARAM(i2), int BZ_DEBUG_PARAM(i3), int BZ_DEBUG_PARAM(i4), int BZ_DEBUG_PARAM(i5)) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>assertInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>3c1d55f425cdaf6fbb99d27277a005ad</anchor>
      <arglist>(int BZ_DEBUG_PARAM(i0), int BZ_DEBUG_PARAM(i1), int BZ_DEBUG_PARAM(i2), int BZ_DEBUG_PARAM(i3), int BZ_DEBUG_PARAM(i4), int BZ_DEBUG_PARAM(i5), int BZ_DEBUG_PARAM(i6)) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>assertInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>78437f013adb4f993a86b4b799450be4</anchor>
      <arglist>(int BZ_DEBUG_PARAM(i0), int BZ_DEBUG_PARAM(i1), int BZ_DEBUG_PARAM(i2), int BZ_DEBUG_PARAM(i3), int BZ_DEBUG_PARAM(i4), int BZ_DEBUG_PARAM(i5), int BZ_DEBUG_PARAM(i6), int BZ_DEBUG_PARAM(i7)) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>assertInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>aba60fa30c802d54d18a991c4469076e</anchor>
      <arglist>(int BZ_DEBUG_PARAM(i0), int BZ_DEBUG_PARAM(i1), int BZ_DEBUG_PARAM(i2), int BZ_DEBUG_PARAM(i3), int BZ_DEBUG_PARAM(i4), int BZ_DEBUG_PARAM(i5), int BZ_DEBUG_PARAM(i6), int BZ_DEBUG_PARAM(i7), int BZ_DEBUG_PARAM(i8)) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>assertInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c65b522bc8222deb0b2aee6b37a8bfbe</anchor>
      <arglist>(int BZ_DEBUG_PARAM(i0), int BZ_DEBUG_PARAM(i1), int BZ_DEBUG_PARAM(i2), int BZ_DEBUG_PARAM(i3), int BZ_DEBUG_PARAM(i4), int BZ_DEBUG_PARAM(i5), int BZ_DEBUG_PARAM(i6), int BZ_DEBUG_PARAM(i7), int BZ_DEBUG_PARAM(i8), int BZ_DEBUG_PARAM(i9)) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>assertInRange</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c1601ef44f92cc6b7bb767afbb1f159b</anchor>
      <arglist>(int BZ_DEBUG_PARAM(i0), int BZ_DEBUG_PARAM(i1), int BZ_DEBUG_PARAM(i2), int BZ_DEBUG_PARAM(i3), int BZ_DEBUG_PARAM(i4), int BZ_DEBUG_PARAM(i5), int BZ_DEBUG_PARAM(i6), int BZ_DEBUG_PARAM(i7), int BZ_DEBUG_PARAM(i8), int BZ_DEBUG_PARAM(i9), int BZ_DEBUG_PARAM(i10)) const </arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>27cd8a94748e057e60ad44d15ce5ec5c</anchor>
      <arglist>(const TinyVector&lt; int, N_rank2 &gt; &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>218e20bb039982abbc7e3f152a62e031</anchor>
      <arglist>(const TinyVector&lt; int, N_rank2 &gt; &amp;index)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>65cfd90e9df2299bd405ece006520484</anchor>
      <arglist>(TinyVector&lt; int, 1 &gt; index) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>9d67eda4b44963c9c470df762de93e06</anchor>
      <arglist>(TinyVector&lt; int, 1 &gt; index)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>6eb659f5dc3e23491f8da81f415a2b95</anchor>
      <arglist>(TinyVector&lt; int, 2 &gt; index) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>efd3aafd5bc4128581b61d20ff301e40</anchor>
      <arglist>(TinyVector&lt; int, 2 &gt; index)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>48ccde3bedca818bb67390818d05e492</anchor>
      <arglist>(TinyVector&lt; int, 3 &gt; index) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>2f3b69e4d9199756253a178b7bbe2936</anchor>
      <arglist>(TinyVector&lt; int, 3 &gt; index)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>1513d0330d79e1f0051fdb02b777507d</anchor>
      <arglist>(const TinyVector&lt; int, 4 &gt; &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b8e3a9b188cb388acabc8005dc1e6f6f</anchor>
      <arglist>(const TinyVector&lt; int, 4 &gt; &amp;index)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>2c48c16a7aba185cb6e71af4588df1ba</anchor>
      <arglist>(const TinyVector&lt; int, 5 &gt; &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c3afef5299296665c6163740ca625e2e</anchor>
      <arglist>(const TinyVector&lt; int, 5 &gt; &amp;index)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>366456aa63f9f9b54ade2e5ce2de8f9a</anchor>
      <arglist>(const TinyVector&lt; int, 6 &gt; &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>68955d7efb206caf0365b81286f5430d</anchor>
      <arglist>(const TinyVector&lt; int, 6 &gt; &amp;index)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>33104477dc9ae6b2eae364f7e3f9dfba</anchor>
      <arglist>(const TinyVector&lt; int, 7 &gt; &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>fe7da01389d310f5c7619fa138444e78</anchor>
      <arglist>(const TinyVector&lt; int, 7 &gt; &amp;index)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>4e2a5777a148764b69e5d44ff842dc48</anchor>
      <arglist>(const TinyVector&lt; int, 8 &gt; &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>8e8020e92047dfb639d86e111fd4c1d3</anchor>
      <arglist>(const TinyVector&lt; int, 8 &gt; &amp;index)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>5332878401c9ec81caefa6bf54772ca0</anchor>
      <arglist>(const TinyVector&lt; int, 9 &gt; &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>9a18fd394f552ed38d5f09a2f0ad580f</anchor>
      <arglist>(const TinyVector&lt; int, 9 &gt; &amp;index)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>9fb1eda95e4bb0d2e112d84e134c5002</anchor>
      <arglist>(const TinyVector&lt; int, 10 &gt; &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>39772df419b0a5fd899a0a66bd45e2d9</anchor>
      <arglist>(const TinyVector&lt; int, 10 &gt; &amp;index)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>cb3302e30614fce17397949fff9ae956</anchor>
      <arglist>(const TinyVector&lt; int, 11 &gt; &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>7980e02a2354e9ef45b3533bc0394314</anchor>
      <arglist>(const TinyVector&lt; int, 11 &gt; &amp;index)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>6e7d61ee6e4837348498d844f2a2f751</anchor>
      <arglist>(int i0) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>65567fb25e7218c096cab93061caa915</anchor>
      <arglist>(int i0)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>a44208dec3b1b98b44c409112611c9b5</anchor>
      <arglist>(int i0, int i1) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c8f2c863ca0c58623350eeeca3d33c25</anchor>
      <arglist>(int i0, int i1)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>ec6c025ed9dd4bd84562109087cc55d1</anchor>
      <arglist>(int i0, int i1, int i2) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>5885740fad97d942e602b11b28c36f58</anchor>
      <arglist>(int i0, int i1, int i2)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f7f62a57b8284c624a790d54e835fd88</anchor>
      <arglist>(int i0, int i1, int i2, int i3) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>a0bba23d41fdb439c367b815a5d17509</anchor>
      <arglist>(int i0, int i1, int i2, int i3)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>0b8def9e3a03ffef3a53954f4f914cf5</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>29483f6eb364743e6a1df32124e10827</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>9bc5ee06b4ebd746a3892e4de1e888db</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>d3e846c42e7a0341dc90038b3424031b</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c9ac4222b4333cf21e281428337d502d</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>e1f10edf11dcd139126c2bc601c883e6</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>0805e7a26dc985ef4dabf3f9cbe0a8c8</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>07109b392a392aacea32bb6641dd2262</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>30e0bf01b5c84c0345f7870390bbf18a</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>3cf3c81a4b8fda25bf0f3e1536b755cf</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>5aa6face3070826707d04865d076f117</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f55d0cd88bba0b3f518db325484649b8</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>de03e79f6d6f3ae9b82a745f25adb279</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b69d1c914293c899e5220773b61b93cd</anchor>
      <arglist>(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>noConst</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>90ce3c59fa9b26ea251e092e7ae5f027</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>a302def8dcf46382b2680e5ea3e94e13</anchor>
      <arglist>(const RectDomain&lt; N_rank &gt; &amp;subdomain) const </arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>d089654bfd25b024abc75003f0d747c5</anchor>
      <arglist>(const StridedDomain&lt; N_rank &gt; &amp;subdomain) const </arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>237833cefd0a253ddcf810cb5ae8ceba</anchor>
      <arglist>(Range r0) const </arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>2fd0c5a123d22ffa5f0bd7ac3e9f01c4</anchor>
      <arglist>(Range r0, Range r1) const </arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>5133307661f35b6a567dd26c3b6af85e</anchor>
      <arglist>(Range r0, Range r1, Range r2) const </arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>5da3752af4bbc20607168da1eca63f8b</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3) const </arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>ca7b645f641c603fb6eb81a92f34d92c</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, Range r4) const </arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>0b8a10b82d1d05320e5838be4161950c</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5) const </arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c994507c928299f379694fd3ce091c1d</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6) const </arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>a6d69693d4935f73677aa78d4036f473</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7) const </arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f10d31d5f873244b7dfde21c16c11d1c</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8) const </arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>1cc4d575d988f8e881486bd5b3e34121</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8, Range r9) const </arglist>
    </member>
    <member kind="function">
      <type>T_array</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>23c20788f30e00e26dd3b4b865f21d26</anchor>
      <arglist>(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8, Range r9, Range r10) const </arglist>
    </member>
    <member kind="function">
      <type>_bz_ArrayExpr&lt; ArrayIndexMapping&lt; FastArrayIterator&lt; T_numtype, N_rank &gt;, N0 &gt; &gt;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>20207b4e5b86a95afb87fd1c52387bc7</anchor>
      <arglist>(IndexPlaceholder&lt; N0 &gt;) const </arglist>
    </member>
    <member kind="function">
      <type>_bz_ArrayExpr&lt; ArrayIndexMapping&lt; FastArrayIterator&lt; T_numtype, N_rank &gt;, N0, N1 &gt; &gt;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>01bef186a31f43b1b340d5051edd9e8a</anchor>
      <arglist>(IndexPlaceholder&lt; N0 &gt;, IndexPlaceholder&lt; N1 &gt;) const </arglist>
    </member>
    <member kind="function">
      <type>_bz_ArrayExpr&lt; ArrayIndexMapping&lt; FastArrayIterator&lt; T_numtype, N_rank &gt;, N0, N1, N2 &gt; &gt;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>887af2f3b5bf926644ad9c0766e1d83d</anchor>
      <arglist>(IndexPlaceholder&lt; N0 &gt;, IndexPlaceholder&lt; N1 &gt;, IndexPlaceholder&lt; N2 &gt;) const </arglist>
    </member>
    <member kind="function">
      <type>_bz_ArrayExpr&lt; ArrayIndexMapping&lt; FastArrayIterator&lt; T_numtype, N_rank &gt;, N0, N1, N2, N3 &gt; &gt;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>fc546e9bac17efa3f95f789dc327f63b</anchor>
      <arglist>(IndexPlaceholder&lt; N0 &gt;, IndexPlaceholder&lt; N1 &gt;, IndexPlaceholder&lt; N2 &gt;, IndexPlaceholder&lt; N3 &gt;) const </arglist>
    </member>
    <member kind="function">
      <type>_bz_ArrayExpr&lt; ArrayIndexMapping&lt; FastArrayIterator&lt; T_numtype, N_rank &gt;, N0, N1, N2, N3, N4 &gt; &gt;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c9a452e4b53fd7e6c31ffb1eb960b1ef</anchor>
      <arglist>(IndexPlaceholder&lt; N0 &gt;, IndexPlaceholder&lt; N1 &gt;, IndexPlaceholder&lt; N2 &gt;, IndexPlaceholder&lt; N3 &gt;, IndexPlaceholder&lt; N4 &gt;) const </arglist>
    </member>
    <member kind="function">
      <type>_bz_ArrayExpr&lt; ArrayIndexMapping&lt; FastArrayIterator&lt; T_numtype, N_rank &gt;, N0, N1, N2, N3, N4, N5 &gt; &gt;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>8c9d93b45255a6cf53add6e4f5381e3b</anchor>
      <arglist>(IndexPlaceholder&lt; N0 &gt;, IndexPlaceholder&lt; N1 &gt;, IndexPlaceholder&lt; N2 &gt;, IndexPlaceholder&lt; N3 &gt;, IndexPlaceholder&lt; N4 &gt;, IndexPlaceholder&lt; N5 &gt;) const </arglist>
    </member>
    <member kind="function">
      <type>_bz_ArrayExpr&lt; ArrayIndexMapping&lt; FastArrayIterator&lt; T_numtype, N_rank &gt;, N0, N1, N2, N3, N4, N5, N6 &gt; &gt;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b14d323a8df7d79fd9af4470cd747ee3</anchor>
      <arglist>(IndexPlaceholder&lt; N0 &gt;, IndexPlaceholder&lt; N1 &gt;, IndexPlaceholder&lt; N2 &gt;, IndexPlaceholder&lt; N3 &gt;, IndexPlaceholder&lt; N4 &gt;, IndexPlaceholder&lt; N5 &gt;, IndexPlaceholder&lt; N6 &gt;) const </arglist>
    </member>
    <member kind="function">
      <type>_bz_ArrayExpr&lt; ArrayIndexMapping&lt; FastArrayIterator&lt; T_numtype, N_rank &gt;, N0, N1, N2, N3, N4, N5, N6, N7 &gt; &gt;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>2f3364287b0f3bfb7a43f366e7b3ef27</anchor>
      <arglist>(IndexPlaceholder&lt; N0 &gt;, IndexPlaceholder&lt; N1 &gt;, IndexPlaceholder&lt; N2 &gt;, IndexPlaceholder&lt; N3 &gt;, IndexPlaceholder&lt; N4 &gt;, IndexPlaceholder&lt; N5 &gt;, IndexPlaceholder&lt; N6 &gt;, IndexPlaceholder&lt; N7 &gt;) const </arglist>
    </member>
    <member kind="function">
      <type>_bz_ArrayExpr&lt; ArrayIndexMapping&lt; FastArrayIterator&lt; T_numtype, N_rank &gt;, N0, N1, N2, N3, N4, N5, N6, N7, N8 &gt; &gt;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>1adea3afbb622d378b7ec27b995e9673</anchor>
      <arglist>(IndexPlaceholder&lt; N0 &gt;, IndexPlaceholder&lt; N1 &gt;, IndexPlaceholder&lt; N2 &gt;, IndexPlaceholder&lt; N3 &gt;, IndexPlaceholder&lt; N4 &gt;, IndexPlaceholder&lt; N5 &gt;, IndexPlaceholder&lt; N6 &gt;, IndexPlaceholder&lt; N7 &gt;, IndexPlaceholder&lt; N8 &gt;) const </arglist>
    </member>
    <member kind="function">
      <type>_bz_ArrayExpr&lt; ArrayIndexMapping&lt; FastArrayIterator&lt; T_numtype, N_rank &gt;, N0, N1, N2, N3, N4, N5, N6, N7, N8, N9 &gt; &gt;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>49f4ba55c18e243a2cf6ccd251aa24db</anchor>
      <arglist>(IndexPlaceholder&lt; N0 &gt;, IndexPlaceholder&lt; N1 &gt;, IndexPlaceholder&lt; N2 &gt;, IndexPlaceholder&lt; N3 &gt;, IndexPlaceholder&lt; N4 &gt;, IndexPlaceholder&lt; N5 &gt;, IndexPlaceholder&lt; N6 &gt;, IndexPlaceholder&lt; N7 &gt;, IndexPlaceholder&lt; N8 &gt;, IndexPlaceholder&lt; N9 &gt;) const </arglist>
    </member>
    <member kind="function">
      <type>_bz_ArrayExpr&lt; ArrayIndexMapping&lt; FastArrayIterator&lt; T_numtype, N_rank &gt;, N0, N1, N2, N3, N4, N5, N6, N7, N8, N9, N10 &gt; &gt;</type>
      <name>operator()</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>8aa404ab779209180afddac9f12bb987</anchor>
      <arglist>(IndexPlaceholder&lt; N0 &gt;, IndexPlaceholder&lt; N1 &gt;, IndexPlaceholder&lt; N2 &gt;, IndexPlaceholder&lt; N3 &gt;, IndexPlaceholder&lt; N4 &gt;, IndexPlaceholder&lt; N5 &gt;, IndexPlaceholder&lt; N6 &gt;, IndexPlaceholder&lt; N7 &gt;, IndexPlaceholder&lt; N8 &gt;, IndexPlaceholder&lt; N9 &gt;, IndexPlaceholder&lt; N10 &gt;) const </arglist>
    </member>
    <member kind="function">
      <type>Array&lt; typename multicomponent_traits&lt; T_numtype &gt;::T_element, N_rank &gt;</type>
      <name>operator[]</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>2037930103cd6058ad58126616ea90b2</anchor>
      <arglist>(const unsigned component)</arglist>
    </member>
    <member kind="function">
      <type>const Array&lt; typename multicomponent_traits&lt; T_numtype &gt;::T_element, N_rank &gt;</type>
      <name>operator[]</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>bddb0f84b164572b832a72fefcb7c6a3</anchor>
      <arglist>(const unsigned component) const </arglist>
    </member>
    <member kind="function">
      <type>Array&lt; typename multicomponent_traits&lt; T_numtype &gt;::T_element, N_rank &gt;</type>
      <name>operator[]</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>cca3c1802edac60f8482419c9902d28f</anchor>
      <arglist>(const int component)</arglist>
    </member>
    <member kind="function">
      <type>const Array&lt; typename multicomponent_traits&lt; T_numtype &gt;::T_element, N_rank &gt;</type>
      <name>operator[]</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>6deb6b01a7a7ac0ef1b5d4f63368354b</anchor>
      <arglist>(const int component) const </arglist>
    </member>
    <member kind="function">
      <type>IndirectArray&lt; T_array, T_indexContainer &gt;</type>
      <name>operator[]</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>4270e4bf9821b745854135ffceb52f67</anchor>
      <arglist>(const T_indexContainer &amp;index)</arglist>
    </member>
    <member kind="function">
      <type>ListInitializationSwitch&lt; T_array, T_numtype * &gt;</type>
      <name>operator=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>e856960044c0f8c560afbb03c9f9dbb8</anchor>
      <arglist>(T_numtype x)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>initialize</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>8e47cd8025d4c786261ebdd1fbf1cbfc</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator+=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>00799037915e296832a77b072a208171</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator-=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>a672a19bc54a543a6cb39e7ceba3eebf</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator*=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>09c01749f6c3f75bcd3ed719ec9bf086</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator/=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c805e73594629c07d43aeb3d9b7b191c</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator%=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>6446eb1e4ac1535bf690110203152973</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator^=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>573a460e0bb126daa063e9405199c8ed</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>0e0bfa81d3de222b137e661e68035fb5</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator|=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>1ddbfed762ffd92aae5165e444e8e8ff</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>eaafaf4353064f64ac7bb49f9be47ea6</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>6c19eff025df4814a201ffe003d49d15</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b18bef70d48420af406c485fdd9eecd9</anchor>
      <arglist>(const Array&lt; T_numtype, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>faa4b7d4807cc14edc58162863dc9d4f</anchor>
      <arglist>(const Array&lt; P_numtype2, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator+=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>85719c8d15b0f17fa4f2845c0cbf830c</anchor>
      <arglist>(const Array&lt; P_numtype2, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator-=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>cd3858593eb8739cdb9926fcd03dff17</anchor>
      <arglist>(const Array&lt; P_numtype2, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator*=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>8e0e5f8e112d15225d7aaf796be62c1c</anchor>
      <arglist>(const Array&lt; P_numtype2, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator/=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>35c9dc42f5dfcd8484d1d7d97eb9f1c1</anchor>
      <arglist>(const Array&lt; P_numtype2, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator%=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>747e81ca0759a133a6aa2c3cea32ca10</anchor>
      <arglist>(const Array&lt; P_numtype2, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator^=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>e0c24833041bcb05c301c6d58bad492b</anchor>
      <arglist>(const Array&lt; P_numtype2, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>44ba96faaafb28b2dacb3e0b7a62697a</anchor>
      <arglist>(const Array&lt; P_numtype2, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator|=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b7d322c036b9869f73c430dfa0add1d1</anchor>
      <arglist>(const Array&lt; P_numtype2, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>4984ac890d1d7f0fd4db7b4c44b97a5f</anchor>
      <arglist>(const Array&lt; P_numtype2, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>26cb886eab3586b1077dbe97f4ee53f4</anchor>
      <arglist>(const Array&lt; P_numtype2, N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>200f3e93f5b601abd7f616c0f0783465</anchor>
      <arglist>(BZ_ETPARM(_bz_ArrayExpr&lt; T_expr &gt;) expr)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator+=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>4cb5dac646813740da718b2cb0bc4478</anchor>
      <arglist>(BZ_ETPARM(_bz_ArrayExpr&lt; T_expr &gt;) expr)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator-=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c14b77f9b40c8ffef5b0f2c706fc8130</anchor>
      <arglist>(BZ_ETPARM(_bz_ArrayExpr&lt; T_expr &gt;) expr)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator*=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>a8abf22e55cc59d17ddf587ce83b19d9</anchor>
      <arglist>(BZ_ETPARM(_bz_ArrayExpr&lt; T_expr &gt;) expr)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator/=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>7b1c0d168f8e0eba64f806561bf6b0b4</anchor>
      <arglist>(BZ_ETPARM(_bz_ArrayExpr&lt; T_expr &gt;) expr)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator%=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>a71f5283b2c9c3cd97ce7d0c8f4f679e</anchor>
      <arglist>(BZ_ETPARM(_bz_ArrayExpr&lt; T_expr &gt;) expr)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator^=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b48a713da2b4b455e8717404b155deac</anchor>
      <arglist>(BZ_ETPARM(_bz_ArrayExpr&lt; T_expr &gt;) expr)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b5bf5aa76804a02302ad8315fe9233fb</anchor>
      <arglist>(BZ_ETPARM(_bz_ArrayExpr&lt; T_expr &gt;) expr)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator|=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f3fdf4e1710a470f09650b05e2bbd61c</anchor>
      <arglist>(BZ_ETPARM(_bz_ArrayExpr&lt; T_expr &gt;) expr)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>189edb878e2ef179345587d20354518f</anchor>
      <arglist>(BZ_ETPARM(_bz_ArrayExpr&lt; T_expr &gt;) expr)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>1fbb424296b0affead9f414eee602392</anchor>
      <arglist>(BZ_ETPARM(_bz_ArrayExpr&lt; T_expr &gt;) expr)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>evaluate</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>6eff186e59044a196dfaa5bd04b45550</anchor>
      <arglist>(T_expr expr, T_update)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>evaluateWithIndexTraversal1</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>73675a3a77b3fdab10a03bc0349663dd</anchor>
      <arglist>(T_expr expr, T_update)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>evaluateWithIndexTraversalN</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>dac362156c476b4607d6f2a6ddc6b455</anchor>
      <arglist>(T_expr expr, T_update)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>evaluateWithStackTraversal1</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>72f15360585559fd21ef0eb25798100d</anchor>
      <arglist>(T_expr expr, T_update)</arglist>
    </member>
    <member kind="function">
      <type>T_array &amp;</type>
      <name>evaluateWithStackTraversalN</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>82c7326a38f2b32c13f41890340af6b5</anchor>
      <arglist>(T_expr expr, T_update)</arglist>
    </member>
    <member kind="function">
      <type>T_numtype *restrict</type>
      <name>getInitializationIterator</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>dcddc81286aed87edf23b9bc569206c6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>canCollapse</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>c63d4b673342ba9e1b84eefccd6a92c7</anchor>
      <arglist>(int outerRank, int innerRank) const </arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_rank</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>0740c98d4e4ef7fb30e689b477c96ca0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>_bz_inline2 void</type>
      <name>computeStrides</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>bc8b772aea64da89e92f029d64403ac5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>_bz_inline2 void</type>
      <name>setupStorage</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>22b37cc98defdc9d72f390931512697c</anchor>
      <arglist>(int rank)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>constructSubarray</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b73a1e3fdddbb0c207cddf7f575f26dd</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, const RectDomain&lt; N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>constructSubarray</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f9cf267d3c93ac2dcd87029853cc9db8</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, const StridedDomain&lt; N_rank &gt; &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>constructSubarray</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>e89f82742aaaa0a97edfc66a34e57b32</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>constructSubarray</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>7baac1b30a7c8053d81782bef87199b3</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>constructSubarray</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>45ea008468c47ffd002623231aba8674</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>constructSubarray</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>ecf4323d2b0d3bd71daacf5304e3790f</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>constructSubarray</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>a889103322562994952493f34ebc9b06</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3, Range r4)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>constructSubarray</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>807246ff4783222419092567bd7d4e2c</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>constructSubarray</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>6e93846ab0e27f92fa469e4831a74636</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>constructSubarray</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f92fd8dba539c2fa6162b75a76bc8eed</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>constructSubarray</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>8bb2c309e6fda218580c38765c1ee8e2</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>constructSubarray</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>74ce196e56d8bd6c59621c19aebc1387</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8, Range r9)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>constructSubarray</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>61e8715866c5b2de855f54793cd7b59b</anchor>
      <arglist>(Array&lt; T_numtype, N_rank &gt; &amp;array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7, Range r8, Range r9, Range r10)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>calculateZeroOffset</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>34294eb964088dd307f1f82a3d5b493c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>constructSlice</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>2811bb945959151c80efde830da496b1</anchor>
      <arglist>(Array&lt; T_numtype, N_rank2 &gt; &amp;array, R0 r0, R1 r1, R2 r2, R3 r3, R4 r4, R5 r5, R6 r6, R7 r7, R8 r8, R9 r9, R10 r10)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>slice</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>10925d27b137e19462e3654d27741cfb</anchor>
      <arglist>(int &amp;setRank, Range r, Array&lt; T_numtype, N_rank2 &gt; &amp;array, TinyVector&lt; int, N_rank2 &gt; &amp;rankMap, int sourceRank)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>slice</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>52e54288f84fee6682984a536c5dfac8</anchor>
      <arglist>(int &amp;setRank, int i, Array&lt; T_numtype, N_rank2 &gt; &amp;array, TinyVector&lt; int, N_rank2 &gt; &amp;rankMap, int sourceRank)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>slice</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b4119de9246da72e15da8886578548a9</anchor>
      <arglist>(int &amp;, nilArraySection, Array&lt; T_numtype, N_rank2 &gt; &amp;, TinyVector&lt; int, N_rank2 &gt; &amp;, int)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>doTranspose</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>5903cff358e066b56a0ddf49adf534e1</anchor>
      <arglist>(int destRank, int sourceRank, T_array &amp;array)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>GeneralArrayStorage&lt; N_rank &gt;</type>
      <name>storage_</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>b59a3d60aed828794ddff5988923ad95</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>TinyVector&lt; int, N_rank &gt;</type>
      <name>length_</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>0cbba3282171c170fd046207fbcc7d14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>TinyVector&lt; diffType, N_rank &gt;</type>
      <name>stride_</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>6defcf382ad5aac0cfb3205e54fd3d69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>diffType</type>
      <name>zeroOffset_</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>d25a756cc1ee25dc4ee04dfe54ea5158</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>MemoryBlockReference&lt; P_numtype &gt;</type>
      <name>T_base</name>
      <anchorfile>classArray.html</anchorfile>
      <anchor>f79a4b00245c7115042c15fec3478e5b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AsymmetricMatrix</name>
    <filename>classAsymmetricMatrix.html</filename>
    <base>MatrixStructure</base>
    <member kind="function">
      <type></type>
      <name>AsymmetricMatrix</name>
      <anchorfile>classAsymmetricMatrix.html</anchorfile>
      <anchor>d9b329cf540fe9b92931a4df12097169</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AsymmetricMatrix</name>
      <anchorfile>classAsymmetricMatrix.html</anchorfile>
      <anchor>bac34ac1f4ae84f4823719e096676e2e</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>columns</name>
      <anchorfile>classAsymmetricMatrix.html</anchorfile>
      <anchor>9029ba3ac3d153656937b5028eb20b4f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>cols</name>
      <anchorfile>classAsymmetricMatrix.html</anchorfile>
      <anchor>5ef0ec381e4d33a1f19be7c3e26410d4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>inRange</name>
      <anchorfile>classAsymmetricMatrix.html</anchorfile>
      <anchor>2454085bcbf885b2f8cd94a9ed70de65</anchor>
      <arglist>(const unsigned i, const unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classAsymmetricMatrix.html</anchorfile>
      <anchor>586bdfd0f1cc7bb0163a562e8f1b6980</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>rows</name>
      <anchorfile>classAsymmetricMatrix.html</anchorfile>
      <anchor>df8ff298b6b24882a147fdcedebe1bbd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>rows_</name>
      <anchorfile>classAsymmetricMatrix.html</anchorfile>
      <anchor>2efe32fe670be113c88a87830c81fe84</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>cols_</name>
      <anchorfile>classAsymmetricMatrix.html</anchorfile>
      <anchor>ce6521deef8ae75af32b8407778a98a9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Beta</name>
    <filename>classBeta.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <base>UniformOpen&lt; T, IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>T</type>
      <name>T_numtype</name>
      <anchorfile>classBeta.html</anchorfile>
      <anchor>21852ff4934eaf5fd4af493a1196c414</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Beta</name>
      <anchorfile>classBeta.html</anchorfile>
      <anchor>2e76abf59c56ab61cb1e0f74ed35cd52</anchor>
      <arglist>(T a, T b)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Beta</name>
      <anchorfile>classBeta.html</anchorfile>
      <anchor>debe5f9e5fe34b9a253e7e7033b88960</anchor>
      <arglist>(T a, T b, unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>random</name>
      <anchorfile>classBeta.html</anchorfile>
      <anchor>d63448f9fec46b8256cc0132aec0848d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameters</name>
      <anchorfile>classBeta.html</anchorfile>
      <anchor>802704d5655d6acd41e94defd150e6f7</anchor>
      <arglist>(T a, T b)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>T</type>
      <name>ranf</name>
      <anchorfile>classBeta.html</anchorfile>
      <anchor>763f9ba62fa309f0265f58fe51d012d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T</type>
      <name>aa</name>
      <anchorfile>classBeta.html</anchorfile>
      <anchor>1fdacfee6935aa760834939aeed671c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T</type>
      <name>bb</name>
      <anchorfile>classBeta.html</anchorfile>
      <anchor>07a4ea0f15e68b58e28eb7c196704c11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T</type>
      <name>infnty</name>
      <anchorfile>classBeta.html</anchorfile>
      <anchor>33511eec58d4ef47b67f85608841b04b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T</type>
      <name>minlog</name>
      <anchorfile>classBeta.html</anchorfile>
      <anchor>69846792971a374e4549c3cf0702b69c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T</type>
      <name>expmax</name>
      <anchorfile>classBeta.html</anchorfile>
      <anchor>aa8721e851d87446912071b4f049c0ff</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>BitwiseAnd</name>
    <filename>structBitwiseAnd.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type>typedef</type>
      <name>BZ_PROMOTE</name>
      <anchorfile>structBitwiseAnd.html</anchorfile>
      <anchor>b70cd3632e0014f01f5cfbe2b0ad3d94</anchor>
      <arglist>(T_numtype1, T_numtype2) T_numtype</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structBitwiseAnd.html</anchorfile>
      <anchor>3c1848fd6f39294b48c99a5e1bd740eb</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structBitwiseAnd.html</anchorfile>
      <anchor>30e02cab900d8bed6004b9802e8d411b</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>BitwiseNot</name>
    <filename>structBitwiseNot.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>T_numtype1</type>
      <name>T_numtype</name>
      <anchorfile>structBitwiseNot.html</anchorfile>
      <anchor>e9d6d12a7c81e1e2f8f4a32dfd72e2e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structBitwiseNot.html</anchorfile>
      <anchor>f3f11bf136e23a944e50a261fbe7429b</anchor>
      <arglist>(T_numtype1 a)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structBitwiseNot.html</anchorfile>
      <anchor>cc80c009ee669f8fb3a44699c381f3d6</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>BitwiseOr</name>
    <filename>structBitwiseOr.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type>typedef</type>
      <name>BZ_PROMOTE</name>
      <anchorfile>structBitwiseOr.html</anchorfile>
      <anchor>44a174627e160486f4794962781cdf04</anchor>
      <arglist>(T_numtype1, T_numtype2) T_numtype</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structBitwiseOr.html</anchorfile>
      <anchor>ed2c366a0432dc4cc3e333e57da3dace</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structBitwiseOr.html</anchorfile>
      <anchor>16a0b41812a1b86da4ee42a39b88aeac</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>BitwiseXor</name>
    <filename>structBitwiseXor.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type>typedef</type>
      <name>BZ_PROMOTE</name>
      <anchorfile>structBitwiseXor.html</anchorfile>
      <anchor>fa57ffa6207faf0894190ce3e83f4e78</anchor>
      <arglist>(T_numtype1, T_numtype2) T_numtype</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structBitwiseXor.html</anchorfile>
      <anchor>947e32b3c5aa8fcd4476d5af7f38f375</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structBitwiseXor.html</anchorfile>
      <anchor>4f5c597b3170ced83aaa88866debedc2</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ChiSquare</name>
    <filename>classChiSquare.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <base>Gamma&lt; T, IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>T</type>
      <name>T_numtype</name>
      <anchorfile>classChiSquare.html</anchorfile>
      <anchor>d878a5ac54f977aba44afd0af4bef754</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ChiSquare</name>
      <anchorfile>classChiSquare.html</anchorfile>
      <anchor>112b66a1e1229c14e078277d69aba90b</anchor>
      <arglist>(T df)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ChiSquare</name>
      <anchorfile>classChiSquare.html</anchorfile>
      <anchor>7edf4f430441995c26046a3579c574c5</anchor>
      <arglist>(T df, unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDF</name>
      <anchorfile>classChiSquare.html</anchorfile>
      <anchor>43992382928a471e6bbbf29e6a4c279d</anchor>
      <arglist>(T _df)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>random</name>
      <anchorfile>classChiSquare.html</anchorfile>
      <anchor>f9d327a7a58cecf32b55312f71371b58</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>T</type>
      <name>sgamma</name>
      <anchorfile>classChiSquare.html</anchorfile>
      <anchor>70a257ca139e902d5252b119e686f339</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T</type>
      <name>df</name>
      <anchorfile>classChiSquare.html</anchorfile>
      <anchor>f2700649cade5394fb1a881bc09020d4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ColumnMajor</name>
    <filename>classColumnMajor.html</filename>
    <base>GeneralMatrix</base>
    <member kind="function">
      <type></type>
      <name>ColumnMajor</name>
      <anchorfile>classColumnMajor.html</anchorfile>
      <anchor>240089521d22727e96c150e8342ef8fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ColumnMajor</name>
      <anchorfile>classColumnMajor.html</anchorfile>
      <anchor>6438127d17cb19d17fab881d4d691057</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>coordToOffset</name>
      <anchorfile>classColumnMajor.html</anchorfile>
      <anchor>d0215be1e1af3ec4df605bb2b43fe2c6</anchor>
      <arglist>(unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>get</name>
      <anchorfile>classColumnMajor.html</anchorfile>
      <anchor>f089a0da37f60269069330574f9d9d44</anchor>
      <arglist>(const T_numtype *restrict data, unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>get</name>
      <anchorfile>classColumnMajor.html</anchorfile>
      <anchor>9c41be1354b0b992b7b4e0934574c834</anchor>
      <arglist>(T_numtype *restrict data, unsigned i, unsigned j)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ColumnMajorIterator</name>
    <filename>classColumnMajorIterator.html</filename>
    <base>GeneralIterator</base>
    <member kind="function">
      <type></type>
      <name>ColumnMajorIterator</name>
      <anchorfile>classColumnMajorIterator.html</anchorfile>
      <anchor>71f32961444246869896b677976c44d6</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator++</name>
      <anchorfile>classColumnMajorIterator.html</anchorfile>
      <anchor>36c620fe894a16e3c1755a087c196001</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Diagonal</name>
    <filename>classDiagonal.html</filename>
    <base>MatrixStructure</base>
    <member kind="typedef">
      <type>DiagonalIterator</type>
      <name>T_iterator</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>10d1f6944fa52a0d07a64e82791e35ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Diagonal</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>8a0fb301083ec1d68055d4ac8a460fc9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Diagonal</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>45f298ba957ce87634f97c7ec94d68ad</anchor>
      <arglist>(const unsigned size)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Diagonal</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>c05224b31c6dca9f9ed551688d5af701</anchor>
      <arglist>(const unsigned rows, const unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>columns</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>e18024d3b2f21ea9e9967ae248bbbdfd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>coordToOffset</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>6702c9928dd0e42c8e699ee4be2ca071</anchor>
      <arglist>(const unsigned i, const unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>firstInRow</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>a48d87386fe718e3fa048ef3c1e253f2</anchor>
      <arglist>(const unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>get</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>8a6b0c39dbca05941079156fb8bb9cc2</anchor>
      <arglist>(const T_numtype *restrict data, const unsigned i, const unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>get</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>aba02a101a3297274bba71f74a51a784</anchor>
      <arglist>(T_numtype *restrict data, const unsigned i, const unsigned j)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>lastInRow</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>805cd3fa72e4b19e77cd567b463c5cd5</anchor>
      <arglist>(const unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>firstInCol</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>38e9c0120b9f55172d8e087309466591</anchor>
      <arglist>(const unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>lastInCol</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>a990aa51399f7477b34f0e6108e2a67e</anchor>
      <arglist>(const unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>inRange</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>d5d65cfb23b1d45b7d5d376e00e4cace</anchor>
      <arglist>(const unsigned i, const unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>numElements</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>dedf6df0a7088a26654f5a03da8ae575</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>rows</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>be0c77c7f3563dc0d27fc051f046b083</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>9a88629dea80fe9c6694a0ee08fbddbc</anchor>
      <arglist>(const unsigned size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>86332b5c95895a0bc57b58f5d8952a70</anchor>
      <arglist>(const unsigned rows, const unsigned cols)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned</type>
      <name>size_</name>
      <anchorfile>classDiagonal.html</anchorfile>
      <anchor>cbc6f9a08e9301ba1e416bb971daee8c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>DiagonalIterator</name>
    <filename>classDiagonalIterator.html</filename>
    <member kind="function">
      <type></type>
      <name>DiagonalIterator</name>
      <anchorfile>classDiagonalIterator.html</anchorfile>
      <anchor>b597a6143fdf97c0409da8fbe34ab14a</anchor>
      <arglist>(const unsigned rows, const unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>classDiagonalIterator.html</anchorfile>
      <anchor>827ab8b36dd2b90282cdae120022f5e0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator++</name>
      <anchorfile>classDiagonalIterator.html</anchorfile>
      <anchor>aa9b8a1c7f7928ae024990055b89855e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>row</name>
      <anchorfile>classDiagonalIterator.html</anchorfile>
      <anchor>75e19c42b907b3159663fadfe65fc35c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>col</name>
      <anchorfile>classDiagonalIterator.html</anchorfile>
      <anchor>47ff15c663b1e0c1d32e1752b34e8dcc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>offset</name>
      <anchorfile>classDiagonalIterator.html</anchorfile>
      <anchor>1da06d3ae5a2d68879f0f265a90996a3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>i_</name>
      <anchorfile>classDiagonalIterator.html</anchorfile>
      <anchor>2ba8f4c0ec1c388e9071044fcd37c3a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>size_</name>
      <anchorfile>classDiagonalIterator.html</anchorfile>
      <anchor>449e656511e2d61e50d878debe597300</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>DiscreteUniform</name>
    <filename>classDiscreteUniform.html</filename>
    <templarg>BZ_TEMPLATE_DEFAULT</templarg>
    <base>IRNGWrapper&lt; IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>int</type>
      <name>T_numtype</name>
      <anchorfile>classDiscreteUniform.html</anchorfile>
      <anchor>affd818479c69c4d6f9fa047b85481a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>P_uniform</type>
      <name>T_uniform</name>
      <anchorfile>classDiscreteUniform.html</anchorfile>
      <anchor>a08e367089d386765d4958f2bef525da</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T</type>
      <name>T_numtype</name>
      <anchorfile>classDiscreteUniform.html</anchorfile>
      <anchor>6f47a7966dca0981342dc45ebadc8852</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DiscreteUniform</name>
      <anchorfile>classDiscreteUniform.html</anchorfile>
      <anchor>377aa895f26a4b83f0bac748832dbb04</anchor>
      <arglist>(int low, int high, double=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>randomize</name>
      <anchorfile>classDiscreteUniform.html</anchorfile>
      <anchor>8f4446c966170fc7b188b9180ab3841d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>random</name>
      <anchorfile>classDiscreteUniform.html</anchorfile>
      <anchor>604881ece5d5d6f2a741866ede60c71b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DiscreteUniform</name>
      <anchorfile>classDiscreteUniform.html</anchorfile>
      <anchor>58e9e61f85c9ad88e21943abe12b936b</anchor>
      <arglist>(T n)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DiscreteUniform</name>
      <anchorfile>classDiscreteUniform.html</anchorfile>
      <anchor>3e2e09a6ac6148e033386447c99a757f</anchor>
      <arglist>(T n, unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>random</name>
      <anchorfile>classDiscreteUniform.html</anchorfile>
      <anchor>b1d242643d5a4efd0adf2a09f4592124</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>low_</name>
      <anchorfile>classDiscreteUniform.html</anchorfile>
      <anchor>cd5ff4e49e2290bb3a875806ac2f216f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>range_</name>
      <anchorfile>classDiscreteUniform.html</anchorfile>
      <anchor>61229fc64d034c0f57f105c922508854</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T_uniform</type>
      <name>uniform_</name>
      <anchorfile>classDiscreteUniform.html</anchorfile>
      <anchor>73d9bc05dc22d23932de94b2dd70d411</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T</type>
      <name>n_</name>
      <anchorfile>classDiscreteUniform.html</anchorfile>
      <anchor>44a0e2013644d1fa6a255e73b5a01f0d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Divide</name>
    <filename>structDivide.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type>typedef</type>
      <name>BZ_PROMOTE</name>
      <anchorfile>structDivide.html</anchorfile>
      <anchor>8c33b2e7bbe766402dee5321fae04fc0</anchor>
      <arglist>(T_numtype1, T_numtype2) T_numtype</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structDivide.html</anchorfile>
      <anchor>4fd6abdfad0a844e426fa806a5b5a865</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structDivide.html</anchorfile>
      <anchor>5bbeac20d8e9e7e8523cce68d9823dfd</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Equal</name>
    <filename>structEqual.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>bool</type>
      <name>T_numtype</name>
      <anchorfile>structEqual.html</anchorfile>
      <anchor>6f28db8aaf38e225887e6a6259563cc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structEqual.html</anchorfile>
      <anchor>80393ec7020fef8de3d4da91f79a2f7d</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structEqual.html</anchorfile>
      <anchor>3932a218d7a3d5c5791dd33cc3a5d64b</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ETBase</name>
    <filename>classETBase.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>ETBase</name>
      <anchorfile>classETBase.html</anchorfile>
      <anchor>0493e8b2a75761c3688f3ea40702e095</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ETBase</name>
      <anchorfile>classETBase.html</anchorfile>
      <anchor>ee4aeb4ee5e5c74e102463904049808a</anchor>
      <arglist>(const ETBase&lt; T &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>unwrap</name>
      <anchorfile>classETBase.html</anchorfile>
      <anchor>686c9a0a29d913b6dd93f8c7625b3a58</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>unwrap</name>
      <anchorfile>classETBase.html</anchorfile>
      <anchor>6e806c92d9bff298853eec1f37692770</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ETBase&lt; T &gt; &amp;</type>
      <name>wrap</name>
      <anchorfile>classETBase.html</anchorfile>
      <anchor>3cc9ea169377f60fd883d427c18bd048</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const ETBase&lt; T &gt; &amp;</type>
      <name>wrap</name>
      <anchorfile>classETBase.html</anchorfile>
      <anchor>2bc825dcfcafc41d9f7e75e0353cde6e</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Exponential</name>
    <filename>classExponential.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <base>ExponentialUnit&lt; T, IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>T</type>
      <name>T_numtype</name>
      <anchorfile>classExponential.html</anchorfile>
      <anchor>3d9baf59336d016f1692fc47641db150</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Exponential</name>
      <anchorfile>classExponential.html</anchorfile>
      <anchor>041eca09b09863c253c6ed85706e228e</anchor>
      <arglist>(T mean)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Exponential</name>
      <anchorfile>classExponential.html</anchorfile>
      <anchor>eae599d482c7695c911d45b5622933e8</anchor>
      <arglist>(T mean, unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>random</name>
      <anchorfile>classExponential.html</anchorfile>
      <anchor>2c9f498208e5954c13ed1d9c199b177b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T</type>
      <name>mean_</name>
      <anchorfile>classExponential.html</anchorfile>
      <anchor>60af8a456dd84b17177fc90202900908</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ExponentialUnit</name>
    <filename>classExponentialUnit.html</filename>
    <templarg>T</templarg>
    <templarg>IRNG</templarg>
    <templarg>stateTag</templarg>
    <base>UniformOpen&lt; T, IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>T</type>
      <name>T_numtype</name>
      <anchorfile>classExponentialUnit.html</anchorfile>
      <anchor>05c0b4ee47416135f494ab520034630a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ExponentialUnit</name>
      <anchorfile>classExponentialUnit.html</anchorfile>
      <anchor>d4a5955828ac266c588fcca44aff4d8e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ExponentialUnit</name>
      <anchorfile>classExponentialUnit.html</anchorfile>
      <anchor>de7df24761c8e56b49e70c6d28ba5e77</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>random</name>
      <anchorfile>classExponentialUnit.html</anchorfile>
      <anchor>5b578440c154674de23f979d4ffc287c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Extremum</name>
    <filename>classExtremum.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classExtremum.html</anchorfile>
      <anchor>305d678d8ea32a4b05f0dcb1c078b0c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>P_index</type>
      <name>T_index</name>
      <anchorfile>classExtremum.html</anchorfile>
      <anchor>bede57c47b4f9968a97bd2758b76589c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Extremum</name>
      <anchorfile>classExtremum.html</anchorfile>
      <anchor>1c4eaf1dba59d473645b87e9d7f4dff6</anchor>
      <arglist>(T_numtype value, T_index index)</arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>value</name>
      <anchorfile>classExtremum.html</anchorfile>
      <anchor>818cacef365e83becac1c5a5ebca7c52</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_index</type>
      <name>index</name>
      <anchorfile>classExtremum.html</anchorfile>
      <anchor>ef44a765a875c5c506c3a09517558e7f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValue</name>
      <anchorfile>classExtremum.html</anchorfile>
      <anchor>bd03c71351bb402a8aab40fabd3df557</anchor>
      <arglist>(T_numtype value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setIndex</name>
      <anchorfile>classExtremum.html</anchorfile>
      <anchor>7b6e93d10f67167700ab761477975fc2</anchor>
      <arglist>(T_index index)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator T_numtype</name>
      <anchorfile>classExtremum.html</anchorfile>
      <anchor>e40d7535e663177f301f5cdaaf0b9d15</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_numtype</type>
      <name>value_</name>
      <anchorfile>classExtremum.html</anchorfile>
      <anchor>85c3dcbf818d0ac6d587907fa250c84e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_index</type>
      <name>index_</name>
      <anchorfile>classExtremum.html</anchorfile>
      <anchor>d8c76332d27149d8550b463d710c55a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>F</name>
    <filename>classF.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>T</type>
      <name>T_numtype</name>
      <anchorfile>classF.html</anchorfile>
      <anchor>a624f906764e18eac83e9a183e208473</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>F</name>
      <anchorfile>classF.html</anchorfile>
      <anchor>9d058af4ef43ec8218c58ae654832718</anchor>
      <arglist>(T numeratorDF, T denominatorDF)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>F</name>
      <anchorfile>classF.html</anchorfile>
      <anchor>fcad662a0f2a0be74292c25340ec747e</anchor>
      <arglist>(T numeratorDF, T denominatorDF, unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDF</name>
      <anchorfile>classF.html</anchorfile>
      <anchor>710f67a6d97ead60d4c9517706fe9981</anchor>
      <arglist>(T _dfn, T _dfd)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>random</name>
      <anchorfile>classF.html</anchorfile>
      <anchor>782dbe24dbb05ed2a91c26d72a8ba1e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>seed</name>
      <anchorfile>classF.html</anchorfile>
      <anchor>3990de55f3782453136def9838796358</anchor>
      <arglist>(IRNG_int s, IRNG_int r)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Gamma&lt; T, IRNG, stateTag &gt;</type>
      <name>ngamma</name>
      <anchorfile>classF.html</anchorfile>
      <anchor>8a172b77fd08bc7ebdf930fb291d66bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Gamma&lt; T, IRNG, stateTag &gt;</type>
      <name>dgamma</name>
      <anchorfile>classF.html</anchorfile>
      <anchor>5656c6e9c4f86ce9682bc1209730e21c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T</type>
      <name>dfn</name>
      <anchorfile>classF.html</anchorfile>
      <anchor>8a963b0e765e5d03eee78a209d0e77cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T</type>
      <name>dfd</name>
      <anchorfile>classF.html</anchorfile>
      <anchor>d2cb7df2be988dec2f2dcf7218839a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T</type>
      <name>mindenom</name>
      <anchorfile>classF.html</anchorfile>
      <anchor>b683a75aff989ffc0b24c8e2db557ff6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Gamma</name>
    <filename>classGamma.html</filename>
    <templarg>T</templarg>
    <templarg>IRNG</templarg>
    <templarg>stateTag</templarg>
    <base>UniformOpen&lt; T, IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>T</type>
      <name>T_numtype</name>
      <anchorfile>classGamma.html</anchorfile>
      <anchor>c7dfd13654199207851b10676b7eeacc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Gamma</name>
      <anchorfile>classGamma.html</anchorfile>
      <anchor>e0393749ce17a19851638c8b7f1a29b5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Gamma</name>
      <anchorfile>classGamma.html</anchorfile>
      <anchor>82bfbe1dcd149148d47261b309adf3a8</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Gamma</name>
      <anchorfile>classGamma.html</anchorfile>
      <anchor>53529aabd1efd48446f4f417ec81fdda</anchor>
      <arglist>(T mean)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Gamma</name>
      <anchorfile>classGamma.html</anchorfile>
      <anchor>2a10f2172505d797cad84a9236fa376d</anchor>
      <arglist>(T mean, unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>random</name>
      <anchorfile>classGamma.html</anchorfile>
      <anchor>a8f5a04a7babd42e044d099e6236d60f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMean</name>
      <anchorfile>classGamma.html</anchorfile>
      <anchor>443a41a5c488f8907a5e9e6c47f738db</anchor>
      <arglist>(T mean)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>T</type>
      <name>ranf</name>
      <anchorfile>classGamma.html</anchorfile>
      <anchor>f7593e218e21b0285b330e2632bc17d3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>T</type>
      <name>snorm</name>
      <anchorfile>classGamma.html</anchorfile>
      <anchor>5a26eb2fc35b3f2ce0206f695ced86e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>T</type>
      <name>sexpo</name>
      <anchorfile>classGamma.html</anchorfile>
      <anchor>5e99392e8752c4f606e96e790f37dd56</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>T</type>
      <name>fsign</name>
      <anchorfile>classGamma.html</anchorfile>
      <anchor>b7bda97209ac6d4f12585fcb59865ae1</anchor>
      <arglist>(T num, T sign)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>NormalUnit&lt; T, IRNG, sharedState &gt;</type>
      <name>normal_</name>
      <anchorfile>classGamma.html</anchorfile>
      <anchor>5eb62105ec383dd3b431b507be1edef0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ExponentialUnit&lt; T, IRNG, sharedState &gt;</type>
      <name>exponential_</name>
      <anchorfile>classGamma.html</anchorfile>
      <anchor>da4576c9ed9705b16bcf9c961ed16106</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T</type>
      <name>a</name>
      <anchorfile>classGamma.html</anchorfile>
      <anchor>64e5ce77cc2a3f73e61cf840ef49dc36</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GeneralIterator</name>
    <filename>classGeneralIterator.html</filename>
    <member kind="function">
      <type></type>
      <name>GeneralIterator</name>
      <anchorfile>classGeneralIterator.html</anchorfile>
      <anchor>36f0739681a75617dd3c8f2f2b29fdd4</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>offset</name>
      <anchorfile>classGeneralIterator.html</anchorfile>
      <anchor>fa3bb0f974c186c23019fd592ace71c0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>classGeneralIterator.html</anchorfile>
      <anchor>a897fe92c6d06af59b94f3c9ede584ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>row</name>
      <anchorfile>classGeneralIterator.html</anchorfile>
      <anchor>0ae3d244bd98156a25b4455b421b874b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>col</name>
      <anchorfile>classGeneralIterator.html</anchorfile>
      <anchor>a4a2805eca53a965588dc7e8c989f1a0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>rows_</name>
      <anchorfile>classGeneralIterator.html</anchorfile>
      <anchor>37abbe3be14d2039bc533f67b0295c75</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>cols_</name>
      <anchorfile>classGeneralIterator.html</anchorfile>
      <anchor>79b45d7433f1cfefda90d1c076990609</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>offset_</name>
      <anchorfile>classGeneralIterator.html</anchorfile>
      <anchor>77ddc58d7ce3a669e01df2bb8d8b21c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>i_</name>
      <anchorfile>classGeneralIterator.html</anchorfile>
      <anchor>9e22c8f4827e407016ccb40b2103aacf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>j_</name>
      <anchorfile>classGeneralIterator.html</anchorfile>
      <anchor>8ca7c0d4eaa4cee3fcb5aa66b8bbacd8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>good_</name>
      <anchorfile>classGeneralIterator.html</anchorfile>
      <anchor>aa7c84a87f8e944b7de35a80066bf73a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GeneralMatrix</name>
    <filename>classGeneralMatrix.html</filename>
    <base>AsymmetricMatrix</base>
    <member kind="function">
      <type></type>
      <name>GeneralMatrix</name>
      <anchorfile>classGeneralMatrix.html</anchorfile>
      <anchor>005084ee9fe6f9418a635ee0779915b2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GeneralMatrix</name>
      <anchorfile>classGeneralMatrix.html</anchorfile>
      <anchor>cc498f3bcd04c3e1cc7cbb0091632d6e</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>firstInRow</name>
      <anchorfile>classGeneralMatrix.html</anchorfile>
      <anchor>0dbd87a3506465846237160813b9e59f</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>lastInRow</name>
      <anchorfile>classGeneralMatrix.html</anchorfile>
      <anchor>a96b69f603eea32b735091e6d4f69374</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>firstInCol</name>
      <anchorfile>classGeneralMatrix.html</anchorfile>
      <anchor>81da215cc8665147e2be6a1799dcbf29</anchor>
      <arglist>(unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>lastInCol</name>
      <anchorfile>classGeneralMatrix.html</anchorfile>
      <anchor>0796f2a1419a569832e44d126789fc56</anchor>
      <arglist>(unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>numElements</name>
      <anchorfile>classGeneralMatrix.html</anchorfile>
      <anchor>66d62ad381a3fbdb172f7a3cd7accf0f</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Greater</name>
    <filename>structGreater.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>bool</type>
      <name>T_numtype</name>
      <anchorfile>structGreater.html</anchorfile>
      <anchor>ab7e7c934b2c920fc5d1c235f28c3ee7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structGreater.html</anchorfile>
      <anchor>cb90643f4441769b1c49657c99313d1a</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structGreater.html</anchorfile>
      <anchor>92e49c02a940a1fd507433979d254fa5</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>GreaterOrEqual</name>
    <filename>structGreaterOrEqual.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>bool</type>
      <name>T_numtype</name>
      <anchorfile>structGreaterOrEqual.html</anchorfile>
      <anchor>316067366f3e77291c7106d5329277cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structGreaterOrEqual.html</anchorfile>
      <anchor>9c6f752e99c34d56adb8df4ea48d72da</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structGreaterOrEqual.html</anchorfile>
      <anchor>b44ad94167e45d27d21680112ba2f600</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>independentState</name>
    <filename>structindependentState.html</filename>
  </compound>
  <compound kind="class">
    <name>IndexPlaceholder</name>
    <filename>classIndexPlaceholder.html</filename>
    <templarg>N</templarg>
    <class kind="class">IndexPlaceholder::SliceInfo</class>
    <member kind="typedef">
      <type>int</type>
      <name>T_numtype</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>d03df79ee5a3bed19e6a8de0dd67cc16</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>T_ctorArg1</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>6ea3b540cd6570da5b5cd10bb258e8cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>T_ctorArg2</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>3142b177266f6c86d2d229ba69cac2d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>T_range_result</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>16dd2ac62ccc2f98092b0ca4a4186c94</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IndexPlaceholder</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>bb86f5feb838be57b819e7605702fbcc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IndexPlaceholder</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>d400b91c1d9890bc6dda225f463881ae</anchor>
      <arglist>(const IndexPlaceholder&lt; N &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~IndexPlaceholder</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>0469c320881ec280c0bc1f306fba70e5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator=</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>d698d06fd1560d26c3f886a3815e25d7</anchor>
      <arglist>(const IndexPlaceholder&lt; N &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>operator*</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>338b2f651eb07a6c10d6e4a27bc8055b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator()</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>8ede76e7dc660570f4108b66eaf9294b</anchor>
      <arglist>(const TinyVector&lt; int, N_rank &gt; &amp;i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ascending</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>b2a8f50faa136325186a2d2d604268f0</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ordering</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>98a3e547003f55008d9b1274cf40f3c9</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>lbound</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>798ba3dad14615498ca30a0fb3989d97</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ubound</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>c7c6d785b577ffd4054c51065b4d0654</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>RectDomain&lt; rank &gt;</type>
      <name>domain</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>53f37cc97607262a9749190546125b76</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>push</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>ead71a4be0cbb4b3d16e8c6532cafef1</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pop</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>bfa8e6ccfa867f4702899a5facf9a1dc</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>advance</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>489f7339a551d77f59ab7f01fcc95a20</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>advance</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>16850cce106784fb1db38556c67a77be</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>loadStride</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>d1f17f836a3f623628c93ca3eaf8dc4e</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>moveTo</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>ee93364c6e7fd8d36b5ffb9f539c7658</anchor>
      <arglist>(const TinyVector&lt; int, N_rank &gt; &amp;i)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isUnitStride</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>ae5c77dbbee3215e7dedddf9622f177a</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>advanceUnitStride</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>6e7adfa1ba0172b057be6d92a9425540</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>canCollapse</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>bd6aa298ec85691787f14fe764aa88f5</anchor>
      <arglist>(int, int) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator[]</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>820ea3db3fe31b01e741ed9118b0b985</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>fastRead</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>0c182997d7f2fb89aa8b22734c084c2d</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>diffType</type>
      <name>suggestStride</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>e7d42ed3b9612b5ddb77c210b30f1690</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isStride</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>e25aa5d02b2316ac045a89a4ab80a7bd</anchor>
      <arglist>(int, diffType) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>shift</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>be1e6e50c01503f7657818b33f1c013b</anchor>
      <arglist>(int offset, int dim) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>shift</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>9125f194e0fcf305abf274d7a31d96f4</anchor>
      <arglist>(int offset1, int dim1, int offset2, int dim2) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_bz_offsetData</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>4e78b296ead3b85b098c4896a4a79a80</anchor>
      <arglist>(sizeType i)</arglist>
    </member>
    <member kind="function">
      <type>T_range_result</type>
      <name>operator()</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>441b0aaa670b7b88b31f0c78b7306572</anchor>
      <arglist>(RectDomain&lt; rank &gt; d) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prettyPrint</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>35afaaafc252685aec371a43b0732542</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>shapeCheck</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>2ad1db16bac8ddc008f4cf66262d015c</anchor>
      <arglist>(const T_shape &amp;) const </arglist>
    </member>
    <member kind="function">
      <type>SliceInfo&lt; T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11 &gt;::T_slice</type>
      <name>operator()</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>7aa16862a2ff13fbabbbabb60f54f9ca</anchor>
      <arglist>(T1 r1, T2 r2, T3 r3, T4 r4, T5 r5, T6 r6, T7 r7, T8 r8, T9 r9, T10 r10, T11 r11) const </arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>numArrayOperands</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>4a6c89e6f365e00f6b772cda2899bae2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>numIndexPlaceholders</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>714db33b62851f95a15d3ab461156657</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>rank</name>
      <anchorfile>classIndexPlaceholder.html</anchorfile>
      <anchor>efaf88de12441fffbf9dfd800805bb75</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IndexPlaceholder::SliceInfo</name>
    <filename>classIndexPlaceholder_1_1SliceInfo.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>IndexPlaceholder&lt; new_rank &gt;</type>
      <name>T_slice</name>
      <anchorfile>classIndexPlaceholder_1_1SliceInfo.html</anchorfile>
      <anchor>8ace82681bae07bcc916d7166cc0092f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>new_rank</name>
      <anchorfile>classIndexPlaceholder_1_1SliceInfo.html</anchorfile>
      <anchor>d8a2db3eaf3199a7c0276db8147882fa</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IRNGWrapper</name>
    <filename>classIRNGWrapper.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>IRNGWrapper&lt; IRNG, independentState &gt;</name>
    <filename>classIRNGWrapper_3_01IRNG_00_01independentState_01_4.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>IRNG::T_state</type>
      <name>T_state</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01independentState_01_4.html</anchorfile>
      <anchor>3c20a250caa429bc4850244267c3823c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IRNGWrapper</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01independentState_01_4.html</anchorfile>
      <anchor>aebe596aab2e13aa75177d3b5f699256</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IRNGWrapper</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01independentState_01_4.html</anchorfile>
      <anchor>aa31e878c8aeb009726da9a262da9451</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>seed</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01independentState_01_4.html</anchorfile>
      <anchor>7cb0dba820968ee5ba2780afe7579735</anchor>
      <arglist>(IRNG_int x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>seed</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01independentState_01_4.html</anchorfile>
      <anchor>0175c34e19f261544a5995fc79aba91a</anchor>
      <arglist>(std::vector&lt; IRNG_int &gt; x)</arglist>
    </member>
    <member kind="function">
      <type>T_state</type>
      <name>getState</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01independentState_01_4.html</anchorfile>
      <anchor>55eb9d0cdb78ec9bb90a0d21ba862bc5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getStateString</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01independentState_01_4.html</anchorfile>
      <anchor>09fe22cf9be60567f8f70f92aafce0cf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setState</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01independentState_01_4.html</anchorfile>
      <anchor>25d4e6cc30694065b6b8615c2ae88e35</anchor>
      <arglist>(const T_state &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setState</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01independentState_01_4.html</anchorfile>
      <anchor>89ed416ce53b8fde72c2f15680dcba46</anchor>
      <arglist>(const std::string &amp;s)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>IRNG</type>
      <name>irng_</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01independentState_01_4.html</anchorfile>
      <anchor>5f5ed6c912616377d2b29e9d139cf671</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IRNGWrapper&lt; IRNG, sharedState &gt;</name>
    <filename>classIRNGWrapper_3_01IRNG_00_01sharedState_01_4.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>IRNG::T_state</type>
      <name>T_state</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01sharedState_01_4.html</anchorfile>
      <anchor>149398a8ddae6e16dada7fad33cdf48c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>seed</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01sharedState_01_4.html</anchorfile>
      <anchor>181420d4b55843c5f0b4736e2fbbc70e</anchor>
      <arglist>(IRNG_int x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>seed</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01sharedState_01_4.html</anchorfile>
      <anchor>9e957d6bfc7cecfabb73430dbc426734</anchor>
      <arglist>(std::vector&lt; IRNG_int &gt; x)</arglist>
    </member>
    <member kind="function">
      <type>T_state</type>
      <name>getState</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01sharedState_01_4.html</anchorfile>
      <anchor>9ec5c0dbf3a57362ad4bf55ac44cc50d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getStateString</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01sharedState_01_4.html</anchorfile>
      <anchor>dbad8112ed466e39617d7a89eecf8eac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setState</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01sharedState_01_4.html</anchorfile>
      <anchor>246750a8ee3a2b2f7720fa452c9653c6</anchor>
      <arglist>(const T_state &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setState</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01sharedState_01_4.html</anchorfile>
      <anchor>811d51240b5eb3a62f9ae7b5b2ebb262</anchor>
      <arglist>(const std::string &amp;s)</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static IRNG</type>
      <name>irng_</name>
      <anchorfile>classIRNGWrapper_3_01IRNG_00_01sharedState_01_4.html</anchorfile>
      <anchor>fc08780484d36ef82967a28642d4f5b8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Less</name>
    <filename>structLess.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>bool</type>
      <name>T_numtype</name>
      <anchorfile>structLess.html</anchorfile>
      <anchor>ea50dc40d12ea6c4db3772a9bce2174d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structLess.html</anchorfile>
      <anchor>e8fcdf4d548c1406980f2f01df018d44</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structLess.html</anchorfile>
      <anchor>3d3777cadf380389ca41867e12d6aaa7</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>LessOrEqual</name>
    <filename>structLessOrEqual.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>bool</type>
      <name>T_numtype</name>
      <anchorfile>structLessOrEqual.html</anchorfile>
      <anchor>5da245a09b4be69e85e4577eeae6b4de</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structLessOrEqual.html</anchorfile>
      <anchor>ead3c7e1b2e0942026d4d0e1bf4a62ca</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structLessOrEqual.html</anchorfile>
      <anchor>cb1b3e02488319eb2434a83519396390</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ListInitializationSwitch</name>
    <filename>classListInitializationSwitch.html</filename>
    <templarg>T_array</templarg>
    <templarg>T_iterator</templarg>
    <member kind="typedef">
      <type>_bz_typename T_array::T_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classListInitializationSwitch.html</anchorfile>
      <anchor>c93356c61fc683b281fe7eed00da55f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ListInitializationSwitch</name>
      <anchorfile>classListInitializationSwitch.html</anchorfile>
      <anchor>f9cdfb54296b9b65c48eed25190a4dbe</anchor>
      <arglist>(const ListInitializationSwitch&lt; T_array &gt; &amp;lis)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ListInitializationSwitch</name>
      <anchorfile>classListInitializationSwitch.html</anchorfile>
      <anchor>a5cc44c2d4a4467ecaed44a785ff483b</anchor>
      <arglist>(T_array &amp;array, T_numtype value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ListInitializationSwitch</name>
      <anchorfile>classListInitializationSwitch.html</anchorfile>
      <anchor>a009c6eef5a558d075df578f0b439fb0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ListInitializer&lt; T_numtype, T_iterator &gt;</type>
      <name>operator,</name>
      <anchorfile>classListInitializationSwitch.html</anchorfile>
      <anchor>6b36c051c9959a418b00cb6853655ba0</anchor>
      <arglist>(T_numtype x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disable</name>
      <anchorfile>classListInitializationSwitch.html</anchorfile>
      <anchor>3a05fb2532600f69e6ded3ec6ff01da4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_array &amp;</type>
      <name>array_</name>
      <anchorfile>classListInitializationSwitch.html</anchorfile>
      <anchor>376d96d286a26585bf025c3fd9a8cad4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_numtype</type>
      <name>value_</name>
      <anchorfile>classListInitializationSwitch.html</anchorfile>
      <anchor>89b33e2549664fee19e796c8cee8a06f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>wipeOnDestruct_</name>
      <anchorfile>classListInitializationSwitch.html</anchorfile>
      <anchor>7f44ada4e2b0abd813eb2acfc72c69cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>ListInitializationSwitch</name>
      <anchorfile>classListInitializationSwitch.html</anchorfile>
      <anchor>9d7a6ad65a13d3d39496da0a131c6bb0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ListInitializer</name>
    <filename>classListInitializer.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>ListInitializer</name>
      <anchorfile>classListInitializer.html</anchorfile>
      <anchor>935e501beebdb1dbe2c67f82ecdf948b</anchor>
      <arglist>(T_iterator iter)</arglist>
    </member>
    <member kind="function">
      <type>ListInitializer&lt; T_numtype, T_iterator &gt;</type>
      <name>operator,</name>
      <anchorfile>classListInitializer.html</anchorfile>
      <anchor>7526eb798ee7471dc84e118c07e9f3fe</anchor>
      <arglist>(T_numtype x)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_iterator</type>
      <name>iter_</name>
      <anchorfile>classListInitializer.html</anchorfile>
      <anchor>5800b8d9f244067505c8e3d49e44655d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>ListInitializer</name>
      <anchorfile>classListInitializer.html</anchorfile>
      <anchor>21ecdbd44be8b5d2a27eaef3a0c48c89</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>LogicalAnd</name>
    <filename>structLogicalAnd.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>bool</type>
      <name>T_numtype</name>
      <anchorfile>structLogicalAnd.html</anchorfile>
      <anchor>a19dc9b79e623426a2c12175e87f71ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structLogicalAnd.html</anchorfile>
      <anchor>4cb9f5f1647ad72da4ee4bb70612bd4b</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structLogicalAnd.html</anchorfile>
      <anchor>bc4d24640b100e222df6c5dee3400603</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>LogicalNot</name>
    <filename>structLogicalNot.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>bool</type>
      <name>T_numtype</name>
      <anchorfile>structLogicalNot.html</anchorfile>
      <anchor>c0bcaddeb53e0a62cf7479fadf2faf5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structLogicalNot.html</anchorfile>
      <anchor>f550cb2c17fd854fa34b344a12096d6c</anchor>
      <arglist>(T_numtype1 a)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structLogicalNot.html</anchorfile>
      <anchor>c14c55eb3e0580b5bb779b0b55ffd0d7</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>LogicalOr</name>
    <filename>structLogicalOr.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>bool</type>
      <name>T_numtype</name>
      <anchorfile>structLogicalOr.html</anchorfile>
      <anchor>2cdbbb45b67c0037d94716c8c3ef2953</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structLogicalOr.html</anchorfile>
      <anchor>7cb448919932e0fcf4c453a4594b707c</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structLogicalOr.html</anchorfile>
      <anchor>bf3509bb5f7e4e969eb7b2f4af7f5fdf</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>LowerTriangular</name>
    <filename>classLowerTriangular.html</filename>
    <base>MatrixStructure</base>
    <member kind="typedef">
      <type>LowerTriangularIterator</type>
      <name>T_iterator</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>d2f4644d5de76f582810385ccfd2b176</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LowerTriangular</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>f8e9f2c82a2537e00a6eb9de2862c45c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LowerTriangular</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>d0c3022864d17d66578ed5c7c1cf39a5</anchor>
      <arglist>(unsigned size)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LowerTriangular</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>e299ce49cf7a1b1b2f0331cded54a074</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>columns</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>9c3aaffa3762dcc201f6ead3ee37cc75</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>coordToOffset</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>e86c6b501ea63695737ee421f73368b1</anchor>
      <arglist>(unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>firstInRow</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>f664460399b80c6f4b79a327c75d86cf</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>get</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>bfe3fa66360129bf4568138de790ff4b</anchor>
      <arglist>(const T_numtype *restrict data, unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>get</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>71cf21cd3926c9d7a33982be5d96ef2c</anchor>
      <arglist>(T_numtype *restrict data, unsigned i, unsigned j)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>lastInRow</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>474fbf1ed788a5a1599e85b5694344f0</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>firstInCol</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>b66ec9810ef7cb7843d121fc755f772b</anchor>
      <arglist>(unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>lastInCol</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>640586ab8c0e475892798d3313365d49</anchor>
      <arglist>(unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>inRange</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>054536ca8f4673c5641068a159e0a5d1</anchor>
      <arglist>(unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>numElements</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>44b436551cbb7daa25c1af18c4577a6c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>rows</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>6836cbda5d17d0533b7e9a11212b6067</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>4df06de907b81d14fea6f5c9f4086369</anchor>
      <arglist>(unsigned size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>d16b70f99811b5fae95de5461c403486</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned</type>
      <name>size_</name>
      <anchorfile>classLowerTriangular.html</anchorfile>
      <anchor>8e03e3074d92bfd753a7c02dcd63af51</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>LowerTriangularIterator</name>
    <filename>classLowerTriangularIterator.html</filename>
    <member kind="function">
      <type></type>
      <name>LowerTriangularIterator</name>
      <anchorfile>classLowerTriangularIterator.html</anchorfile>
      <anchor>dd29bef9ecb40a8b01968a773ffd753a</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>classLowerTriangularIterator.html</anchorfile>
      <anchor>1f8e805dbce1c75c1632db956964bb82</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator++</name>
      <anchorfile>classLowerTriangularIterator.html</anchorfile>
      <anchor>3a6ef9b64d999f93ee128f74aca38527</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>row</name>
      <anchorfile>classLowerTriangularIterator.html</anchorfile>
      <anchor>7ab1227d3631b54fa8232a5e6be63f90</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>col</name>
      <anchorfile>classLowerTriangularIterator.html</anchorfile>
      <anchor>e40bea60442dec3df59a9ac33f321362</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>offset</name>
      <anchorfile>classLowerTriangularIterator.html</anchorfile>
      <anchor>c7ce365e64b671be6c612d27da6b1f35</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>size_</name>
      <anchorfile>classLowerTriangularIterator.html</anchorfile>
      <anchor>4e7c1d15a20473697c3d5f50bbe30048</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>good_</name>
      <anchorfile>classLowerTriangularIterator.html</anchorfile>
      <anchor>1fe365228ff5a0b895ec8385c7f56bef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>offset_</name>
      <anchorfile>classLowerTriangularIterator.html</anchorfile>
      <anchor>b0e3b6c8a550e73abcde1300c7d42413</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>i_</name>
      <anchorfile>classLowerTriangularIterator.html</anchorfile>
      <anchor>463a9c160941415d1129a078f3b307d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>j_</name>
      <anchorfile>classLowerTriangularIterator.html</anchorfile>
      <anchor>034c0e9424c86261f4268230569361e1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Matrix</name>
    <filename>classMatrix.html</filename>
    <templarg>P_numtype</templarg>
    <templarg>BZ_TEMPLATE_DEFAULT</templarg>
    <base protection="protected">MemoryBlockReference&lt; P_numtype &gt;</base>
    <member kind="typedef">
      <type>P_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>a2e0c7f09cbf31c078ad0b0977588e70</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>P_structure</type>
      <name>T_structure</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>0441c5aed57ace2b56e48fc618b081bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Matrix&lt; P_numtype, P_structure &gt;</type>
      <name>T_matrix</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>e07f7dfb83325c5854333ed7e85d2ebb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Matrix</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>f681cd26c7a0d3a102e309198be1c8c8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Matrix</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>6a7f5ed5100e108331ece885dc641dd5</anchor>
      <arglist>(int rows, int cols, T_structure structure=T_structure())</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>cols</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>7a780e46272c5270b6e3d5dcb4c70e4b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>columns</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>7943fa99256bcd90b17288e12466168f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>makeUnique</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>b4a3546ccce6320ac4a42e02d1edd180</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>numElements</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>d29299b659a1fd96ce011623e065a1a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reference</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>dafdeeb697e99efebd602a505685edec</anchor>
      <arglist>(T_matrix &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>ca81b41a4f1e72d05e2e28a99f8bdb58</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>rows</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>c042ab4f91be304a8c7a6b9c3505157f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>_bz_MatrixRef&lt; T_numtype, T_structure &gt;</type>
      <name>_bz_getRef</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>ca6af21599b112514b60a251e26bfcb5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator()</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>6a6d0a116a2f2a67f74826802c155080</anchor>
      <arglist>(unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>ed58f052dd1ef9c14a3fcc3335a90905</anchor>
      <arglist>(unsigned i, unsigned j)</arglist>
    </member>
    <member kind="function">
      <type>T_matrix &amp;</type>
      <name>operator=</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>7685367f9f39a4a5491f1ebdd8bc9c1f</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_matrix &amp;</type>
      <name>operator+=</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>7c018a47b2dc374ce5557011ce25a97c</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_matrix &amp;</type>
      <name>operator-=</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>4c6e1284becba17f5e718be131297b05</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_matrix &amp;</type>
      <name>operator*=</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>5efa9625f2bc76625fb8dbd4d7c0ee79</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_matrix &amp;</type>
      <name>operator/=</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>c40dded18c2020ca4e07fa62357c1cf6</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_matrix &amp;</type>
      <name>operator=</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>cd99ff74498c0a7d14358f36bfdad359</anchor>
      <arglist>(const Matrix&lt; P_numtype2, P_structure2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_matrix &amp;</type>
      <name>operator+=</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>d07d9409286a7025f2cef4264a716321</anchor>
      <arglist>(const Matrix&lt; P_numtype2, P_structure2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_matrix &amp;</type>
      <name>operator-=</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>e17a5b379888e7ac1464d1113772ac0f</anchor>
      <arglist>(const Matrix&lt; P_numtype2, P_structure2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_matrix &amp;</type>
      <name>operator*=</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>21a0fbd4d624901d2cca93f082d8ceda</anchor>
      <arglist>(const Matrix&lt; P_numtype2, P_structure2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_matrix &amp;</type>
      <name>operator/=</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>e79f028e0031e49523a79f7814b19332</anchor>
      <arglist>(const Matrix&lt; P_numtype2, P_structure2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_matrix &amp;</type>
      <name>operator=</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>85c6cde58dc888d6294ceb99d955e2d5</anchor>
      <arglist>(_bz_MatExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_matrix &amp;</type>
      <name>operator++</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>d3dc8cdf857c29e70ecdf606eaa5e893</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator++</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>94c4061ae4d963408cd3f9e4a611daef</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>T_matrix &amp;</type>
      <name>operator--</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>5c90036a8cb89645d761d77ee14462fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator--</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>0f3f165869af9b9a63e18507164e189d</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>MemoryBlockReference&lt; P_numtype &gt;</type>
      <name>T_base</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>3805c017cb5a2bc0a0520572e219f6a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T_structure</type>
      <name>structure_</name>
      <anchorfile>classMatrix.html</anchorfile>
      <anchor>fd6f66aad8c628934e34d59134d05ee2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MatrixStructure</name>
    <filename>classMatrixStructure.html</filename>
  </compound>
  <compound kind="class">
    <name>MemoryBlock</name>
    <filename>classMemoryBlock.html</filename>
    <templarg>P_type</templarg>
    <member kind="typedef">
      <type>P_type</type>
      <name>T_type</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>6281668c80ac278a3912d82549b69d25</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>MemoryBlock</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>9163b536fb7736ab1415633cbcd07ba5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>MemoryBlock</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>3856def13eaae6f2342eceb473175764</anchor>
      <arglist>(sizeType items)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>MemoryBlock</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>5f8f12141e3350487ef4868c790a6ee4</anchor>
      <arglist>(sizeType length, T_type *data)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~MemoryBlock</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>a4bd0004d3f6452e205ac328bf87a0f3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>doLock</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>ed8772cd85f88d489e0cbfb1f47918c3</anchor>
      <arglist>(bool lockingPolicy)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>addReference</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>450beb9276de1e25ad85fcc6372a1b64</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>T_type *restrict</type>
      <name>data</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>6cb6c999416b3dab1b120156fce2a1ee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const T_type *restrict</type>
      <name>data</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>a7736e3ccff0db3a43b70a8b9b05fd54</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>T_type *&amp;</type>
      <name>dataBlockAddress</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>7b44e01c3f8af72e6e695a766afeea72</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>sizeType</type>
      <name>length</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>24abff29b9c109c552a42ff34535041e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>removeReference</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>f9277d6452801374fe337623f5413058</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>references</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>91009415fa949d3949ba829c760b6c9d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>allocate</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>9cd3d110b730265219ebc785988ca96c</anchor>
      <arglist>(sizeType length)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>deallocate</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>01a4125a3dbff1c7cde94934ff0841c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>MemoryBlock</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>2aa8f3aff840dea4da0274c4cd9b14ba</anchor>
      <arglist>(const MemoryBlock&lt; T_type &gt; &amp;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>operator=</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>1fe3ae7491faf44d7661118da5fea7e7</anchor>
      <arglist>(const MemoryBlock&lt; T_type &gt; &amp;)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T_type *restrict</type>
      <name>data_</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>d69b45b731d96b95ce88afb54039302a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T_type *</type>
      <name>dataBlockAddress_</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>4feebf2d5c97f66c783e894a7087c0cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>volatile int</type>
      <name>references_</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>e35529475e30ae76468065b56d366667</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>mutexLocking_</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>46ea7bb11d1cb42fb0c8b5f7c5124331</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>sizeType</type>
      <name>length_</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>0298b4c7299b8e8698628ae2c801e161</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>MemoryBlockReference&lt; P_type &gt;</name>
      <anchorfile>classMemoryBlock.html</anchorfile>
      <anchor>24807c23f28b2f1a89f39c7dd9fb04ae</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MemoryBlockReference</name>
    <filename>classMemoryBlockReference.html</filename>
    <templarg>P_type</templarg>
    <member kind="typedef">
      <type>P_type</type>
      <name>T_type</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>bf67312980afa9874edcdacc5d3f3eb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MemoryBlockReference</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>60dea46292bf937fcd039e4ac4388dc1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MemoryBlockReference</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>e3cdb8f1ca1c536672b3955e713a4ae3</anchor>
      <arglist>(MemoryBlockReference&lt; T_type &gt; &amp;ref, sizeType offset=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MemoryBlockReference</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>ed37efcb099103edd568daff9935570c</anchor>
      <arglist>(sizeType length, T_type *data, preexistingMemoryPolicy deletionPolicy)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MemoryBlockReference</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>5b5b98a711c875ac3b207e335e9220d0</anchor>
      <arglist>(sizeType items)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~MemoryBlockReference</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>a76996b8ab86fd43c2da3624eb945a60</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>numReferences</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>3aa545876fa5afe5217108d952113b88</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>lockReferenceCount</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>8f2180e4f5a8c44b2cb44adcd5130c2a</anchor>
      <arglist>(bool lockingPolicy) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>changeToNullBlock</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>e3e3d72bd8f0fe616f4cd5e7cd3edc3d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>changeBlock</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>154e209dce462f57968f53950dff2dca</anchor>
      <arglist>(MemoryBlockReference&lt; T_type &gt; &amp;ref, sizeType offset=0)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>newBlock</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>88cd31c126086a7eaa816f722b9239ce</anchor>
      <arglist>(sizeType items)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_type *restrict</type>
      <name>data_</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>a357e2cf55a9eac0da062e7e0c27a07a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>blockRemoveReference</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>733bb94fe509f71ae8842cf788b8d434</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>addReference</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>dd667982679a9e8ba5f80acf2dee0aa2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>removeReference</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>3437238e2657eb0ef9ccaa9733b11e48</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>operator=</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>44993edc18044184d7abd3239e7c30d2</anchor>
      <arglist>(const MemoryBlockReference&lt; T_type &gt; &amp;)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>MemoryBlock&lt; T_type &gt; *</type>
      <name>block_</name>
      <anchorfile>classMemoryBlockReference.html</anchorfile>
      <anchor>96401d31ddf27dffa6bae3e518ea5d79</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MersenneTwister</name>
    <filename>classMersenneTwister.html</filename>
    <class kind="struct">MersenneTwister::BitMixer</class>
    <class kind="class">MersenneTwister::mt_state</class>
    <member kind="typedef">
      <type>mt_state</type>
      <name>T_state</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>d0a9ea2cc1572693a37df878ae065730</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MersenneTwister</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>003f17bd5590608d481738f9b926fef6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>seed</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>2f6e0902671e03578423d19849881271</anchor>
      <arglist>(twist_int seed=reference_seed)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reload</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>d0aa3a5a40cac4ff022be9d66205fda5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>twist_int</type>
      <name>random</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>f674667e319b149105d60d75b7ac49e0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MersenneTwister</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>003f17bd5590608d481738f9b926fef6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MersenneTwister</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>0846bfbc0294d807e285774eb365d791</anchor>
      <arglist>(twist_int aa, twist_int bb, twist_int cc)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MersenneTwister</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>cb32e87c27794a6773e74a2213e67a7a</anchor>
      <arglist>(twist_int initial_seed)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MersenneTwister</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>cbcc275e10806bd3b499a9fa8b5b1674</anchor>
      <arglist>(twist_int aa, twist_int bb, twist_int cc, twist_int initial_seed)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>seed</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>2f6e0902671e03578423d19849881271</anchor>
      <arglist>(twist_int seed=reference_seed)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>seed</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>49f4e0988f06bda7a29786aaf8aaeb71</anchor>
      <arglist>(State seed_vector)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reload</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>d0aa3a5a40cac4ff022be9d66205fda5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>twist_int</type>
      <name>random</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>f674667e319b149105d60d75b7ac49e0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>T_state</type>
      <name>getState</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>b18820358213655f37047d405dbabeee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getStateString</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>58ede51949a4a8a58fea193205c41315</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setState</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>b2a6fab5b95f538e681603d86ea8316a</anchor>
      <arglist>(const T_state &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setState</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>4162cc9b1acbb3c14a91bdaf235a29e5</anchor>
      <arglist>(const std::string &amp;s)</arglist>
    </member>
    <member kind="enumvalue">
      <name>N</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>db8cc037a02e42acd8020b18608d939ef2e9ebf93e865e5246d5dffda4782003</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PF</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>db8cc037a02e42acd8020b18608d939ed548100998c89c737c2d35f9d9d43837</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>reference_seed</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>db8cc037a02e42acd8020b18608d939ebf7eab15b6cb08e0b403e2a91a145d3b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>N</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>db8cc037a02e42acd8020b18608d939ef2e9ebf93e865e5246d5dffda4782003</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PF</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>db8cc037a02e42acd8020b18608d939ed548100998c89c737c2d35f9d9d43837</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>reference_seed</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>db8cc037a02e42acd8020b18608d939ebf7eab15b6cb08e0b403e2a91a145d3b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>unsigned int</type>
      <name>twist_int</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>ba05296f0232a4ae185b4bc0e693db30</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>vector&lt; twist_int &gt;</type>
      <name>State</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>3e932cdbd87949e9e1232fb991e12012</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>State::iterator</type>
      <name>Iter</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>cda2fe5fd19206999d9ce9ca0e7ce338</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>vector&lt; twist_int &gt;</type>
      <name>State</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>3e932cdbd87949e9e1232fb991e12012</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>State::size_type</type>
      <name>SizeType</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>85fd7651fe5b9da17f6a64a5b865e552</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>State::iterator</type>
      <name>Iter</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>cda2fe5fd19206999d9ce9ca0e7ce338</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>f25bae282154b414446dd1edaabdd19d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>State</type>
      <name>S</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>bc3f15f62f0f1281d7d2b07a20378580</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Iter</type>
      <name>I</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>bb1bef504cfff8827383399a20449f65</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BitMixer</type>
      <name>twist_</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>5fe2e0aad2349da210293a6abc3c57cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const twist_int</type>
      <name>b_</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>c504e53b560acb5fbb6555f2ded6787d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const twist_int</type>
      <name>c_</name>
      <anchorfile>classMersenneTwister.html</anchorfile>
      <anchor>0701a67794b30485a7370c277c73ba1c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>MersenneTwister::BitMixer</name>
    <filename>structMersenneTwister_1_1BitMixer.html</filename>
    <member kind="enumvalue">
      <name>K</name>
      <anchorfile>structMersenneTwister_1_1BitMixer.html</anchorfile>
      <anchor>2bd35860cd8ef1d441ba734d32c2d54ff78772660c34c878baa280db4b50f8a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BitMixer</name>
      <anchorfile>structMersenneTwister_1_1BitMixer.html</anchorfile>
      <anchor>877757609c04b3226656d63e89a12a67</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>twist_int</type>
      <name>high_mask</name>
      <anchorfile>structMersenneTwister_1_1BitMixer.html</anchorfile>
      <anchor>6ed5ac01a9920687d616a3251aeb128a</anchor>
      <arglist>(twist_int s1) const </arglist>
    </member>
    <member kind="function">
      <type>twist_int</type>
      <name>operator()</name>
      <anchorfile>structMersenneTwister_1_1BitMixer.html</anchorfile>
      <anchor>4c63e895806abbc0f2fa1c0c43408569</anchor>
      <arglist>(twist_int s1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BitMixer</name>
      <anchorfile>structMersenneTwister_1_1BitMixer.html</anchorfile>
      <anchor>877757609c04b3226656d63e89a12a67</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BitMixer</name>
      <anchorfile>structMersenneTwister_1_1BitMixer.html</anchorfile>
      <anchor>8d72bc7ad48c06ee8b3d90ff16c824de</anchor>
      <arglist>(twist_int k)</arglist>
    </member>
    <member kind="function">
      <type>twist_int</type>
      <name>low_mask</name>
      <anchorfile>structMersenneTwister_1_1BitMixer.html</anchorfile>
      <anchor>9c21058ee6bd66869aa8e1e57f0bc002</anchor>
      <arglist>(twist_int s1) const </arglist>
    </member>
    <member kind="function">
      <type>twist_int</type>
      <name>high_mask</name>
      <anchorfile>structMersenneTwister_1_1BitMixer.html</anchorfile>
      <anchor>6ed5ac01a9920687d616a3251aeb128a</anchor>
      <arglist>(twist_int s1) const </arglist>
    </member>
    <member kind="function">
      <type>twist_int</type>
      <name>operator()</name>
      <anchorfile>structMersenneTwister_1_1BitMixer.html</anchorfile>
      <anchor>4c63e895806abbc0f2fa1c0c43408569</anchor>
      <arglist>(twist_int s1)</arglist>
    </member>
    <member kind="variable">
      <type>twist_int</type>
      <name>s0</name>
      <anchorfile>structMersenneTwister_1_1BitMixer.html</anchorfile>
      <anchor>9cb7f7e60511d471f0afd7c9e8d0df37</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const twist_int</type>
      <name>K</name>
      <anchorfile>structMersenneTwister_1_1BitMixer.html</anchorfile>
      <anchor>0322d7d152afeb3de07bf8561e3a6551</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend twist_int</type>
      <name>low_mask</name>
      <anchorfile>structMersenneTwister_1_1BitMixer.html</anchorfile>
      <anchor>e26e49cee2d250eb1a65dbd3f1eb5354</anchor>
      <arglist>(twist_int s1)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MersenneTwister::mt_state</name>
    <filename>classMersenneTwister_1_1mt__state.html</filename>
    <member kind="function">
      <type></type>
      <name>mt_state</name>
      <anchorfile>classMersenneTwister_1_1mt__state.html</anchorfile>
      <anchor>6bea036ecdebf05c94a985659543ed82</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>mt_state</name>
      <anchorfile>classMersenneTwister_1_1mt__state.html</anchorfile>
      <anchor>4aec5ff4edd17aa5e1f6a8b71a3a46f8</anchor>
      <arglist>(State s, State::difference_type i)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>mt_state</name>
      <anchorfile>classMersenneTwister_1_1mt__state.html</anchorfile>
      <anchor>ba61c3b71b5eef6d9592a6da2bcf0124</anchor>
      <arglist>(const std::string &amp;s)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>classMersenneTwister_1_1mt__state.html</anchorfile>
      <anchor>c1335106ad0d97885b0104bb373b5413</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>str</name>
      <anchorfile>classMersenneTwister_1_1mt__state.html</anchorfile>
      <anchor>f045387953a5a13650d9ee788dd4bea8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>State</type>
      <name>S</name>
      <anchorfile>classMersenneTwister_1_1mt__state.html</anchorfile>
      <anchor>368dc4512942e7642aaaa2085ccd4cbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>State::difference_type</type>
      <name>I</name>
      <anchorfile>classMersenneTwister_1_1mt__state.html</anchorfile>
      <anchor>e0d24fac6c8b9e0bd120589dcb061b08</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>MersenneTwister</name>
      <anchorfile>classMersenneTwister_1_1mt__state.html</anchorfile>
      <anchor>b4f64ddea8d782febd7d9793dd71ebd2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MersenneTwisterCreator</name>
    <filename>classMersenneTwisterCreator.html</filename>
    <member kind="function" static="yes">
      <type>static MersenneTwister</type>
      <name>create</name>
      <anchorfile>classMersenneTwisterCreator.html</anchorfile>
      <anchor>5b09cf5823aeea8ec26b85f1c22b2009</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static const unsigned int</type>
      <name>n</name>
      <anchorfile>classMersenneTwisterCreator.html</anchorfile>
      <anchor>51012f9fcbe71062f1f54470bb3f5813</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static const twist_int</type>
      <name>a_</name>
      <anchorfile>classMersenneTwisterCreator.html</anchorfile>
      <anchor>f3245903dbe5daef327b7bd11e87392c</anchor>
      <arglist>[n]</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static const twist_int</type>
      <name>b_</name>
      <anchorfile>classMersenneTwisterCreator.html</anchorfile>
      <anchor>f69548fe71d9d4ea51e065fafab80127</anchor>
      <arglist>[n]</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static const twist_int</type>
      <name>c_</name>
      <anchorfile>classMersenneTwisterCreator.html</anchorfile>
      <anchor>c6444497163c18514fa26861581d1ffc</anchor>
      <arglist>[n]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MersenneTwisterDouble</name>
    <filename>classMersenneTwisterDouble.html</filename>
    <member kind="function">
      <type></type>
      <name>MersenneTwisterDouble</name>
      <anchorfile>classMersenneTwisterDouble.html</anchorfile>
      <anchor>44ed7490307d415417765610956e0623</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>randomize</name>
      <anchorfile>classMersenneTwisterDouble.html</anchorfile>
      <anchor>8c33add29852de0bb90bed7f57f252f3</anchor>
      <arglist>(unsigned int seed)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>random</name>
      <anchorfile>classMersenneTwisterDouble.html</anchorfile>
      <anchor>c55a53961d65f302303d76bd83083a28</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>MersenneTwister</type>
      <name>gen_</name>
      <anchorfile>classMersenneTwisterDouble.html</anchorfile>
      <anchor>cad28378eb9be6ad40f55fd2c928e51f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>f</name>
      <anchorfile>classMersenneTwisterDouble.html</anchorfile>
      <anchor>bd148bbc340971d9b713d06dbe63f492</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>MinMaxValue</name>
    <filename>structMinMaxValue.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator=</name>
      <anchorfile>structMinMaxValue.html</anchorfile>
      <anchor>3bcf460c46cf98f6b0708e3514418390</anchor>
      <arglist>(const T &amp;val)</arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>min</name>
      <anchorfile>structMinMaxValue.html</anchorfile>
      <anchor>224267034a24edb0e50b68584bcd17fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>max</name>
      <anchorfile>structMinMaxValue.html</anchorfile>
      <anchor>f6dd31e01bb4ab3baff80606d556a7fe</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Modulo</name>
    <filename>structModulo.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type>typedef</type>
      <name>BZ_PROMOTE</name>
      <anchorfile>structModulo.html</anchorfile>
      <anchor>f9932729cadf75a881d9893e2bad3a76</anchor>
      <arglist>(T_numtype1, T_numtype2) T_numtype</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structModulo.html</anchorfile>
      <anchor>ce716c473a067d2c5d9d57a980883193</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structModulo.html</anchorfile>
      <anchor>352ad78f68ec78479c3d6f1a74e499c9</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Multiply</name>
    <filename>structMultiply.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type>typedef</type>
      <name>BZ_PROMOTE</name>
      <anchorfile>structMultiply.html</anchorfile>
      <anchor>055a4dfdc8ba9fccfb74da4d25561d70</anchor>
      <arglist>(T_numtype1, T_numtype2) T_numtype</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structMultiply.html</anchorfile>
      <anchor>b014a987045229336e7fbe1fb0efbf4f</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structMultiply.html</anchorfile>
      <anchor>e3b082c6398de4a514a26e1193e64dbe</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Normal</name>
    <filename>classNormal.html</filename>
    <templarg>BZ_TEMPLATE_DEFAULT</templarg>
    <base>NormalUnit&lt; T, IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>double</type>
      <name>T_numtype</name>
      <anchorfile>classNormal.html</anchorfile>
      <anchor>db906ca01b97f722be42f1aa55febbdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T</type>
      <name>T_numtype</name>
      <anchorfile>classNormal.html</anchorfile>
      <anchor>abfd66f25f68386c35edb20bd3574542</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Normal</name>
      <anchorfile>classNormal.html</anchorfile>
      <anchor>d48f902513a206568678e02189a24419</anchor>
      <arglist>(double mean=0.0, double variance=1.0, double=0.0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>randomize</name>
      <anchorfile>classNormal.html</anchorfile>
      <anchor>29e7f0f527451b378a410949893e3a5f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>random</name>
      <anchorfile>classNormal.html</anchorfile>
      <anchor>36d9056940ee96a0452693d31a20b51c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Normal</name>
      <anchorfile>classNormal.html</anchorfile>
      <anchor>de99d4a07e578cb82f666cc28efc0978</anchor>
      <arglist>(T mean, T standardDeviation)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Normal</name>
      <anchorfile>classNormal.html</anchorfile>
      <anchor>501ce9c681472833f65ed1fd594603de</anchor>
      <arglist>(T mean, T standardDeviation, unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>random</name>
      <anchorfile>classNormal.html</anchorfile>
      <anchor>4480b2e0e35f26f5ee78996c9f6a25b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>mean_</name>
      <anchorfile>classNormal.html</anchorfile>
      <anchor>1ba32ec6e3b9069cc471f0e14641d8f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>sigma_</name>
      <anchorfile>classNormal.html</anchorfile>
      <anchor>2d5a520390f17870c70b9599229131f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>P_uniform</type>
      <name>uniform_</name>
      <anchorfile>classNormal.html</anchorfile>
      <anchor>f130696090eed51bad77a30b3ac13b17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T</type>
      <name>mean_</name>
      <anchorfile>classNormal.html</anchorfile>
      <anchor>6fffd6b3fcb89c4f3c1b338c11480c2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T</type>
      <name>standardDeviation_</name>
      <anchorfile>classNormal.html</anchorfile>
      <anchor>9d93b8e6d2f2d27e7a0a7eb7a4d3e2b8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NormalUnit</name>
    <filename>classNormalUnit.html</filename>
    <templarg>T</templarg>
    <templarg>IRNG</templarg>
    <templarg>stateTag</templarg>
    <base>UniformOpen&lt; T, IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>T</type>
      <name>T_numtype</name>
      <anchorfile>classNormalUnit.html</anchorfile>
      <anchor>e222b53f3bdeb92ae2f9193c0c2a5fac</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NormalUnit</name>
      <anchorfile>classNormalUnit.html</anchorfile>
      <anchor>0340d0830c9a0194b72d445e01ae609f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NormalUnit</name>
      <anchorfile>classNormalUnit.html</anchorfile>
      <anchor>79f484ccc550a3dd31ed688a1a490533</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>random</name>
      <anchorfile>classNormalUnit.html</anchorfile>
      <anchor>2cfc6c87e3e9782e79016cefecf97468</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>NotEqual</name>
    <filename>structNotEqual.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>bool</type>
      <name>T_numtype</name>
      <anchorfile>structNotEqual.html</anchorfile>
      <anchor>4e272874d7e63082f09dcbfc89642535</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structNotEqual.html</anchorfile>
      <anchor>0bfd55a00e14a83ecdd32ff193aa1624</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structNotEqual.html</anchorfile>
      <anchor>4cb6d91705e9e9a40f71b0bf1bce2935</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>prettyPrintFormat</name>
    <filename>classprettyPrintFormat.html</filename>
    <member kind="function">
      <type></type>
      <name>prettyPrintFormat</name>
      <anchorfile>classprettyPrintFormat.html</anchorfile>
      <anchor>3561a7d09b34dbb7f5751bbffb0c7408</anchor>
      <arglist>(const bool terse=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDumpArrayShapesMode</name>
      <anchorfile>classprettyPrintFormat.html</anchorfile>
      <anchor>bb99502281aab1a5fe35fd4de28c031b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>nextArrayOperandSymbol</name>
      <anchorfile>classprettyPrintFormat.html</anchorfile>
      <anchor>97beed6f45776dc3a9673a71688065a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>nextScalarOperandSymbol</name>
      <anchorfile>classprettyPrintFormat.html</anchorfile>
      <anchor>e3b4c9d50f7cc8400367f08a219fa0d0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>tersePrintingSelected</name>
      <anchorfile>classprettyPrintFormat.html</anchorfile>
      <anchor>39eea2c9a1cc2e596e96a0f277bd3b8f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>dumpArrayShapesMode</name>
      <anchorfile>classprettyPrintFormat.html</anchorfile>
      <anchor>52b9abe2ad91ad1d24114d1fb65907fe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>tersePrintingSelected_</name>
      <anchorfile>classprettyPrintFormat.html</anchorfile>
      <anchor>73785a4e7f4232399f2d9e877d225584</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>dumpArrayShapes_</name>
      <anchorfile>classprettyPrintFormat.html</anchorfile>
      <anchor>806f984b70e8cf9165644d162fb636be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>arrayOperandCounter_</name>
      <anchorfile>classprettyPrintFormat.html</anchorfile>
      <anchor>65fa277e622a8609c49eeaefa51bb8ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>scalarOperandCounter_</name>
      <anchorfile>classprettyPrintFormat.html</anchorfile>
      <anchor>6b53514513cf799cabc0fe1c53c53562</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Random</name>
    <filename>classRandom.html</filename>
    <templarg>P_distribution</templarg>
    <member kind="typedef">
      <type>P_distribution</type>
      <name>T_distribution</name>
      <anchorfile>classRandom.html</anchorfile>
      <anchor>e8a9b68164901d4edcc47f1fd7bf5fcf</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>_bz_typename T_distribution::T_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classRandom.html</anchorfile>
      <anchor>b93dcd40486dee5d190ead368dbe4414</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Random</name>
      <anchorfile>classRandom.html</anchorfile>
      <anchor>2e19d676e1fd49f110b57e44b16aa681</anchor>
      <arglist>(double parm1=0.0, double parm2=1.0, double parm3=0.0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>randomize</name>
      <anchorfile>classRandom.html</anchorfile>
      <anchor>4dd0af309c3e5a6148a4d3e2edc85ff7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>random</name>
      <anchorfile>classRandom.html</anchorfile>
      <anchor>2d738bb02046afb490ae627068012d25</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator T_numtype</name>
      <anchorfile>classRandom.html</anchorfile>
      <anchor>b34ff9e00f14d375c5c52f6fcc3c4ef4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_distribution</type>
      <name>generator_</name>
      <anchorfile>classRandom.html</anchorfile>
      <anchor>31e29edc3f3d9aff69a5f0735c0ad13e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Range</name>
    <filename>classRange.html</filename>
    <member kind="typedef">
      <type>int</type>
      <name>T_numtype</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>7a87483a88a6bc1ae142f15459a6b630</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned int</type>
      <name>T_sizetype</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>13f787b56be5a4a42ec05d1c5df7ba00</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Range</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>a4407a93074fbb726deb613f7a067983</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Range</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>28248f518f2f5453e1fc9d6bc9d01c5e</anchor>
      <arglist>(T_numtype slicePosition)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Range</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>84ebcf89f4929331c914156ad278e196</anchor>
      <arglist>(T_numtype first, T_numtype last, diffType stride=1)</arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>first</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>188aeca9a54fa619dc7772dbfd98e721</anchor>
      <arglist>(T_numtype lowRange=0) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>last</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>152dbe1806c9ebe8b57ff41249f6af50</anchor>
      <arglist>(T_numtype highRange=0) const </arglist>
    </member>
    <member kind="function">
      <type>T_sizetype</type>
      <name>length</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>47e2cd1ee0247ff2a55a366fe86dfdc0</anchor>
      <arglist>(int=0) const </arglist>
    </member>
    <member kind="function">
      <type>diffType</type>
      <name>stride</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>27e9a6662fa7458ee384382468cb3402</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isAscendingContiguous</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>427cdad0d78c8abfb5969e4e35e2c303</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRange</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>a7205817f2d5d42c985dec85d51a0015</anchor>
      <arglist>(T_numtype first, T_numtype last, diffType stride=1)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isUnitStride</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>26216cdac88c42b6e32a6bde28ec8350</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Range</type>
      <name>operator-</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>63e90c0e3ee948ee16fbe044d4f05085</anchor>
      <arglist>(T_numtype shift) const </arglist>
    </member>
    <member kind="function">
      <type>Range</type>
      <name>operator+</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>c1bc77d7bb87fbdafb404a9456238b5b</anchor>
      <arglist>(T_numtype shift) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator[]</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>4432670f979488d8a995da017f5fc8db</anchor>
      <arglist>(T_sizetype i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator()</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>911cd275682d1d6598a44f4f7631728f</anchor>
      <arglist>(T_sizetype i) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_bz_hasFastAccess</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>9e9d6f5a2a8ec76b0794897f91fbe696</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>4237cd1ea018a0f03224dd23816d43a3</anchor>
      <arglist>(unsigned int i) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>_bz_suggestLength</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>86d9c9c3caa2e3899061952273d1722b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>_bz_VecExpr&lt; Range &gt;</type>
      <name>_bz_asVecExpr</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>85b8db85a148e364b7782f75ca15e6cc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Range</type>
      <name>all</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>a071ae3c742560c4fff0c5ae44abd4ba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_staticLengthCount</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>4a4f7cb18880893a26e8e1bc44b1b66b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_dynamicLengthCount</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>d0bb30bd4236495d18a0b50fbee6536e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_staticLength</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>9f2976312ae268a1e43f06099da3381e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T_numtype</type>
      <name>first_</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>a0b02e3f5670cb061828c41799c384cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T_numtype</type>
      <name>last_</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>20b2c92ead23ba8d2db5c2cad4db51bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>diffType</type>
      <name>stride_</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>5ba33c82f1ad9bc7fcd98c6a9213c193</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classRange.html</anchorfile>
      <anchor>b26640a4547c7d20f06f4adff50713a9</anchor>
      <arglist>(ostream &amp;os, const Range &amp;range)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceAll</name>
    <filename>classReduceAll.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceAll.html</anchorfile>
      <anchor>3aa5bceb735aa17176eb9906a8648e33</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bool</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceAll.html</anchorfile>
      <anchor>002a37d5068dee35a2e7aa99f51534c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceAll.html</anchorfile>
      <anchor>9ffb6c80449a64513a350fde7be01e25</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceAll</name>
      <anchorfile>classReduceAll.html</anchorfile>
      <anchor>ffd826b420156aff40c8e65eb3c95dc7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceAll.html</anchorfile>
      <anchor>e25409bf599a57f26758db25371a705c</anchor>
      <arglist>(const T_sourcetype &amp;x, const int=0) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceAll.html</anchorfile>
      <anchor>fe24ad1360b10f03c33b91028f83fa65</anchor>
      <arglist>(const int) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceAll.html</anchorfile>
      <anchor>c52557d5280f1080c05222269c321f3c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceAll.html</anchorfile>
      <anchor>6d9e9d7a5f1e72034ecb556d23213653</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceAll.html</anchorfile>
      <anchor>e4994bdeee71db701d286424d0c2f501</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceAll.html</anchorfile>
      <anchor>14f36711df3fc5fe9c7d8db7c7ab8156</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>all_</name>
      <anchorfile>classReduceAll.html</anchorfile>
      <anchor>8f66a3b45ced05f78e3ce051c663b081</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceAny</name>
    <filename>classReduceAny.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceAny.html</anchorfile>
      <anchor>ca939058a9ec607efe2ed7ebb23ddaf7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bool</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceAny.html</anchorfile>
      <anchor>95a4fe59c854ec752b05800dc935362a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceAny.html</anchorfile>
      <anchor>f966c7bd201bbd0b89d54534afa215d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceAny</name>
      <anchorfile>classReduceAny.html</anchorfile>
      <anchor>9285ce2b0859664335fbcfae6f485321</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceAny.html</anchorfile>
      <anchor>a740eed81151a6deb08680dca5489bbf</anchor>
      <arglist>(const T_sourcetype &amp;x, const int=0) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceAny.html</anchorfile>
      <anchor>9f2c98bc7319dd6d9a4673d063440a34</anchor>
      <arglist>(const int) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceAny.html</anchorfile>
      <anchor>e3101b19490e28a0a95e95c583a81586</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceAny.html</anchorfile>
      <anchor>3166cede12fe3a60f118fa94f932c429</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceAny.html</anchorfile>
      <anchor>6687c9a352b60aa42902a6ae04b5e272</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceAny.html</anchorfile>
      <anchor>777747e0735e8b9fe81042fd5742e340</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>any_</name>
      <anchorfile>classReduceAny.html</anchorfile>
      <anchor>4d1558fa9e8d342395639157ef3e7847</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceCount</name>
    <filename>classReduceCount.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceCount.html</anchorfile>
      <anchor>53a44049c4d2c0d0ce458c62ec9a6b29</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceCount.html</anchorfile>
      <anchor>eca4c153ec33e643b9104184d7d7d240</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceCount.html</anchorfile>
      <anchor>5167d1d7427f26f792d3fa26e77f9a1a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceCount</name>
      <anchorfile>classReduceCount.html</anchorfile>
      <anchor>793bc2c350a7476c8771d71604a275b5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceCount.html</anchorfile>
      <anchor>46865e93aa79a0b72891524f9f0140be</anchor>
      <arglist>(const T_sourcetype &amp;x, const int=0) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceCount.html</anchorfile>
      <anchor>18abc83ac67083e2107fceb485e86f69</anchor>
      <arglist>(const int) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceCount.html</anchorfile>
      <anchor>db2a0a4a7510afdb3ce71dc3e1999891</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceCount.html</anchorfile>
      <anchor>41398a6d3089974241d69e6dbcd5c6ae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceCount.html</anchorfile>
      <anchor>21a0b77e29742867419fa7001472b5be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceCount.html</anchorfile>
      <anchor>b5db2bc94511faf8fc6d0f2d3d93e14e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>count_</name>
      <anchorfile>classReduceCount.html</anchorfile>
      <anchor>c07a02efbce10910a7ab991b681de1e1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceFirst</name>
    <filename>classReduceFirst.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceFirst.html</anchorfile>
      <anchor>d153fdeca330b044f1fd20d47a541356</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceFirst.html</anchorfile>
      <anchor>011cd3328393e76bf26501a6b8652d09</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceFirst.html</anchorfile>
      <anchor>2ad67486354b89d10192c554f28801eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceFirst</name>
      <anchorfile>classReduceFirst.html</anchorfile>
      <anchor>e815b668f25b980ff33f958f9fe9625d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceFirst.html</anchorfile>
      <anchor>4a21a2c13f9f81a01d7ec2f8a3f00ae3</anchor>
      <arglist>(const T_sourcetype &amp;x, const T_resulttype &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceFirst.html</anchorfile>
      <anchor>5b8b6f85cdc7c27481fe2d5be4788a25</anchor>
      <arglist>(const int) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceFirst.html</anchorfile>
      <anchor>b46913db49c2caaac0dbbac6c773375d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceFirst.html</anchorfile>
      <anchor>9b0f0388836435c4ee449b35473d3006</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceFirst.html</anchorfile>
      <anchor>9ef141fc1550aeda6bdec3316dee391d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceFirst.html</anchorfile>
      <anchor>ae4afeb680c425049a0e844babfa2f1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>index_</name>
      <anchorfile>classReduceFirst.html</anchorfile>
      <anchor>6ddd641c6f6e86511f4f0940212aeace</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceLast</name>
    <filename>classReduceLast.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceLast.html</anchorfile>
      <anchor>b31d92dccc2dc7f98a31c40f1aa10f2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceLast.html</anchorfile>
      <anchor>173360092022caa3c428ac7bdca8c9dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceLast.html</anchorfile>
      <anchor>df839b2684ce133fbf40e7e07f0e0708</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceLast</name>
      <anchorfile>classReduceLast.html</anchorfile>
      <anchor>78d8c242a9e9d830dbac414ab215aaf7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceLast.html</anchorfile>
      <anchor>a25ec0d91a9efc4fc96b741dd251c727</anchor>
      <arglist>(const T_sourcetype &amp;x, const T_resulttype &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceLast.html</anchorfile>
      <anchor>481839e1e5c4e40c6e539ed970f7cde9</anchor>
      <arglist>(const int) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceLast.html</anchorfile>
      <anchor>a32fc3c4cdc9b9be55961f48380c659f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceLast.html</anchorfile>
      <anchor>356d34f1de0675753c976729f98e5ab7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceLast.html</anchorfile>
      <anchor>cb74691ed54238b159e787f230abda16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceLast.html</anchorfile>
      <anchor>34a37c804cb9e442063488f87c317d6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>index_</name>
      <anchorfile>classReduceLast.html</anchorfile>
      <anchor>8523b605adf272f5161c59d569810420</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceMax</name>
    <filename>classReduceMax.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceMax.html</anchorfile>
      <anchor>814f56c97fb024a6ef81d22e9fd52b23</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceMax.html</anchorfile>
      <anchor>5e86077304fc95a12800e10c2059f88a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceMax.html</anchorfile>
      <anchor>e4efd4d75d2f9126d3191a2c96a43e96</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceMax</name>
      <anchorfile>classReduceMax.html</anchorfile>
      <anchor>b5f50c6b8414dd1db98760fd0c7f4f33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceMax.html</anchorfile>
      <anchor>2a5bf90043e49c260695faf81334ec00</anchor>
      <arglist>(const T_sourcetype &amp;x, const int=0) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceMax.html</anchorfile>
      <anchor>9c781b4503e30a1bd93a7a6c62ab247e</anchor>
      <arglist>(const int) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceMax.html</anchorfile>
      <anchor>da89f9bdee2779b9943b612022a1ae88</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceMax.html</anchorfile>
      <anchor>bd39784338daade53da235c5cde658b5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceMax.html</anchorfile>
      <anchor>1826b9280463d17acf648acbbf255e5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceMax.html</anchorfile>
      <anchor>e0a9af3d7e87db80b9778c0ae1c47ebe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>max_</name>
      <anchorfile>classReduceMax.html</anchorfile>
      <anchor>232fc6ca51eddc4f596d9cd6307c7c3d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceMaxIndex</name>
    <filename>classReduceMaxIndex.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceMaxIndex.html</anchorfile>
      <anchor>dfdd5e8fad286a64079e6ddcb46622e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceMaxIndex.html</anchorfile>
      <anchor>233790a71b058cce73f75ffe7523d1d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceMaxIndex.html</anchorfile>
      <anchor>00d9bc74fd8688be2adfe00c25a7cabe</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceMaxIndex</name>
      <anchorfile>classReduceMaxIndex.html</anchorfile>
      <anchor>ff4bed992518d9bbfa27c2b9382854ce</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceMaxIndex.html</anchorfile>
      <anchor>a1341a97faa7cdbbec51a8a9f806eb1f</anchor>
      <arglist>(const T_sourcetype &amp;x, const T_resulttype &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceMaxIndex.html</anchorfile>
      <anchor>6dd068a6fba43a571ab86c418697dbce</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceMaxIndex.html</anchorfile>
      <anchor>c41d4f6a5a1574964c0d94adf2ddf06b</anchor>
      <arglist>(const T_resulttype &amp;index) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceMaxIndex.html</anchorfile>
      <anchor>e4b5de4fc3d2c722976cbff65bc69f0c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceMaxIndex.html</anchorfile>
      <anchor>522b1a3857414ec84aedd65a85975a00</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceMaxIndex.html</anchorfile>
      <anchor>a2a30dd413134b68a2fab9b451777cbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_sourcetype</type>
      <name>max_</name>
      <anchorfile>classReduceMaxIndex.html</anchorfile>
      <anchor>f4a613c8c45e85f7871c111fbfa8f2e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>index_</name>
      <anchorfile>classReduceMaxIndex.html</anchorfile>
      <anchor>45f13aca0de12f5131713c560ed70c4c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceMaxIndexVector</name>
    <filename>classReduceMaxIndexVector.html</filename>
    <templarg></templarg>
    <templarg>N_rank</templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceMaxIndexVector.html</anchorfile>
      <anchor>959c30c0e834ac3a1f5c2a85e3f8521e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TinyVector&lt; int, N_rank &gt;</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceMaxIndexVector.html</anchorfile>
      <anchor>a692334e6c8dff5065b896773e77eac8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceMaxIndexVector.html</anchorfile>
      <anchor>a1139b968fabe9c7696c31579e7faab0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceMaxIndexVector</name>
      <anchorfile>classReduceMaxIndexVector.html</anchorfile>
      <anchor>38686e77f31a773dc6d88faec3ee44e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceMaxIndexVector.html</anchorfile>
      <anchor>b6ed4f228c448b7bf1827952b2ee557e</anchor>
      <arglist>(const T_sourcetype &amp;x, const T_resulttype &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceMaxIndexVector.html</anchorfile>
      <anchor>9767d0ddd5478b989d23bca83ca032b8</anchor>
      <arglist>(const int) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceMaxIndexVector.html</anchorfile>
      <anchor>ed815aa1c482079991534a2d4c4a6b29</anchor>
      <arglist>(const T_resulttype &amp;index) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceMaxIndexVector.html</anchorfile>
      <anchor>6e913c296aedb0e2b61609c28d56b45f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceMaxIndexVector.html</anchorfile>
      <anchor>51ead6990c48900812f206b5197904ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceMaxIndexVector.html</anchorfile>
      <anchor>140b9eba5b667f22ca1fa75c808d6d93</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_sourcetype</type>
      <name>max_</name>
      <anchorfile>classReduceMaxIndexVector.html</anchorfile>
      <anchor>4bc06bbd26b382063eb6bee1fa4bea4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>index_</name>
      <anchorfile>classReduceMaxIndexVector.html</anchorfile>
      <anchor>5edd3207ff03f26cddb2d0e84456e00d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceMean</name>
    <filename>classReduceMean.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceMean.html</anchorfile>
      <anchor>5764ca6260fcf90c35a516b7a5ec0fde</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>P_resulttype</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceMean.html</anchorfile>
      <anchor>6ba4ff1f0f7d4ddf9d2b2a1ed93d7812</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceMean.html</anchorfile>
      <anchor>fe8ae2f9c567033aceb0824e8ee735e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceMean</name>
      <anchorfile>classReduceMean.html</anchorfile>
      <anchor>25faac9d0a8ae09621d6bac6831dfa5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceMean.html</anchorfile>
      <anchor>e04bf2f2de3888e5574ddde70ae009c8</anchor>
      <arglist>(const T_sourcetype &amp;x, const int=0) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceMean.html</anchorfile>
      <anchor>02b6ddf4a3d9dc7131634593b334defd</anchor>
      <arglist>(const int count) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceMean.html</anchorfile>
      <anchor>eaadc52165638bc9a70eb877887cd5d4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceMean.html</anchorfile>
      <anchor>43c5f61933ee5da1abecebd7ee7b40a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceMean.html</anchorfile>
      <anchor>dafc7d37f7e62d45356634ab1453b9dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceMean.html</anchorfile>
      <anchor>210a65824fcaf29db4797b376cb9b762</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>sum_</name>
      <anchorfile>classReduceMean.html</anchorfile>
      <anchor>27a3d360fad5c0108687d90e42fa9326</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceMin</name>
    <filename>classReduceMin.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceMin.html</anchorfile>
      <anchor>7e14cd389f6cd755ec4dd2e224dcc969</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceMin.html</anchorfile>
      <anchor>80cd05c565051ac4bcfdbb85b6c4d9fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceMin.html</anchorfile>
      <anchor>28eb01a636caef7d9430a57a4f6943a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceMin</name>
      <anchorfile>classReduceMin.html</anchorfile>
      <anchor>e8ca1a261463cc1f3d4ebbc9d5d1fbf7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceMin.html</anchorfile>
      <anchor>5065aaff5ac756c2a04f6e8411d8d39a</anchor>
      <arglist>(const T_sourcetype &amp;x, const int=0) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceMin.html</anchorfile>
      <anchor>0c6745c6eb707967dbb52e5d19c2ebc9</anchor>
      <arglist>(const int) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceMin.html</anchorfile>
      <anchor>29def1e647b8a4f95c2f9af5174fd650</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceMin.html</anchorfile>
      <anchor>53442a6fefbf6211a45d9c445e89e77c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceMin.html</anchorfile>
      <anchor>a96204f893b09a800bf6633ce41a0ee4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceMin.html</anchorfile>
      <anchor>e6fa0f20d5cb51b9579b2ace68240c17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>min_</name>
      <anchorfile>classReduceMin.html</anchorfile>
      <anchor>b6ad6e8065cdff6f98c75c5ff2050852</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceMinIndex</name>
    <filename>classReduceMinIndex.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceMinIndex.html</anchorfile>
      <anchor>32f8a59b01d3624a3832598984dc4f2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceMinIndex.html</anchorfile>
      <anchor>bc233796b665428682336475b539b6cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceMinIndex.html</anchorfile>
      <anchor>ec2f7360d000099b2e6b2893cf4e7430</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceMinIndex</name>
      <anchorfile>classReduceMinIndex.html</anchorfile>
      <anchor>c43683b6d36a5b89ca387efbf6d2be5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceMinIndex.html</anchorfile>
      <anchor>4bfe1bf560faef09cd49c79475f782ee</anchor>
      <arglist>(const T_sourcetype &amp;x, const T_resulttype &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceMinIndex.html</anchorfile>
      <anchor>d8772c2177c68dbb6b7e28ed3c4eb3cc</anchor>
      <arglist>(const int) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceMinIndex.html</anchorfile>
      <anchor>50e5c15951c9e49cee63d9a07f4bd95a</anchor>
      <arglist>(const T_resulttype &amp;index) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceMinIndex.html</anchorfile>
      <anchor>c8cc03e197a63e0307d63fe9c78b558f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceMinIndex.html</anchorfile>
      <anchor>dd70aed71f94752c8ab7295a89550c4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceMinIndex.html</anchorfile>
      <anchor>44a49676c2544bcbd568f850e9098c8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_sourcetype</type>
      <name>min_</name>
      <anchorfile>classReduceMinIndex.html</anchorfile>
      <anchor>f88672c6246ca52ebcbc09963cdda02c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>index_</name>
      <anchorfile>classReduceMinIndex.html</anchorfile>
      <anchor>eca6bfa11f1aecc839b99f6e7824238b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceMinIndexVector</name>
    <filename>classReduceMinIndexVector.html</filename>
    <templarg></templarg>
    <templarg>N</templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceMinIndexVector.html</anchorfile>
      <anchor>65030b49259be23f83d7a2714e93f502</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TinyVector&lt; int, N &gt;</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceMinIndexVector.html</anchorfile>
      <anchor>2e7c894a95020e5638affc6f1c8a4e50</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceMinIndexVector.html</anchorfile>
      <anchor>f174899864203ff165812b420d848125</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceMinIndexVector</name>
      <anchorfile>classReduceMinIndexVector.html</anchorfile>
      <anchor>a14ce0a1a8046e431338b7073677fcae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceMinIndexVector.html</anchorfile>
      <anchor>625b647ad3ab920cee4ae1d7403d6462</anchor>
      <arglist>(const T_sourcetype &amp;x, const T_resulttype &amp;index) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceMinIndexVector.html</anchorfile>
      <anchor>9ba24cede82de17b49e32d5e9e22dc3a</anchor>
      <arglist>(const int) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceMinIndexVector.html</anchorfile>
      <anchor>7b03727d19b284a7788f810824d5952a</anchor>
      <arglist>(const T_resulttype &amp;index) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceMinIndexVector.html</anchorfile>
      <anchor>759deac5cc95fdf792f69e31a3ef22e3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceMinIndexVector.html</anchorfile>
      <anchor>e8d5f6b4584469fa8032a054c0fa7f3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceMinIndexVector.html</anchorfile>
      <anchor>fcd199a55a2b3b4a14dad5663b290809</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_sourcetype</type>
      <name>min_</name>
      <anchorfile>classReduceMinIndexVector.html</anchorfile>
      <anchor>4af67907330e5b438af07b9c5d39ecf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>index_</name>
      <anchorfile>classReduceMinIndexVector.html</anchorfile>
      <anchor>f49e80bf4109fc24159049c5d81cc46c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceMinMax</name>
    <filename>classReduceMinMax.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceMinMax.html</anchorfile>
      <anchor>e0d38bc22b416eefb4af7022978dba05</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>MinMaxValue&lt; P_sourcetype &gt;</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceMinMax.html</anchorfile>
      <anchor>eb7c80a5b13a78c6503326721a0e3746</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceMinMax.html</anchorfile>
      <anchor>0ea8e1377caa32fd62625dc0ac24402b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceMinMax</name>
      <anchorfile>classReduceMinMax.html</anchorfile>
      <anchor>f17cd623a56e96c32b2693b87ef76a72</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceMinMax.html</anchorfile>
      <anchor>c1366c1124565750181f6fb37f09be54</anchor>
      <arglist>(T_sourcetype x, const int=0) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceMinMax.html</anchorfile>
      <anchor>34b751eccbae30ad94535045d40971c9</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceMinMax.html</anchorfile>
      <anchor>ab4f4b81ee4e29316ed93d5edf4ed7a1</anchor>
      <arglist>(P_sourcetype initialValue) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceMinMax.html</anchorfile>
      <anchor>5837743822fb88d5d41a9a79754a14ff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceMinMax.html</anchorfile>
      <anchor>e400189790be6d3b513405ce84397dd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceMinMax.html</anchorfile>
      <anchor>c4e0d04f417071ef4571a4ace5a407bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>minmax_</name>
      <anchorfile>classReduceMinMax.html</anchorfile>
      <anchor>132f39faad4791dc8db8829516bcc2ea</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceProduct</name>
    <filename>classReduceProduct.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceProduct.html</anchorfile>
      <anchor>1d6481320a3565d8af41236e92cfd22d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>P_resulttype</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceProduct.html</anchorfile>
      <anchor>042fd3f78d9968e5534a1783758cb838</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceProduct.html</anchorfile>
      <anchor>1f98f468942c947df3e5357c0a09d10e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceProduct</name>
      <anchorfile>classReduceProduct.html</anchorfile>
      <anchor>d1838adc9eaab4138ce5ca080e0936b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceProduct.html</anchorfile>
      <anchor>26bd1fb0aedd905ec19eab74bca5bff0</anchor>
      <arglist>(const T_sourcetype &amp;x, const int=0) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceProduct.html</anchorfile>
      <anchor>bdb362ee367a090da1d03dd79ddcce94</anchor>
      <arglist>(const int) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceProduct.html</anchorfile>
      <anchor>ed43a4709c76c4d74610c4067cb5ba97</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceProduct.html</anchorfile>
      <anchor>9b45aeae03b4e9b933867f67a325a0d0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceProduct.html</anchorfile>
      <anchor>34a75451486743c6f900935a72b6a7bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceProduct.html</anchorfile>
      <anchor>e3050050c6798f8f08a77411e9b17ad3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>product_</name>
      <anchorfile>classReduceProduct.html</anchorfile>
      <anchor>30301dc530285a65fb469edaa0d75864</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ReduceSum</name>
    <filename>classReduceSum.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_sourcetype</type>
      <name>T_sourcetype</name>
      <anchorfile>classReduceSum.html</anchorfile>
      <anchor>7b69b4723eb1e1087ffad91f8573beb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>P_resulttype</type>
      <name>T_resulttype</name>
      <anchorfile>classReduceSum.html</anchorfile>
      <anchor>2d3d58d67dfb475db90aad9fe0c66bf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_resulttype</type>
      <name>T_numtype</name>
      <anchorfile>classReduceSum.html</anchorfile>
      <anchor>0e862930f1f359e5d61b56501ad4a9b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ReduceSum</name>
      <anchorfile>classReduceSum.html</anchorfile>
      <anchor>e27d9a857e8f419be2c8bdf6fca0f6a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classReduceSum.html</anchorfile>
      <anchor>cabad17e6d13e8f0792a4fdbf61e37b9</anchor>
      <arglist>(const T_sourcetype &amp;x, const int=0) const </arglist>
    </member>
    <member kind="function">
      <type>T_resulttype</type>
      <name>result</name>
      <anchorfile>classReduceSum.html</anchorfile>
      <anchor>b8cc2fcb57ade7b1d9793982a89c927e</anchor>
      <arglist>(const int) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classReduceSum.html</anchorfile>
      <anchor>0bed7ffd03d4c721e183fa2eb804f3ca</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>name</name>
      <anchorfile>classReduceSum.html</anchorfile>
      <anchor>0314a5be9b2f90a5f9af3b42f5463a4c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needIndex</name>
      <anchorfile>classReduceSum.html</anchorfile>
      <anchor>e3451086ae3616fb05793984015788f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const bool</type>
      <name>needInit</name>
      <anchorfile>classReduceSum.html</anchorfile>
      <anchor>9e195dbc187e5bfde5a1163c3ab04124</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T_resulttype</type>
      <name>sum_</name>
      <anchorfile>classReduceSum.html</anchorfile>
      <anchor>376d084caf4136d445dbf36f60132dbc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RowMajor</name>
    <filename>classRowMajor.html</filename>
    <base>GeneralMatrix</base>
    <member kind="typedef">
      <type>RowMajorIterator</type>
      <name>T_iterator</name>
      <anchorfile>classRowMajor.html</anchorfile>
      <anchor>b2fbe61409740e91b674de66e515b05f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RowMajor</name>
      <anchorfile>classRowMajor.html</anchorfile>
      <anchor>b7b36460eddb20cadb1032f5e967634e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RowMajor</name>
      <anchorfile>classRowMajor.html</anchorfile>
      <anchor>f17428a09d00116660012d37f81a8f84</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>coordToOffset</name>
      <anchorfile>classRowMajor.html</anchorfile>
      <anchor>304ac9f90e2ba8be95875a2f55cb0364</anchor>
      <arglist>(unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>get</name>
      <anchorfile>classRowMajor.html</anchorfile>
      <anchor>00cfe5659d412ec8de353508bc83b983</anchor>
      <arglist>(const T_numtype *restrict data, unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>get</name>
      <anchorfile>classRowMajor.html</anchorfile>
      <anchor>66e986fc1b3c6548a948f53ab321b1e9</anchor>
      <arglist>(T_numtype *restrict data, unsigned i, unsigned j)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RowMajorIterator</name>
    <filename>classRowMajorIterator.html</filename>
    <base>GeneralIterator</base>
    <member kind="function">
      <type></type>
      <name>RowMajorIterator</name>
      <anchorfile>classRowMajorIterator.html</anchorfile>
      <anchor>c9e619d5990b8b774dfd3aac2f1eac79</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator++</name>
      <anchorfile>classRowMajorIterator.html</anchorfile>
      <anchor>e2e6fbbb21abf85f9290e8e016c5c291</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>sharedState</name>
    <filename>structsharedState.html</filename>
  </compound>
  <compound kind="struct">
    <name>ShiftLeft</name>
    <filename>structShiftLeft.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type>typedef</type>
      <name>BZ_PROMOTE</name>
      <anchorfile>structShiftLeft.html</anchorfile>
      <anchor>63330baf8c71796efda2651491f32a9b</anchor>
      <arglist>(T_numtype1, T_numtype2) T_numtype</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structShiftLeft.html</anchorfile>
      <anchor>6fa1f410108f13baaef961ca28e5712b</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structShiftLeft.html</anchorfile>
      <anchor>fd5d6272df3ca07a56de7c8b1823c0f5</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ShiftRight</name>
    <filename>structShiftRight.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type>typedef</type>
      <name>BZ_PROMOTE</name>
      <anchorfile>structShiftRight.html</anchorfile>
      <anchor>60a147ec090129b8431c3daa3becb417</anchor>
      <arglist>(T_numtype1, T_numtype2) T_numtype</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structShiftRight.html</anchorfile>
      <anchor>702161135ff0df0947f3bc9d27058905</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structShiftRight.html</anchorfile>
      <anchor>60e864c75842b91e8c91f6bd7dcd0e33</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Subtract</name>
    <filename>structSubtract.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type>typedef</type>
      <name>BZ_PROMOTE</name>
      <anchorfile>structSubtract.html</anchorfile>
      <anchor>60421a0b5887ec44b19836901825a983</anchor>
      <arglist>(T_numtype1, T_numtype2) T_numtype</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structSubtract.html</anchorfile>
      <anchor>95e87cd27b2ab658525c819f77901e34</anchor>
      <arglist>(T_numtype1 a, T_numtype2 b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structSubtract.html</anchorfile>
      <anchor>45f27fc5a454172d1ac10060f4dc348d</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1, const T2 &amp;t2)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Symmetric</name>
    <filename>classSymmetric.html</filename>
    <base>MatrixStructure</base>
    <member kind="typedef">
      <type>SymmetricIterator</type>
      <name>T_iterator</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>50668bff9c5fc0f47e71a3998d65571a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Symmetric</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>3a75cf3d92f34a1a17a72b6ca8fd1938</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Symmetric</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>2310deb51bb0329cd0f792ca2e73c6b0</anchor>
      <arglist>(unsigned size)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Symmetric</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>732b3a10ee998bcebd0c8a21276b0803</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>columns</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>a32827b7f886c179a8e68320cc71aae7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>coordToOffset</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>317439104ac975dcf99daaab1994a243</anchor>
      <arglist>(unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>firstInRow</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>485ee108918878fb7fd5048474816edc</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>get</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>e29b3bd0d57ee61ba7cd8e643e6e3df8</anchor>
      <arglist>(const T_numtype *restrict data, unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>get</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>e5773f263366c9d11e25932680afff00</anchor>
      <arglist>(T_numtype *restrict data, unsigned i, unsigned j)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>lastInRow</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>0af7363986c09cfaa4c7396b76961c5a</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>firstInCol</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>7d89ac90e5ea60d6901e8dfbd4c1c545</anchor>
      <arglist>(unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>lastInCol</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>e49f2e22c7bf230d40b0cb234179254d</anchor>
      <arglist>(unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>inRange</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>cbc1fe24d3b1b98292a1657418d3be2a</anchor>
      <arglist>(unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>numElements</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>6d3c74c6c5972dec02de77af1adec283</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>rows</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>f24860e540144cb11f035fa1b156cafe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>7bca6e76a758b5b5d2c88f856e1acb09</anchor>
      <arglist>(unsigned size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>43a484370563ad12bcd3e593cd41ddff</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned</type>
      <name>size_</name>
      <anchorfile>classSymmetric.html</anchorfile>
      <anchor>1932ed2c562064e40c2a1d93612e3c6d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SymmetricIterator</name>
    <filename>classSymmetricIterator.html</filename>
    <member kind="function">
      <type></type>
      <name>SymmetricIterator</name>
      <anchorfile>classSymmetricIterator.html</anchorfile>
      <anchor>4a971b769c786a33bfd232d0ddc4c2f3</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>classSymmetricIterator.html</anchorfile>
      <anchor>92b93ce1b9d57e22daf368fa3fac5229</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator++</name>
      <anchorfile>classSymmetricIterator.html</anchorfile>
      <anchor>15df0301b7441940924c1bfe3fa3b174</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>row</name>
      <anchorfile>classSymmetricIterator.html</anchorfile>
      <anchor>c0960c71e1d65e41ba6734abcc899d67</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>col</name>
      <anchorfile>classSymmetricIterator.html</anchorfile>
      <anchor>c8d6d51aa7730fc2e2758618150216e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>offset</name>
      <anchorfile>classSymmetricIterator.html</anchorfile>
      <anchor>0b295d3cae80c7da110705b63d84c30c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>size_</name>
      <anchorfile>classSymmetricIterator.html</anchorfile>
      <anchor>f20fec83b924fece2f18e16e64d1d158</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>good_</name>
      <anchorfile>classSymmetricIterator.html</anchorfile>
      <anchor>7834372e8d347ba7c7889b5237fc5f90</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>offset_</name>
      <anchorfile>classSymmetricIterator.html</anchorfile>
      <anchor>5816a2db16fb9fb1067d83f5fa35baa4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>i_</name>
      <anchorfile>classSymmetricIterator.html</anchorfile>
      <anchor>c592bd5ebb045c0ef23511d26f89fefe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>j_</name>
      <anchorfile>classSymmetricIterator.html</anchorfile>
      <anchor>51d98d28b3de3b6719c74960a151d3a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TinyVector</name>
    <filename>classTinyVector.html</filename>
    <templarg>P_numtype</templarg>
    <templarg>N_length</templarg>
    <member kind="enumvalue">
      <name>numElements</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>ff7deffb9cf7dad6b7a20524c7a76fc21f76817120f91910580eea984b03f1c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>P_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>b8e7df758dd5a369e92b3cb54a48bdbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TinyVector&lt; T_numtype, N_length &gt;</type>
      <name>T_vector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>ea08e4463006acf6842a93c026b27094</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TinyVectorIter&lt; T_numtype, N_length, 1 &gt;</type>
      <name>T_iterator</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>6044134b6f2401fe4e2d73bd7dfa25c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TinyVectorIterConst&lt; T_numtype, N_length, 1 &gt;</type>
      <name>T_constIterator</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>f420f8f49beb7efac60ac22a5d1f2e84</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T_numtype *</type>
      <name>iterator</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>7e1e065c0b894add536ab278dfe28202</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>const T_numtype *</type>
      <name>const_iterator</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>58fc9319708794276cdad6399cf03eed</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>dab8554f53e1a366ecb89ee21a296c0b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>7274fce49f2067df72f2306015284032</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>7d6f6a1f5ea0e2de3c8244d91b13d3b2</anchor>
      <arglist>(const TinyVector&lt; T_numtype, N_length &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>97aad16a01092e6f5b3c92423ecb5691</anchor>
      <arglist>(const TinyVector&lt; T_numtype2, N_length &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>78911596eae6bf0ea81094cd7c6598f0</anchor>
      <arglist>(const T_numtype initValue)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>56ab707986f243178d588671b9f5930e</anchor>
      <arglist>(const T_numtype x[])</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>c32907fd075ee37dd7a6d83d92d6f647</anchor>
      <arglist>(T_numtype x0, T_numtype x1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>db3681f289aeb468ec00ff9d79911aac</anchor>
      <arglist>(T_numtype x0, T_numtype x1, T_numtype x2)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>9047e96db706520df0e035175e6f0e43</anchor>
      <arglist>(T_numtype x0, T_numtype x1, T_numtype x2, T_numtype x3)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>43a71ef3b2d02940758258cbf4d7f551</anchor>
      <arglist>(T_numtype x0, T_numtype x1, T_numtype x2, T_numtype x3, T_numtype x4)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>15a83eb8e298b11a8ffd8527237f4f15</anchor>
      <arglist>(T_numtype x0, T_numtype x1, T_numtype x2, T_numtype x3, T_numtype x4, T_numtype x5)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>38c7b4b809579f339d8caf2ea97e2dd3</anchor>
      <arglist>(T_numtype x0, T_numtype x1, T_numtype x2, T_numtype x3, T_numtype x4, T_numtype x5, T_numtype x6)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>44f3022b29cd00455619f8f4aab10c7b</anchor>
      <arglist>(T_numtype x0, T_numtype x1, T_numtype x2, T_numtype x3, T_numtype x4, T_numtype x5, T_numtype x6, T_numtype x7)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>e962519d56e0cf088b5ed6573dcc146e</anchor>
      <arglist>(T_numtype x0, T_numtype x1, T_numtype x2, T_numtype x3, T_numtype x4, T_numtype x5, T_numtype x6, T_numtype x7, T_numtype x8)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>1be98043aeed2c1da5185894c9f96061</anchor>
      <arglist>(T_numtype x0, T_numtype x1, T_numtype x2, T_numtype x3, T_numtype x4, T_numtype x5, T_numtype x6, T_numtype x7, T_numtype x8, T_numtype x9)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>3bd02ef633d40144fea0170ae888bebf</anchor>
      <arglist>(T_numtype x0, T_numtype x1, T_numtype x2, T_numtype x3, T_numtype x4, T_numtype x5, T_numtype x6, T_numtype x7, T_numtype x8, T_numtype x9, T_numtype x10)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVector</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>4da46f3f3b30eb459985cc288ad46314</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt; expr)</arglist>
    </member>
    <member kind="function">
      <type>T_iterator</type>
      <name>beginFast</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>b0f3a27787c2cca5572248c2102459c4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T_constIterator</type>
      <name>beginFast</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>c0fc61c75970f50e4721a06b0e660bdb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>515d02738c299b0006140995286916f6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>c34147e11e5db228d3f64b98017c6ada</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>end</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>ffa6a71dd63c4c6d2150bf62dcd23ad1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>end</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>276faa465ad7117075894cb9238a9806</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype *restrict</type>
      <name>data</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>949614e43ea6613a98c4aa740011646c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype *restrict</type>
      <name>data</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>aeeb5c4302e27750a01d45565ac4a18d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype *restrict</type>
      <name>dataFirst</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>4ef46ae2f363fcdddd2d84b7c3f85ca1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype *restrict</type>
      <name>dataFirst</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>a6c883a683a95500d270f0985c06ece3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>length</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>1ebd93b754246952a79a40c49aa48189</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>_bz_suggestLength</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>ab4c79393a3ce6d92194f0025873c4c9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_bz_hasFastAccess</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>8fc28407c661a712a06f45491712e377</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>eed741a4369651e69de924658a66286f</anchor>
      <arglist>(unsigned i)</arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>3ea5a8e93b3b320512c69ae1ca2c5733</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_bz_assign</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>4fe317ca3e1bad01a5d9f88d60bf7326</anchor>
      <arglist>(P_expr, P_updater)</arglist>
    </member>
    <member kind="function">
      <type>_bz_VecExpr&lt; T_constIterator &gt;</type>
      <name>_bz_asVecExpr</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>e76d1dbf3163bd47a74c69c2f457d447</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>lengthCheck</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>afeb9ba1e759621c78b9d7b8babadeed</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;</type>
      <name>operator()</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>cc9fe7abc20a6b454bea94a75e817268</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>7be55be0cebe8a873660a693daeb67ce</anchor>
      <arglist>(unsigned i)</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype &amp;</type>
      <name>operator[]</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>f35728f73013791f3726f80eb695cd35</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator[]</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>f42df933d8dca5898274c89a24f5143b</anchor>
      <arglist>(unsigned i)</arglist>
    </member>
    <member kind="function">
      <type>ListInitializationSwitch&lt; T_vector, T_numtype * &gt;</type>
      <name>operator=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>5aaae7f752e6da93a07c03e27cbbed72</anchor>
      <arglist>(T_numtype x)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>initialize</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>38407575837cfacf14c4351b643f4ac2</anchor>
      <arglist>(const T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator+=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>24da928694f0b6dcd65e3d3d72b50111</anchor>
      <arglist>(const T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator-=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>e5ca3cd2d70b8d54c52f2892c4a99feb</anchor>
      <arglist>(const T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator*=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>a0681f9f8028d82559b544141565d398</anchor>
      <arglist>(const T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator/=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>91b12f1f85119bb466f53093b1cbb2fb</anchor>
      <arglist>(const T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator%=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>4357b3ca446de44720f2b8669b0c9ca7</anchor>
      <arglist>(const T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator^=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>dee58a6ddd71deb0b598809a118c9488</anchor>
      <arglist>(const T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>8e15aead56bf308c03343312b150accc</anchor>
      <arglist>(const T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator|=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>9f9260828dd2bbd8ea82c5ba259f9208</anchor>
      <arglist>(const T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>f0bd8cdb4fcd2c38a6b64cc2c7c09a65</anchor>
      <arglist>(const int)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>c6932dcca764e901b60ba5883235a496</anchor>
      <arglist>(const int)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>02c0a0ae9aedddd96a982d217a043e15</anchor>
      <arglist>(const TinyVector&lt; P_numtype2, N_length &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator+=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>1fe4f1bbde3a40d1bb8e5d6d83935c02</anchor>
      <arglist>(const TinyVector&lt; P_numtype2, N_length &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator-=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>91b6952f4f1d30dbb83555a9e2ace0ba</anchor>
      <arglist>(const TinyVector&lt; P_numtype2, N_length &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator*=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>f0aa14611dae01d045eb220fb7bb7ab0</anchor>
      <arglist>(const TinyVector&lt; P_numtype2, N_length &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator/=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>dd653e29502b3272a09bc05c9104abce</anchor>
      <arglist>(const TinyVector&lt; P_numtype2, N_length &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator%=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>74dcf1a15a6e679fb44f9bdb5c9b394a</anchor>
      <arglist>(const TinyVector&lt; P_numtype2, N_length &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator^=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>89e850a8680564fe6c140fe47c1b8db8</anchor>
      <arglist>(const TinyVector&lt; P_numtype2, N_length &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>8dd9da37b3c55f92611e13ee4f3904a3</anchor>
      <arglist>(const TinyVector&lt; P_numtype2, N_length &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator|=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>697535f11fa3494591662b4ac7762071</anchor>
      <arglist>(const TinyVector&lt; P_numtype2, N_length &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>7eddfad74b51cc09e05a3edb7a1c87a5</anchor>
      <arglist>(const TinyVector&lt; P_numtype2, N_length &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>47ba940ab0810904df9bddc82c2c317f</anchor>
      <arglist>(const TinyVector&lt; P_numtype2, N_length &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>5a5b78dfdebcd758f58ca26f7953aa74</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator+=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>75e6cac3776fbb650e72e24ca6c724c2</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator-=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>bd80b68d4cb9f7beb6680b5bbf6464de</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator*=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>3e3ee84ede9f1134b3511c2d6e2a83d5</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator/=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>83d3cef5626a9ca829e4ab061a3e23d1</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator%=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>698c7baa68ee42b7a4ad1d6424bb7e67</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator^=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>f8cb3c0ccee02ec9a9638f2d869b2f34</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>9ed97a4aebf488e5893e3e8b4236d047</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator|=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>a1c6ae63e2df7ef452d7d87332fa6b75</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>affbc5d32cdba75cab69b203a9faed87</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>7b59fe73ca3cf4540cf993d8e3384d25</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>28a1b9be54797320eb197ae2755b0c17</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator+=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>20a02ec6db4828e30fdb78b1d5526c9b</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator-=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>abfe7efcac4a682db1cb72f977a2f215</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator*=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>78b32e3ec58e5cab6c30788433a19709</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator/=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>ff1b4ad685e472854b80cccc3e844c20</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator%=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>e9ec4f04f07920e0d3eda1e662d5adc5</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator^=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>4eb16ea67b0219f2081a37fed752fc3c</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>54bd96deedf4ee0be0fc0cd991db15ef</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator|=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>9c6add14d22c68858734a8cfb3c7a955</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>3582743002bddcb87f721d45cccc77a8</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>f5ee72fb347339bc7350073119dca3e8</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>5eb42bb2a5fd644e954ef41d1d07fba0</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator+=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>4ba89f404af2943e75cdb44b8811b2ba</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator-=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>fdd229dbba778cd882bb8284f7cb4d68</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator*=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>d71649a22ec45a90585719c4343f4c5b</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator/=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>1db14a796092de3bb2320d5d67a7ca3d</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator%=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>19823e4991614b1a900ab755b806cbc0</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator^=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>574bea93fbc59f899426b2b934fc89fd</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>5fcd89e7cd857b1073fbcf4467966c58</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator|=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>231e62a7cac93c51e8eae3985984363a</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>75a3ca1d2641029d91825a9cbb5bed28</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>6476d45e3737c169bd6ba35a5adaa89d</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>75f632a15456444fd91cbeff834ecb32</anchor>
      <arglist>(const Range &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator+=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>b80965becca69273cb5c9a1d6f970eef</anchor>
      <arglist>(const Range &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator-=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>09228379bbd00aacb52449291e58f7d2</anchor>
      <arglist>(const Range &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator*=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>7da868412b3e5a3964dd00bfa286b986</anchor>
      <arglist>(const Range &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator/=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>f452d1f580c1182544749efc2163eb17</anchor>
      <arglist>(const Range &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator%=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>233031cb177cbebccb8dd8e83e276dc2</anchor>
      <arglist>(const Range &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator^=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>97f2f281fa88e4bfbd956a8135554112</anchor>
      <arglist>(const Range &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>2453f8a6856c66e8fc87029fd611c47e</anchor>
      <arglist>(const Range &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator|=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>9b5d8529e68520bfbf976eff1e8c7d16</anchor>
      <arglist>(const Range &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>573738f38e6845def278596b5dc157fd</anchor>
      <arglist>(const Range &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>3fe6a196771ab43406af9f7f41ce9db5</anchor>
      <arglist>(const Range &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_numtype *restrict</type>
      <name>getInitializationIterator</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>87fb14363e0cfedd906471832be9d69a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T_numtype</type>
      <name>data_</name>
      <anchorfile>classTinyVector.html</anchorfile>
      <anchor>cea86df73f692f8cf4fea1ae259a8b86</anchor>
      <arglist>[N_length]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TinyVector&lt; T, 0 &gt;</name>
    <filename>classTinyVector_3_01T_00_010_01_4.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>TinyVectorIter</name>
    <filename>classTinyVectorIter.html</filename>
    <templarg>P_numtype</templarg>
    <templarg>N_length</templarg>
    <templarg>N_stride</templarg>
    <member kind="typedef">
      <type>P_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>b04e0c7e17b2742a45a7d52e8d5c6642</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVectorIter</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>2497ddbd5debcbae967c04bf30a1e283</anchor>
      <arglist>(TinyVector&lt; T_numtype, N_length &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator[]</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>b437586230654bb1c1a5f71fe4e32431</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator[]</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>872554f9032c7126ded34dee29be98e7</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator()</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>4a5ddd2ce17fdd9b5883f61102d584b7</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>a89d5f9b28d705c8d3af950a7a874ae4</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>length</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>45d0185f2bfc4b7918eafe8d95984105</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_bz_hasFastAccess</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>ee7dbcdb52fa6df7a69fd646d4adf166</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>f31e154d18372fe52966ae6197a18f64</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>2af3e6100212b2d99f127f462185cd7b</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>_bz_suggestLength</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>75287da4d8a0c8f2f8d5037346f47706</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_staticLengthCount</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>7ecabfc445498738260e7a44efaaebfb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_dynamicLengthCount</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>7b38e0a69de061e32134e85d97942f08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_staticLength</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>b558e5d5a64b58c06b0e9a9f91cef920</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T_numtype *restrict</type>
      <name>data_</name>
      <anchorfile>classTinyVectorIter.html</anchorfile>
      <anchor>518d480973f872845e2c3d68a9321f4d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TinyVectorIterConst</name>
    <filename>classTinyVectorIterConst.html</filename>
    <templarg>P_numtype</templarg>
    <templarg>N_length</templarg>
    <templarg>N_stride</templarg>
    <member kind="typedef">
      <type>P_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classTinyVectorIterConst.html</anchorfile>
      <anchor>f6c906e88c1735d57e65accb54aba68f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TinyVectorIterConst</name>
      <anchorfile>classTinyVectorIterConst.html</anchorfile>
      <anchor>5eaa24b1d5797df71208420acb86fb51</anchor>
      <arglist>(const TinyVector&lt; T_numtype, N_length &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator[]</name>
      <anchorfile>classTinyVectorIterConst.html</anchorfile>
      <anchor>add834f05142ed9ef7c77254bc48fb33</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator()</name>
      <anchorfile>classTinyVectorIterConst.html</anchorfile>
      <anchor>698b6ff2291c7e8d6e6b25f2f60789ce</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>length</name>
      <anchorfile>classTinyVectorIterConst.html</anchorfile>
      <anchor>5eae9b7c537d5c9d572bb41de280c134</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_bz_hasFastAccess</name>
      <anchorfile>classTinyVectorIterConst.html</anchorfile>
      <anchor>eb26b3a598792679a7781f70e9c10383</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classTinyVectorIterConst.html</anchorfile>
      <anchor>55acfe5a6f080a899ca202afcbf9ce17</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>_bz_suggestLength</name>
      <anchorfile>classTinyVectorIterConst.html</anchorfile>
      <anchor>88642c744ca2cdc3f9c399ba956a9add</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_staticLengthCount</name>
      <anchorfile>classTinyVectorIterConst.html</anchorfile>
      <anchor>2a56fae035a5f29da7aa981c45c95f7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_dynamicLengthCount</name>
      <anchorfile>classTinyVectorIterConst.html</anchorfile>
      <anchor>7bc88d76f2039bc2c13b604d064f365f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_staticLength</name>
      <anchorfile>classTinyVectorIterConst.html</anchorfile>
      <anchor>37866ca03b6d6623c246f2fc39fa3d61</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const T_numtype *restrict</type>
      <name>data_</name>
      <anchorfile>classTinyVectorIterConst.html</anchorfile>
      <anchor>618cfece210748805bd3682c52df2919</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Toeplitz</name>
    <filename>classToeplitz.html</filename>
    <base>GeneralMatrix</base>
    <member kind="typedef">
      <type>ToeplitzIterator</type>
      <name>T_iterator</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>8bbcba842f8424d8ab8a8d9258c2d734</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Toeplitz</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>dcd641820af0f7eda830ad0c3ef29783</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Toeplitz</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>ae835df39101e2975774a47b2305f0cb</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>columns</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>d76fb460e5e677bbca481757b5909ebb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>coordToOffset</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>faeb1e3af5241111d77767dc4f731c31</anchor>
      <arglist>(unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>firstInRow</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>554331d69afc95b27afef4413c755cc3</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>get</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>cd923025bfd439b1fc3818bdb2e55679</anchor>
      <arglist>(const T_numtype *restrict data, unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>get</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>64d53c05768e91d03af5950af2f9abef</anchor>
      <arglist>(T_numtype *restrict data, unsigned i, unsigned j)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>lastInRow</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>c9b6c539f5e5a5aade13a3ec6ac5aae4</anchor>
      <arglist>(const unsigned) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>firstInCol</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>7d2133049c2c3c8172b1973f110cdfaa</anchor>
      <arglist>(const unsigned) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>lastInCol</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>a22125c68c707689a76a880a08e7a06e</anchor>
      <arglist>(const unsigned) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>inRange</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>d2ada75c98ddbae673e1d1fcc4aa4648</anchor>
      <arglist>(const unsigned i, const unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>numElements</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>407e71d69eebae34c712b9d31d3b444f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>rows</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>78fc701939ace48cdfa2bd5cb38ffb6b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>63194df7034619f81655051cfe1891d6</anchor>
      <arglist>(const unsigned rows, const unsigned cols)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned</type>
      <name>rows_</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>11098bc9497283ee251795600e2846c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned</type>
      <name>cols_</name>
      <anchorfile>classToeplitz.html</anchorfile>
      <anchor>3ac4094635858de8c9995da0c5ec85db</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ToeplitzIterator</name>
    <filename>classToeplitzIterator.html</filename>
    <member kind="function">
      <type></type>
      <name>ToeplitzIterator</name>
      <anchorfile>classToeplitzIterator.html</anchorfile>
      <anchor>e8e8cf5aebb1d18154f9a0f51ea76004</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>classToeplitzIterator.html</anchorfile>
      <anchor>36f3ded21500ef7a0df2a480f667aea7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator++</name>
      <anchorfile>classToeplitzIterator.html</anchorfile>
      <anchor>6f2b3f41c1633769277997bce0f90fb9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>row</name>
      <anchorfile>classToeplitzIterator.html</anchorfile>
      <anchor>737a799a6b3190e2b052af2e50a4f6d5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>col</name>
      <anchorfile>classToeplitzIterator.html</anchorfile>
      <anchor>c0af06a9ab9bd4e208f1d6c62875061f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>offset</name>
      <anchorfile>classToeplitzIterator.html</anchorfile>
      <anchor>34529860401fa5183e64189223b78279</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>offset_</name>
      <anchorfile>classToeplitzIterator.html</anchorfile>
      <anchor>d334e0b9de29ed027b35f5d096bb8e98</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>i_</name>
      <anchorfile>classToeplitzIterator.html</anchorfile>
      <anchor>3c3e35c4e0163b9dbd6c3d8b0e318c77</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>j_</name>
      <anchorfile>classToeplitzIterator.html</anchorfile>
      <anchor>88bdb00dbd25f207efca52fbb373c637</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>rows_</name>
      <anchorfile>classToeplitzIterator.html</anchorfile>
      <anchor>cc1568fc4b29f056d4e59176e351c790</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>cols_</name>
      <anchorfile>classToeplitzIterator.html</anchorfile>
      <anchor>0ee7bbef9e883cd666b1e3e4c2f82097</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>good_</name>
      <anchorfile>classToeplitzIterator.html</anchorfile>
      <anchor>fe73d7874f9af9ba2b78399a51c6d5ad</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TT800</name>
    <filename>classTT800.html</filename>
    <member kind="typedef">
      <type>double</type>
      <name>T_numtype</name>
      <anchorfile>classTT800.html</anchorfile>
      <anchor>950711e6ab4f527c9dab0367d70afbbd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TT800</name>
      <anchorfile>classTT800.html</anchorfile>
      <anchor>b118d03ad53ee001db8dddc54f230c0b</anchor>
      <arglist>(double low=0.0, double high=1.0, double=0.0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>randomize</name>
      <anchorfile>classTT800.html</anchorfile>
      <anchor>f3585e927714dcc8f6b28635ed64546b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned long</type>
      <name>randomUint32</name>
      <anchorfile>classTT800.html</anchorfile>
      <anchor>344d896ee88ab49f489875ecd04fc8b6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>random</name>
      <anchorfile>classTT800.html</anchorfile>
      <anchor>11166195e15b9a03607430ad3ed98d73</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>generate</name>
      <anchorfile>classTT800.html</anchorfile>
      <anchor>0df537eafc530cd5f05a41829e22c212</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="enumvalue">
      <name>N</name>
      <anchorfile>classTT800.html</anchorfile>
      <anchor>611c9c291004270b0b778e0597489dcc05528a326759518e041444af9c16f2ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>M</name>
      <anchorfile>classTT800.html</anchorfile>
      <anchor>611c9c291004270b0b778e0597489dccb6db503fa99902f1c43857629c9122de</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>low_</name>
      <anchorfile>classTT800.html</anchorfile>
      <anchor>d9e7ea1bc086a7fc46bb2298fe5a99db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>length_</name>
      <anchorfile>classTT800.html</anchorfile>
      <anchor>3e76ffd6742bae27fbc29c9bef746b13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>f</name>
      <anchorfile>classTT800.html</anchorfile>
      <anchor>6548eadc11d425f59e25cbf544826a91</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>k</name>
      <anchorfile>classTT800.html</anchorfile>
      <anchor>c58cd93b94375f8b57a36916622603f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned long</type>
      <name>x</name>
      <anchorfile>classTT800.html</anchorfile>
      <anchor>0583650ebc2c150d0413fd26f42494b4</anchor>
      <arglist>[N]</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned long</type>
      <name>mag01</name>
      <anchorfile>classTT800.html</anchorfile>
      <anchor>319f708cc360b5c24302c3a8c54d0e2a</anchor>
      <arglist>[2]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>UnaryMinus</name>
    <filename>structUnaryMinus.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>T_numtype1</type>
      <name>T_numtype</name>
      <anchorfile>structUnaryMinus.html</anchorfile>
      <anchor>364322f473533b7311d65464a7f8d9d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structUnaryMinus.html</anchorfile>
      <anchor>3a109179d44fcb962f3ddc0a4afb5b38</anchor>
      <arglist>(T_numtype1 a)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structUnaryMinus.html</anchorfile>
      <anchor>bc01046d12e1e5328fdbe614b0ceeefe</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>UnaryPlus</name>
    <filename>structUnaryPlus.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>T_numtype1</type>
      <name>T_numtype</name>
      <anchorfile>structUnaryPlus.html</anchorfile>
      <anchor>e6083f57706fe1ffb13dd34bc04dc8ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype</type>
      <name>apply</name>
      <anchorfile>structUnaryPlus.html</anchorfile>
      <anchor>cdfce45dac0500fcb4a44804d1a20192</anchor>
      <arglist>(T_numtype1 a)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>prettyPrint</name>
      <anchorfile>structUnaryPlus.html</anchorfile>
      <anchor>8d6d0fe0ab111ab0d60a0f53a30dc533</anchor>
      <arglist>(BZ_STD_SCOPE(string)&amp;str, prettyPrintFormat &amp;format, const T1 &amp;t1)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Uniform</name>
    <filename>classUniform.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <base>UniformClosedOpen&lt; T, IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>double</type>
      <name>T_numtype</name>
      <anchorfile>classUniform.html</anchorfile>
      <anchor>b647bc4212bf1e95a211641535c7bc64</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Uniform</name>
      <anchorfile>classUniform.html</anchorfile>
      <anchor>770b0b81ced4759e56bce6b6b26e7704</anchor>
      <arglist>(double low=0.0, double high=1.0, double=0.0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>randomize</name>
      <anchorfile>classUniform.html</anchorfile>
      <anchor>1ea34aafbdc5acb34f59337b8737a005</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>random</name>
      <anchorfile>classUniform.html</anchorfile>
      <anchor>1b09caaf1357fbd704a33bab43be1457</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator double</name>
      <anchorfile>classUniform.html</anchorfile>
      <anchor>0877ce58f5e71cf8cef715511aab564f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Uniform</name>
      <anchorfile>classUniform.html</anchorfile>
      <anchor>9689d3a751ca7fcd46e31f465bfd20fe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Uniform</name>
      <anchorfile>classUniform.html</anchorfile>
      <anchor>b0316b976076286b1d27a98e42eaa46c</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>low_</name>
      <anchorfile>classUniform.html</anchorfile>
      <anchor>bc35bae3106921225807600fa775ca71</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>length_</name>
      <anchorfile>classUniform.html</anchorfile>
      <anchor>313053279aca4c7c45b6bf28f12a5929</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>seed</name>
      <anchorfile>classUniform.html</anchorfile>
      <anchor>b0197eae880ae09ec28a589cb2c48916</anchor>
      <arglist>[4]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UniformClosed</name>
    <filename>classUniformClosed.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>UniformClosed&lt; double, IRNG, stateTag &gt;</name>
    <filename>classUniformClosed_3_01double_00_01IRNG_00_01stateTag_01_4.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base>IRNGWrapper&lt; IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>double</type>
      <name>T_numtype</name>
      <anchorfile>classUniformClosed_3_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>e1d3a5c787c237e25f0a8db6b0fce77a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformClosed</name>
      <anchorfile>classUniformClosed_3_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>640a7cba7fc75f362a2edf5c425e7d93</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformClosed</name>
      <anchorfile>classUniformClosed_3_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>72c72793eedcd40e9e3cd116fd461ea3</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>random</name>
      <anchorfile>classUniformClosed_3_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>f7e5f861b9c5d8b1a1328329891c9866</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getUniform</name>
      <anchorfile>classUniformClosed_3_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>7189e27fcc7e911766fcea52145eb9ce</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UniformClosed&lt; float, IRNG, stateTag &gt;</name>
    <filename>classUniformClosed_3_01float_00_01IRNG_00_01stateTag_01_4.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base>IRNGWrapper&lt; IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>float</type>
      <name>T_numtype</name>
      <anchorfile>classUniformClosed_3_01float_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>57148eced89a33396b982d7edb26946e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformClosed</name>
      <anchorfile>classUniformClosed_3_01float_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>aad9385ba700808474f266c7625a26ac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformClosed</name>
      <anchorfile>classUniformClosed_3_01float_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>fa0285df5389b44001509fa72fd13543</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>random</name>
      <anchorfile>classUniformClosed_3_01float_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>03f0b57f0ab0d1443a8fdd2bda4a1c9b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>getUniform</name>
      <anchorfile>classUniformClosed_3_01float_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>2ef0189b831ebaae8396f4fc63c2a4c2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UniformClosed&lt; long double, IRNG, stateTag &gt;</name>
    <filename>classUniformClosed_3_01long_01double_00_01IRNG_00_01stateTag_01_4.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base>IRNGWrapper&lt; IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>long double</type>
      <name>T_numtype</name>
      <anchorfile>classUniformClosed_3_01long_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>41e7bce23a081c0cfe716228e6e7a553</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformClosed</name>
      <anchorfile>classUniformClosed_3_01long_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>ef08e4ed1b58358dcb46e8a1aafb8a8f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformClosed</name>
      <anchorfile>classUniformClosed_3_01long_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>c8743ba6c5dc6f7abc203ab16249217e</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>long double</type>
      <name>random</name>
      <anchorfile>classUniformClosed_3_01long_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>8d1571c5cb486e009fea18f23f8f6c62</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long double</type>
      <name>getUniform</name>
      <anchorfile>classUniformClosed_3_01long_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>c9db50582b80791959fb0a9a42500228</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UniformClosedOpen</name>
    <filename>classUniformClosedOpen.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>UniformClosedOpen&lt; double, IRNG, stateTag &gt;</name>
    <filename>classUniformClosedOpen_3_01double_00_01IRNG_00_01stateTag_01_4.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base>IRNGWrapper&lt; IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>double</type>
      <name>T_numtype</name>
      <anchorfile>classUniformClosedOpen_3_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>6ff63cd4697bd1e493e9bf7d25fcdb9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformClosedOpen</name>
      <anchorfile>classUniformClosedOpen_3_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>90c5c7eec626f83a3389304965b086db</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformClosedOpen</name>
      <anchorfile>classUniformClosedOpen_3_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>5aa6bf3bbec9608ffddf3bc4749f5000</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>random</name>
      <anchorfile>classUniformClosedOpen_3_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>f10f1f99eebecbbc9d8ae7cff7d106af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getUniform</name>
      <anchorfile>classUniformClosedOpen_3_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>6862bbdb757d795f6c8fda54558889eb</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UniformClosedOpen&lt; float, IRNG, stateTag &gt;</name>
    <filename>classUniformClosedOpen_3_01float_00_01IRNG_00_01stateTag_01_4.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base>IRNGWrapper&lt; IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>float</type>
      <name>T_numtype</name>
      <anchorfile>classUniformClosedOpen_3_01float_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>2401eb0800007d297299f623c9fdd8a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformClosedOpen</name>
      <anchorfile>classUniformClosedOpen_3_01float_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>567a65feb9686ade441c192af8c9780e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformClosedOpen</name>
      <anchorfile>classUniformClosedOpen_3_01float_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>e9a6bcd9e246aebe6ad82c7df5a590d5</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>random</name>
      <anchorfile>classUniformClosedOpen_3_01float_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>919f097e5e3f8970db6bd7f44fe8e170</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>getUniform</name>
      <anchorfile>classUniformClosedOpen_3_01float_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>6c1afc1172c997f960618d9583e96645</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UniformClosedOpen&lt; long double, IRNG, stateTag &gt;</name>
    <filename>classUniformClosedOpen_3_01long_01double_00_01IRNG_00_01stateTag_01_4.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base>IRNGWrapper&lt; IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>long double</type>
      <name>T_numtype</name>
      <anchorfile>classUniformClosedOpen_3_01long_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>4de4b3a729c6cb226d99bbd4d191eb20</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformClosedOpen</name>
      <anchorfile>classUniformClosedOpen_3_01long_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>787b02d7727fd15ad9722d7affad6818</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformClosedOpen</name>
      <anchorfile>classUniformClosedOpen_3_01long_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>accbdcff12174ddbf80d0f49299cd431</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>long double</type>
      <name>random</name>
      <anchorfile>classUniformClosedOpen_3_01long_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>922c3e9c3368131b730073f952720c71</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long double</type>
      <name>getUniform</name>
      <anchorfile>classUniformClosedOpen_3_01long_01double_00_01IRNG_00_01stateTag_01_4.html</anchorfile>
      <anchor>944efebafe9a93afebf15399208a3a92</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UniformOpen</name>
    <filename>classUniformOpen.html</filename>
    <templarg>T</templarg>
    <templarg>IRNG</templarg>
    <templarg>stateTag</templarg>
    <base>UniformClosedOpen&lt; T, IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>T</type>
      <name>T_numtype</name>
      <anchorfile>classUniformOpen.html</anchorfile>
      <anchor>3849b4d8bc9f429e42094678485cbac3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformOpen</name>
      <anchorfile>classUniformOpen.html</anchorfile>
      <anchor>a93cc7dae584434a11551495f91239ff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformOpen</name>
      <anchorfile>classUniformOpen.html</anchorfile>
      <anchor>f551c4020749fb7766ceefc439ee9ddc</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>random</name>
      <anchorfile>classUniformOpen.html</anchorfile>
      <anchor>e479884550c33d546b55eeb039ed06b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>getUniform</name>
      <anchorfile>classUniformOpen.html</anchorfile>
      <anchor>1ebb785a6d2a5074eda29e36cdabbeb5</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UniformOpenClosed</name>
    <filename>classUniformOpenClosed.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <base>UniformClosedOpen&lt; T, IRNG, stateTag &gt;</base>
    <member kind="typedef">
      <type>T</type>
      <name>T_numtype</name>
      <anchorfile>classUniformOpenClosed.html</anchorfile>
      <anchor>8de27b659cb590df444764cfd30b43e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformOpenClosed</name>
      <anchorfile>classUniformOpenClosed.html</anchorfile>
      <anchor>0352bed32514a22f6843e13233b88c78</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformOpenClosed</name>
      <anchorfile>classUniformOpenClosed.html</anchorfile>
      <anchor>86deb5eb087696928a99557303410ca5</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>random</name>
      <anchorfile>classUniformOpenClosed.html</anchorfile>
      <anchor>546e0cf4b7feb7fc2d4a0918712683e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>getUniform</name>
      <anchorfile>classUniformOpenClosed.html</anchorfile>
      <anchor>b11494e71a9f69f8b1de2ebcecd8b247</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UpperTriangular</name>
    <filename>classUpperTriangular.html</filename>
    <base>MatrixStructure</base>
    <member kind="typedef">
      <type>UpperTriangularIterator</type>
      <name>T_iterator</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>b82c2e760411603c189ea24b5d67b499</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UpperTriangular</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>903c3966499bbb5a3cc967c993eb5151</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UpperTriangular</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>2b2d339def21734b15303c27b3f9744b</anchor>
      <arglist>(unsigned size)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UpperTriangular</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>149c92f7b48608c313b5cfa3dcb61305</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>columns</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>cc79e6952297e448d67580913332e346</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>coordToOffset</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>0ae047a32d07c300fe52fa65bdaa913c</anchor>
      <arglist>(unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>firstInRow</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>35f33c462e10d00350f4a3b69840a10e</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>get</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>f6afd1a429ee6de4df586b76181ae6f6</anchor>
      <arglist>(const T_numtype *restrict data, unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>get</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>e1371b1227db1459efcd7868e0fdc6b6</anchor>
      <arglist>(T_numtype *restrict data, unsigned i, unsigned j)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>lastInRow</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>9b0a17a32b8955f88e5217d54ae27df4</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>firstInCol</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>0ea73c20a888758206c2e1b92064c737</anchor>
      <arglist>(unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>lastInCol</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>b19d481683f2f9e893dcafd9de0f8efc</anchor>
      <arglist>(unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>inRange</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>26b4a2cc78e56f7ffc127a32c9eb288e</anchor>
      <arglist>(const unsigned i, const unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>numElements</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>3a0608a2ca518cafca5e759930fe0714</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>rows</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>eb2fa8962cd3af4d5101279fa29e6cdf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>339a5fd5607a61694b8bac365baf514d</anchor>
      <arglist>(const unsigned size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>116ee5c72454748c51fc617628cbc144</anchor>
      <arglist>(const unsigned rows, const unsigned cols)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned</type>
      <name>size_</name>
      <anchorfile>classUpperTriangular.html</anchorfile>
      <anchor>9478841a9fd71e2b8dcd2b88ab094b3a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UpperTriangularIterator</name>
    <filename>classUpperTriangularIterator.html</filename>
    <member kind="function">
      <type></type>
      <name>UpperTriangularIterator</name>
      <anchorfile>classUpperTriangularIterator.html</anchorfile>
      <anchor>c0b821b6876d40c4e46a85292fe779a2</anchor>
      <arglist>(unsigned rows, unsigned cols)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>classUpperTriangularIterator.html</anchorfile>
      <anchor>481cfad92336d968428da320ba8fd7d6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator++</name>
      <anchorfile>classUpperTriangularIterator.html</anchorfile>
      <anchor>9ed10a8f70b2efac6da0269915ae3cfc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>row</name>
      <anchorfile>classUpperTriangularIterator.html</anchorfile>
      <anchor>fe1782495437b70acbf7b2d60e7cfcfb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>col</name>
      <anchorfile>classUpperTriangularIterator.html</anchorfile>
      <anchor>ea5cf5bd74d12bd13f2ebad79183d660</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>offset</name>
      <anchorfile>classUpperTriangularIterator.html</anchorfile>
      <anchor>9f47ed58b3a94c6d21aa13d8c6b45016</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>size_</name>
      <anchorfile>classUpperTriangularIterator.html</anchorfile>
      <anchor>0c6e58c284e4e65c2017666da3831573</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>good_</name>
      <anchorfile>classUpperTriangularIterator.html</anchorfile>
      <anchor>d01ffa6b1c60402626db7cf9860c8b84</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>offset_</name>
      <anchorfile>classUpperTriangularIterator.html</anchorfile>
      <anchor>ad40a6efac16e56d13eb124907965dd4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>i_</name>
      <anchorfile>classUpperTriangularIterator.html</anchorfile>
      <anchor>a6a266d1e02ed93ddee18a143822415a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>j_</name>
      <anchorfile>classUpperTriangularIterator.html</anchorfile>
      <anchor>6f784b1be08d73ff791a1fe0a84286ff</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Vector</name>
    <filename>classVector.html</filename>
    <templarg>P_numtype</templarg>
    <base protection="protected">MemoryBlockReference&lt; P_numtype &gt;</base>
    <member kind="typedef">
      <type>P_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>63dfe9fb06d8b4595b9e8fb10fc0755e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Vector&lt; T_numtype &gt;</type>
      <name>T_vector</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>29e279edfeac4d65aad0d814c05cfaf0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VectorIter&lt; T_numtype &gt;</type>
      <name>T_iterator</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>3595565cd5a82f30d054fe37d0aaa802</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VectorIterConst&lt; T_numtype &gt;</type>
      <name>T_constIterator</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>6713f9dd10d7bd7d91b7452cf0208565</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VectorPick&lt; T_numtype &gt;</type>
      <name>T_pick</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>5fbb048b36ae3897d8b0c6d993b33a9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Vector&lt; int &gt;</type>
      <name>T_indexVector</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>a02a1323b0f3ca8c6cc82732fad69768</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>ee4ac39fec9d9fe9d7e46078faa20edb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>f05f2b93ab84395815ed1dbd8b5be875</anchor>
      <arglist>(const Vector&lt; T_numtype &gt; &amp;vec)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>38be771b9d958001e0b254cf3b803944</anchor>
      <arglist>(int length)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>2c4c2092b709e7de633d3176fb3853fc</anchor>
      <arglist>(const Vector&lt; T_numtype &gt; &amp;vec, Range r)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>14396fffa4fcd603bc9a495f1c5c7e63</anchor>
      <arglist>(int length, T_numtype initValue)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>a406cba2f7c131bfd2b6f968efe2b9d2</anchor>
      <arglist>(int length, T_numtype firstValue, T_numtype delta)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>5a4f6ccc4fdcabb3426e9bf74dd2e6f8</anchor>
      <arglist>(int length, Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>595a735f5f6c2f2497473315fbb4123e</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt; expr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>b333be86fbb2c4b59deb8ce7c9f685c6</anchor>
      <arglist>(int length, T_numtype *restrict data, int stride=1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>01a63661317f3e014e7c561074796b0c</anchor>
      <arglist>(Range r)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assertUnitStride</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>72444363cd75161cadbb9bfe7cb4280d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T_iterator</type>
      <name>beginFast</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>591f75ccd54446d9d5b9a3dad62da79a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T_constIterator</type>
      <name>beginFast</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>a85824e5320a1ae5f9900602c4e1f9f1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_vector</type>
      <name>copy</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>55d29df87fabeb5de8f000f19cc36bd3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype *restrict</type>
      <name>data</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>5a39ac5863d5fd6e859b782ff4ce956f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T_numtype *restrict</type>
      <name>data</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>6296f596c36a329f8f0af3ae48fc93fc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isUnitStride</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>a4ae0c8062004e1cf31e272f79ce9227</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>length</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>d4853c638cc673c9482cea9b75ef6de2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>makeUnique</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>68ac4820260c10b5993729f2b5a40067</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reference</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>46f8e9952216f3a25dfccfe93901af88</anchor>
      <arglist>(T_vector &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>bcb311f63292603d3800bc33e8a68c22</anchor>
      <arglist>(int length)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resizeAndPreserve</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>bb89965ed772d10ba2e111e3a3805adc</anchor>
      <arglist>(int newLength)</arglist>
    </member>
    <member kind="function">
      <type>T_vector</type>
      <name>reverse</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>3e90ce0f4782c74833d15958860197d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>stride</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>941b5a6e377ba6a0c127955d8a555ef5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator _bz_VecExpr&lt; VectorIterConst&lt; T_numtype &gt; &gt;</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>47837d106251d81517d3877ae17f9f27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>_bz_suggestLength</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>40d48e3950aac1d020b13c096cc19930</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_bz_hasFastAccess</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>8d7a8c1338ec4c6d80c056c8a96e3e88</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>e76ca783ba8c09238851464dd858a522</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>5d3a05bca37f8a8f68ba1a4dffafdc5a</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_bz_assign</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>6a7dad6537ded55af065a83418489cd0</anchor>
      <arglist>(P_expr, P_updater)</arglist>
    </member>
    <member kind="function">
      <type>_bz_VecExpr&lt; T_constIterator &gt;</type>
      <name>_bz_asVecExpr</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>1ac2b769312c96ee1395530728445a5b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator()</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>30ba25e8c925e844db5b108045dcf1c9</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>15e0ad9ff7f44fcd4ea01ed3ad6be866</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator[]</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>3041dfa1ad0b03a054da1f652bf1e0bd</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;restrict</type>
      <name>operator[]</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>bdc2fcc26323ccba699ca8f1a6102b74</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>T_vector</type>
      <name>operator()</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>a4e9255348248f40e454f3e6639fd3b7</anchor>
      <arglist>(Range r)</arglist>
    </member>
    <member kind="function">
      <type>T_vector</type>
      <name>operator[]</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>12f5164b480eef511e3e192b976efce5</anchor>
      <arglist>(Range r)</arglist>
    </member>
    <member kind="function">
      <type>T_pick</type>
      <name>operator()</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>d6829a2327882fe77c8ba5ba523add7a</anchor>
      <arglist>(T_indexVector i)</arglist>
    </member>
    <member kind="function">
      <type>T_pick</type>
      <name>operator[]</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>81cc4fba69333b0932f6460a9c0021a5</anchor>
      <arglist>(T_indexVector i)</arglist>
    </member>
    <member kind="function">
      <type>ListInitializationSwitch&lt; T_vector, T_iterator &gt;</type>
      <name>operator=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>e91d623820c477af80690f777ebca547</anchor>
      <arglist>(T_numtype x)</arglist>
    </member>
    <member kind="function">
      <type>T_iterator</type>
      <name>getInitializationIterator</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>4a59fc0b4ccc854f6991701b3dd47603</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>initialize</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>dff961e2050b71961dd4b0a745f07eb3</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>2e88f7f0c53867b9b082c31a65aff8d9</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator-=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>7510f78083c124573370e4d10fc7cd05</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator*=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>41fbd39e6f186b306c8608651177cf14</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator/=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>71f3cfdb99a12730a6961dffb7e10407</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator%=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>da39147108eec008f41a6095f8160348</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator^=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>2adfac383a6cfd7d8cb7c3f1f6925a38</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>4a399c697300019c9ba9e096805eaa19</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator|=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>6f59653a47e64cb24c88aea091bf7e2c</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>0708e3837558cba4507e02a2c5a2f44e</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>fbf8a6d4aecc51138ecc6500018efe4b</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>9d2f4bf75ac40a697ef7dcc08fb00ba7</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>ec8d3a6ce80fa659a3e93c2aaa7b21d7</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator-=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>42a456ce8d01dd853d0330bf94732677</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator*=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>ade103a1513aefbbd15c646a508c73d8</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator/=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>4f5e8de0817c79e9ae2b586e34c05fc4</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator%=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>e3eaca9958fe060508b1174515753ab6</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator^=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>5c5e863eaac4ab2a36d3a4e28191f4be</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>82d788cb0d54b88ef652b939bcac5d17</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator|=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>d312f2896bc0d28ccdc81d6f2e0fcef4</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>af6db53f7371319e3b8a65e87a827f6c</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>108ff3467cc64556aab7708fb8eb9376</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>cd241033547232aaad3c7f4c4a83294c</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>fe985a2b7bd4a89efe619df57cf6ca0f</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator-=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>0afd4b8fe543727367920fdeb751a280</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator*=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>4d55141001264909f69f6e5c89a305a7</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator/=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>3677c4ac75cb01abc8694be964e88801</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator%=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>dfc353083b4421aa0f7acc7c1444ea40</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator^=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>d1feb2570dade4f17ce6c7e9d04a294c</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>b457f42ed0505c21b7a66a69cf17ae95</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator|=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>f71ba4f631c6bd200f906ee79e8e710b</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>60bbc1e4e4cc4fdb5bf5e0f8f05a8f7a</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>13b415ee9fd77bd6f6b41926107ceccd</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>4f16325cc96cd4de5487589c2aa363ce</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>06a90c4746a69257dcc9f3897a39127c</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator-=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>b25b3ca73641f6505b916679d559ea34</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator*=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>c19632fe098b022e898a81444a1b79bd</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator/=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>e5648d6958308097868893689a716e83</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator%=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>6aa06e16399184a495197e731ab2b23e</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator^=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>a36fda51d048df27bd9a0d2a50724225</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>5f938af12e68534ba83838ca90d32cf0</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator|=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>650cadfc9aa89c9cde92308e5ff4ed83</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>48dd530cb81cf935ffafbf1bbbd32388</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>eb43f294aacf84627165852249825432</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>721370fa12f3d62a006f00b6a749405d</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>f0d8ac97ac36e8a11a7ed78db4a74f3b</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator-=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>2747e58920271c4f8086a9083a2068d3</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator*=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>296ff9342a598452ee07881d22dc9695</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator/=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>8633b3e99037c24787d0bdd2f09675a8</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator%=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>2ca06bf58574f26eb1feb0d4a9cc40c5</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator^=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>aaa6693e1b9755b653d1edd8586727bf</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>f41deafd769e66233da458d66896b2f3</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator|=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>e8d5e806d5fc2beb72f812913dc54975</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>b9aaffd7a30c813a2ee5997659f2629d</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>1b0c85d1bcd1e6811e314be3a1edf4f3</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>cc514a12d009f035b064462d5a1d27ca</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>5d021f7aca83bbc0df3c29a37263ec71</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator-=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>f296e4142be86d1fbe3a560431aed0a3</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator*=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>ce5105280bbfa86735f865d70aa030be</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator/=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>24615370cd826d8280d38def83e43d62</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator%=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>d9c2b987a87713752dec4df9d5a18c3c</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator^=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>934466c7399aaabaa4b3a5d0b412acf4</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>cf56849ff46372010312a03c07e82580</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>operator|=</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>236bd98f8dfdada2e93e5ed4d2fa3f44</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>MemoryBlockReference&lt; P_numtype &gt;</type>
      <name>T_base</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>694af483267d03a46bef986a8209040d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>length_</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>553b34b01aaf29d2f01cfee72f4dce08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>stride_</name>
      <anchorfile>classVector.html</anchorfile>
      <anchor>6c2fcaac55b8f84d011755be2a3556b6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>VectorIter</name>
    <filename>classVectorIter.html</filename>
    <templarg>P_numtype</templarg>
    <member kind="typedef">
      <type>P_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>ac3a64c6fd8651eff6039cb346be1af1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VectorIter</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>56cff4862da53097bb06af61862d7145</anchor>
      <arglist>(Vector&lt; P_numtype &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VectorIter</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>f2234e12465ae68ed43716f3531b1cb7</anchor>
      <arglist>(P_numtype *restrict data, int stride, int length)</arglist>
    </member>
    <member kind="function">
      <type>P_numtype</type>
      <name>operator[]</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>44896fa2adb8bbc46125aae3678923b4</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>P_numtype &amp;restrict</type>
      <name>operator[]</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>ba8bbbc7b7d300560aff4cc9b57aebc3</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>P_numtype</type>
      <name>operator()</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>d45e6883c4c2827df13586aa1c8594d0</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>P_numtype &amp;restrict</type>
      <name>operator()</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>22ad3c8c495b19a258493e8b660080db</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>P_numtype</type>
      <name>operator*</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>dcc9aee3c2ca699089de6f0f03402522</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>P_numtype &amp;</type>
      <name>operator*</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>e931daa256977fe04db917c74caa021a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>VectorIter&lt; P_numtype &gt;</type>
      <name>operator+</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>2571631d281b78848e7b8b61f54b3fa6</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>length</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>5994dbca68413be18704c7a0c82389cc</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isUnitStride</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>988c106e3d456f9b1690066d38077230</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_bz_hasFastAccess</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>04efe8ca2840e09f02310f6e00de9427</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>P_numtype</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>8935baef7d8ddbbe20c656d583cbb359</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>P_numtype &amp;restrict</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>186a9a1059686d28ca456dd309679c97</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>_bz_suggestLength</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>3e911c462211ff532ae46e543125c1cf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_staticLengthCount</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>5c1484d75f0ef56a0e347a5cd654a1fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_dynamicLengthCount</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>5584656ea9b435ae2ee3deb74213dc06</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_staticLength</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>f0a294e404a2578006da378ff14f4458</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>VectorIter</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>c01c565c6d07804f7f9913021aebecfd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>P_numtype *restrict</type>
      <name>data_</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>9e8ff3240c7fda2a2d638d997498365f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>stride_</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>07e8dd850a0e32fdb2ffbaf8d2604809</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>length_</name>
      <anchorfile>classVectorIter.html</anchorfile>
      <anchor>33d6f18b799c7184aec21e6b8d4e6e09</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>VectorIterConst</name>
    <filename>classVectorIterConst.html</filename>
    <templarg>P_numtype</templarg>
    <member kind="typedef">
      <type>P_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>9dca841e00192ee5d6277f7443833603</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VectorIterConst</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>c0f827a86530b446ac35169e52f38a2c</anchor>
      <arglist>(const Vector&lt; P_numtype &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VectorIterConst</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>ef4870c7b4ee98e8c96b154423bba02b</anchor>
      <arglist>(P_numtype *restrict data, int stride, int length)</arglist>
    </member>
    <member kind="function">
      <type>P_numtype</type>
      <name>operator[]</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>69a9b3393046cd494ec477cc04a4717c</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>P_numtype</type>
      <name>operator()</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>59218a68b79658b7926468ddf6b080e2</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>P_numtype</type>
      <name>operator*</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>d1f40d5cd092cfd45cf1ba3606925835</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>VectorIterConst&lt; P_numtype &gt;</type>
      <name>operator+</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>b7b3cb105d01d41b18c5070dd8ac9c86</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>length</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>3670612d84e395194fe3cdc5df2877a8</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isUnitStride</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>e4bf5a07bd6f95b1fb33600fd4c2e1d3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_bz_hasFastAccess</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>50c98e070fca163f71d2adac2c7d80aa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>P_numtype</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>51babf4bdbcaf9aa2d00c7c3df8ae79c</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>_bz_suggestLength</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>26a27eef00bf17bebfe53da97f64107a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_staticLengthCount</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>fd959c64a5ed086e9f494dd672e6c425</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_dynamicLengthCount</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>5d97ad5affa0a96d0ed6e092e8d877e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_staticLength</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>9fae2e88f80b34d4bdb2bd1ce89503dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const P_numtype *restrict</type>
      <name>data_</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>36207c3bbb4170dbcf598f118e23dedd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>stride_</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>fc7ae4491012be68359fecaf877dfd93</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>length_</name>
      <anchorfile>classVectorIterConst.html</anchorfile>
      <anchor>a21d6463ac9b4e1f9a6b9c8b61db069a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>VectorPick</name>
    <filename>classVectorPick.html</filename>
    <templarg>P_numtype</templarg>
    <member kind="typedef">
      <type>P_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>8e830396ccfaea2b85a2a442f45fca35</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Vector&lt; T_numtype &gt;</type>
      <name>T_vector</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>d84fb47502945888eb8854b1460e493b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Vector&lt; int &gt;</type>
      <name>T_indexVector</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>a9b24fd60f963a737fa946622c5e39a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VectorPick&lt; T_numtype &gt;</type>
      <name>T_pick</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>b257fd713ce0f2a81bc79059cec93ac9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VectorPickIter&lt; T_numtype &gt;</type>
      <name>T_iterator</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>8c1792384cedd1074814cc152aea9e72</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VectorPickIterConst&lt; T_numtype &gt;</type>
      <name>T_constIterator</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>5c6029ef4573adb719b497be94ce2a57</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VectorPick</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>b14d106783a9792094d514ba01882bb1</anchor>
      <arglist>(T_vector &amp;vector, T_indexVector &amp;indexarg)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VectorPick</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>4a21c5260690030332b01f5ef0b48146</anchor>
      <arglist>(const T_pick &amp;vecpick)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VectorPick</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>423da234d663ce887658739472ad71ab</anchor>
      <arglist>(T_pick &amp;vecpick, Range r)</arglist>
    </member>
    <member kind="function">
      <type>T_iterator</type>
      <name>beginFast</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>c838bc112796e55b2fb8d947da294139</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T_constIterator</type>
      <name>beginFast</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>31b9c882f8cf5cba3d0013dd8ecb7fd6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_indexVector &amp;</type>
      <name>indexSet</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>ee2f5ca29b2009f4b994c45d844860be</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T_indexVector &amp;</type>
      <name>indexSet</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>72a2a0e2ffe6006a67f1c200430daeca</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>length</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>f826c2b7b660235b9cb087ecee9ba153</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setVector</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>15b7b1ce0c9fd0177183c06a9401eb5e</anchor>
      <arglist>(Vector&lt; T_numtype &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setIndex</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>fef469cd7c207d158a5538478b74aca9</anchor>
      <arglist>(Vector&lt; int &gt; &amp;index)</arglist>
    </member>
    <member kind="function">
      <type>T_vector &amp;</type>
      <name>vector</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>da686dd18fcd948bc70673f5aa8e9e14</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T_vector &amp;</type>
      <name>vector</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>afe5a26735cd9dea9bdfe08190319d4a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>_bz_suggestLength</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>fe4110178a782d9c2f908a040e31cb8e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_bz_hasFastAccess</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>ef1659199769ad33c74496309411d206</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>03935b8c4a109cb0ea18474bcc1b98cd</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>c0818825b97a1e9344cf6e9ed09b98c5</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>_bz_VecExpr&lt; T_constIterator &gt;</type>
      <name>_bz_asVecExpr</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>fd6606f86ae883542434f7c772e26de1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator()</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>e7f56f2d51de42241fb793932a383b7b</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>operator()</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>bbd4a26d326c094cf7d3dbf7b597ef2b</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator[]</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>0f45701e9d69fc993f6a325cfb928967</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>operator[]</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>2872c1cc39f87635a42d4f16343e9507</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>T_pick</type>
      <name>operator()</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>e3854109108868d68a8a0ff51c1455ab</anchor>
      <arglist>(Range r)</arglist>
    </member>
    <member kind="function">
      <type>T_pick</type>
      <name>operator[]</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>dbd8c81e078f7a3ed5677dacfdf84855</anchor>
      <arglist>(Range r)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>ca32a501293238de751e43505c4b8d9f</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>039ad6b792830edfe5f77147aa41cc69</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator-=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>64a516e352f654692ca1f68b483e4d5d</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator*=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>7b89bab85f86832ca20a7fd6b03c8017</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator/=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>9fd725edd394c1fe9aab3c20e7a14c62</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator%=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>2bf9ca1975c29df2474324d7fb5db87e</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator^=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>fda95e2c32338c932fd7c1c31fdcb45b</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>e7111c982e36b66a7dc44a66cb320e09</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator|=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>b6ad50e2137879482f3311302f24ce69</anchor>
      <arglist>(T_numtype)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>28b169f72f85f8ab9b0b9f17c0572919</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>454c4920a7298b3268deec577f98aeee</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>af7ffd68dc8e9d994b476541642784bb</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>0969c7b6b9a0d104128f09eca4b16315</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator-=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>0e7ea6ceb555e2035eaafba7d5cc2251</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator*=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>eb89d60673fdebd7825ef043f3a2988a</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator/=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>2ba6bcaa510137166170deb990c99005</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator%=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>7f885920e41aa235858dc8838dd8c78f</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator^=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>9b8c0798c3358654602103db09a314c7</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>6b648eba374ca88d54f2837be3db140a</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator|=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>c3049320b323680fc3e85e16e202381e</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>d1915daac5e3d40569034973f65037d5</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>e726ea174593237c34b0fd7b3901d599</anchor>
      <arglist>(const Vector&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>d6a0cc7f9edb0bb65ce5ebde3bb53bc5</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>682063d5ac5cca24d01f30533eef31d8</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator-=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>efae0fabaf5359648d29ab04f2b87af2</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator*=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>b224ad7f010690f9763481c1fef7535b</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator/=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>71ccdbe925b69377f641f80ea1a51b3b</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator%=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>82813dfa81e018b94e5b36b51d01ad8e</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator^=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>1cd98ce1168c512ef5da442dec25e83d</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>0247c644b7f8d4078ac1b9c2f85ae727</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator|=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>e5c448c407108d0e6ff867b302df5ebe</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>f96a80f84379d97653b289a1a96ad15f</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>25b10d09868e66e8d964a61d6504e7be</anchor>
      <arglist>(_bz_VecExpr&lt; P_expr &gt;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>92d4b9c3b2ca223f2a2ac84adaa7a25d</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>d25b6edeadbde87657ffc657e502f793</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator-=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>459111af611f5500226883808c5a6c00</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator*=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>afd0f4922f005583d4c2f0e5fe99bb4a</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator/=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>a313f4590f95c034ed9dfd2ce5e81e26</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator%=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>1055884fb225f253e576456451e5aaee</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator^=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>15b661ce749b182f9568a3bd4ddaa16b</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>4d30030bbbffcf00c2828e148019cf30</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator|=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>bbe2535d666c65ba48dba2819b5a7e31</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>2c490821da68773318bba5ee5e5962ba</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>70e326ef451d59f06027a5f9dc18c7b4</anchor>
      <arglist>(Range)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>aac91cbd42fb6379674ae6c9e0d37fe4</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>a91c782b010e256d6feb006abf46c472</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator-=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>4d0f3c335888ff6e08e0a0b4622af740</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator*=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>407b12db5069c31dc52bb789b2cf089f</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator/=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>a75ba432f22f473b468b2205d812cbb6</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator%=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>14e90b0321eaea14d3e151e22f88a3a6</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator^=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>74de9836d577da3cb0efb8cd95d22d11</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>e22adce3827d57fdf4b3015da85ae8cb</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator|=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>183377f258bf631c7bf57dfeebe248e9</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&gt;&gt;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>4c0bfb2ca7ce54476f14eef5eda47aa2</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&lt;&lt;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>bf29d94d5322e7bda53846d58984591e</anchor>
      <arglist>(const VectorPick&lt; P_numtype2 &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>35b653fc68a6d7e1e52f3dfd4370c63f</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>b2a866b46cc5b549f083e37e1c47e9c6</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator-=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>018f01f093d59c5717c058b6dadb1e00</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator*=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>5db19beec71fb0f81cc9cdd994b479bc</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator/=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>b02a168b0a3238845ed7a5e113afce6e</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator%=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>c87021c78ec8f65ad08af60471ae78b6</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator^=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>82fe6c3998a111b6cb0d1070594a7601</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>cb8c2951c937e4705728d094f3ce563f</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function">
      <type>T_pick &amp;</type>
      <name>operator|=</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>f30442b1685da7999e2daff954bceba1</anchor>
      <arglist>(Random&lt; P_distribution &gt; &amp;random)</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>VectorPick</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>7bb7fca4e1fb7dbb1604884b74439e2d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>_bz_assign</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>4a71fb6359edf71f8cfaf5a94995769a</anchor>
      <arglist>(P_expr, P_updater)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T_vector</type>
      <name>vector_</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>22fe7d8acc3ba8a465b7c0f277b3c68e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T_indexVector</type>
      <name>index_</name>
      <anchorfile>classVectorPick.html</anchorfile>
      <anchor>7caeadc81cb4e54df43e98f133674132</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>VectorPickIter</name>
    <filename>classVectorPickIter.html</filename>
    <templarg>P_numtype</templarg>
    <member kind="typedef">
      <type>P_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>105b4687faac1a8a5ee37bdec8163f92</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VectorPickIter</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>834212637140ee41fe3614c6af3f2b32</anchor>
      <arglist>(VectorPick&lt; T_numtype &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator[]</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>70b6552aec5448cd841bc0f677c3e2c6</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>operator[]</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>2bb0290a79c3f855b5ef93a18b09d722</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>length</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>8ce5e1eaf57976ae9048d4d364172b8c</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>_bz_suggestLength</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>3e6561605f364f742cf77915cbeba6c5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isUnitStride</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>405f46975bde2f503fb3a2f1c4482e8f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_bz_hasFastAccess</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>16937aaa4112db780056bd5dfb740bc6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>1327eb4f9cd353758f61d07bb4ba97e9</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype &amp;</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>3bd9b0179ab6f664233f442758850201</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_staticLengthCount</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>f457b51965968e83b9d4725eb89055b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_dynamicLengthCount</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>53b51cbbe675d8e9575d8adbb6b7bfa8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_staticLength</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>71f81c5af536d5f8ac87d1e91f8bac84</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T_numtype *restrict</type>
      <name>data_</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>5107509735339c5767b04879645efce0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>dataStride_</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>e58ccdbc42b86af16c29e96fbf5c7681</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const int *restrict</type>
      <name>index_</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>c03f5198ba3bb7cc23417d918b2dc1db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>indexStride_</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>21588cc5948b394c45d0e5be8e86ed7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>length_</name>
      <anchorfile>classVectorPickIter.html</anchorfile>
      <anchor>ddb2450ee974859e7da0871ad9f8f045</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>VectorPickIterConst</name>
    <filename>classVectorPickIterConst.html</filename>
    <templarg>P_numtype</templarg>
    <member kind="typedef">
      <type>P_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>598ff8242bb68fb7f4cfb38666977a37</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VectorPickIterConst</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>eff39b18bf83fb845f14687d95b0f146</anchor>
      <arglist>(const VectorPick&lt; T_numtype &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>operator[]</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>7a69180e91b3b6fa4848ad88e9a47e6e</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>length</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>fb8b76bdcd70d890fa825ecd000badca</anchor>
      <arglist>(int) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>_bz_suggestLength</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>c50f48aed70f27d448bdcd3940d37296</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isUnitStride</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>894a20d7c4e67048e12a68cfb17f8cb8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_bz_hasFastAccess</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>8755cbff6b4e5ccef6fe8d9d482d4196</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T_numtype</type>
      <name>_bz_fastAccess</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>29f2c1757118a2c4f3f6f007ad3d0a41</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_staticLengthCount</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>fa70ce044f98bf61e159595844293086</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_dynamicLengthCount</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>dc2916b40c25cce7d67a53205761d82e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>_bz_staticLength</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>27fa86056161026d326b4e6df386489f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const T_numtype *restrict</type>
      <name>data_</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>0639c11d4ac133e59ff5c96a4488d8c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>dataStride_</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>079de6e802fc4e0355780fb527c99fea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const int *restrict</type>
      <name>index_</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>8670acdf237f8f8860e2c17d4a3e1ab3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>indexStride_</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>fc2913a5ef1db5412f67f727f85862ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>length_</name>
      <anchorfile>classVectorPickIterConst.html</anchorfile>
      <anchor>ab37a4f4513980c1902c3cbfb83edaf4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ZeroElement</name>
    <filename>classZeroElement.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>P_numtype</type>
      <name>T_numtype</name>
      <anchorfile>classZeroElement.html</anchorfile>
      <anchor>7875bd7b7cb6515725d60df536fa888f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T_numtype &amp;</type>
      <name>zero</name>
      <anchorfile>classZeroElement.html</anchorfile>
      <anchor>2750b4bfa1587be1566edfda86ef17da</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static T_numtype</type>
      <name>zero_</name>
      <anchorfile>classZeroElement.html</anchorfile>
      <anchor>60c72c8949fe9b8129eac793e8257c46</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
