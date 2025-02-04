const express = require('express');
const router = express.Router();
const access_rights = require('../models/access_rights_model');
const { checkAdmin } = require('../authentication');

//get all 
router.get('/', checkAdmin, function (request, response) {
    access_rights.getAll(function (err, result) {
      if (err) {
        response.json(err);
      } else {
        response.json(result);
      }
    });
  });

  
// get by access id
router.get('/:idaccess_rights', checkAdmin, function (request, response) {
      access_rights.getById(request.params.idaccess_rights, function (err, result) {
        if (err) {
          response.json(err);
        } else {
          response.json(result[0]);
        }
      });
    },
  );

 // add an access right 
 router.post('/', checkAdmin, function (request, response) {
    access_rights.add(request.body, function (err, result) {
      if (err) {
        response.json(err);
      } else {
        response.json(result.affectedRows);
      }
    });
  });

 // delete 
 router.delete('/:idaccess_rights', checkAdmin, function (request, response) {
    access_rights.delete(request.params.idaccess_rights, function (err, result) {
      if (err) {
        response.json(err);
      } else {
        response.json(result.affectedRows);
      }
    });
  }); 
module.exports = router;