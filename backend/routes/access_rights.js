const express = require('express');
const router = express.Router();
const access_rights = require('../models/access_rights_model');
const { checkAdmin } = require('../authentication');



module.exports = router;