<!doctype html>
<?php
session_start();
@include "udpload.php";
?>
<html>
<head>
<title>PS3 Config</title>
<meta name="viewport" content="width=device-width, initial-scale=1" />
<link rel="stylesheet" href="../jquery/jquery.mobile-1.4.3.min.css" />
<script src="../jquery/jquery-1.11.1.min.js"></script>
<script src="../jquery/jquery.mobile-1.4.3.min.js"></script>
</script>
</head>
<body>

<div data-role="page" id="wsdebug">
<div data-role="header">
<a href="../index.php" data-ajax="false" data-rel="back" data-transition="slide" class="ui-btn ui-corner-all ui-btn-inline">Go Back</a>
<h1>UDPConfig</h1>
</div>

<form data-ajax="false" method="post" action="udpsave.php">
<div role="main" class="ui-content">

<div class="ui-field-contain">
<label for="name"><a href="#p_pwm_min" data-rel="popup">ESC min:</a></label>
<input type="number" name="c0_0" id="c0_0" value="<?php echo $c[0][0];?>"/>
<label for="name"><a href="#p_pwm_max" data-rel="popup">ESC max:</a></label>
<input type="number" name="c0_1" id="c0_1" value="<?php echo $c[0][1];?>"/>

<label for="c1_0">Yaw - A:</label>
<input type="number" name="c1_0" id="c1_2" value="<?php echo $c[1][0];?>"/>
<label for="c1_1">Pitch - A:</label>
<input type="number" name="c1_1" id="c1_2" value="<?php echo $c[1][1];?>"/>
<label for="c1_2">Roll - A:</label>
<input type="number" name="c1_2" id="c1_2" value="<?php echo $c[1][2];?>"/>

<input type="submit" value="Save"/>

<div data-role="collapsible" data-collapsed="true">
<h3>Config view</h3>
<pre>
<?php
readfile($config_path."udp.config");
?>
</pre>
</div>
</div>
</form>
</div>
</body>
</html>
