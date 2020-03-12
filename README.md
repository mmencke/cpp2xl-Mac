# cpp2xl-Mac
Black Scholes implementation in C++ imported to Excel 2016 on Mac

Developed in Xcode 9.2. The C++ project (cpp2xl.xcodeproj) contains
- blackScholes.h:   Black-Scholes implementation
- cpp2xl.h:         header for the Dynamic Library
- cpp2xl.m:         main file for the Dynamic Library
- gaussians.h:      Implementation of the Gaussian distribution functions
- monteCarlo.h:     Implementation of Black-Scholes Monte Carlo simulations of Call options

libcpp2xl.dylib is the Dynamic Library itself. This must be put in "/Library/Application Support/Microsoft" for Excel to be able to see it.

Cpp2xl_v2.xlsm is the Macro-Enabled Excel workbook. 

<p class="h1">Example VBA function</p>
The following VBA code imports "xBlackScholes" function from cpp2xl.m into Private VBA function "cppBlackScholes"

```
Private Declare PtrSafe Function cppBlackScholes Lib "/Library/Application Support/Microsoft/libcpp2xl.dylib" Alias "xBlackScholes" (ByVal spot As Double, ByVal strike As Double, ByVal mat As Double, ByVal rate As Double, ByVal vol As Double) As Double
```

Then we create Public VBA function "BlackScholes" that checks whether the workbook has access to the Dynamic Library before calling "cppBlackScholes"

```
Public Function BlackScholes(spot As Double, strike As Double, mat As Double, rate As Double, vol As Double) As Double

    If hasAccess = False Then
        hasAccess = requestFileAccess()
    End If
    
    If hasAccess Then
        BlackScholes = cppBlackScholes(spot, strike, mat, rate, vol)
    End If
    
End Function
```

hasAccess is a boolean VBA variable. The requestFileAccess function can be seen below

```
Private Function requestFileAccess() As Boolean
    
    Dim fileAccessGranted As Boolean
    Dim filePermissionCandidates
    
    filePermissionCandidates = Array("/Library/Application Support/Microsoft/libcpp2xl.dylib")
    fileAccessGranted = GrantAccessToMultipleFiles(filePermissionCandidates)
    
    requestFileAccess = fileAccessGranted

End Function
```
