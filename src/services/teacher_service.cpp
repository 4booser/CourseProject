#include "services/teacher_service.h"

#include "repositories/teacher_repository.h"
#include "repositories/workload_repository.h"

namespace services
{
    OperationResult ValidateTeacher(const models::Teacher& teacher)
    {
        if (teacher.full_name.empty())
        {
            return OperationResult::Fail("ПIБ викладача не може бути порожнiм.");
        }

        if (teacher.digital_commission.empty())
        {
            return OperationResult::Fail("Цифрова комiсiя не може бути порожньою.");
        }

        if (teacher.quota == 0)
        {
            return OperationResult::Fail("Квота викладача повинна бути бiльше 0.");
        }

        return OperationResult::Ok();
    }

    OperationResult CreateTeacher(models::Teacher& teacher)
    {
        OperationResult validation_result = ValidateTeacher(teacher);
        if (!validation_result.success)
        {
            return validation_result;
        }

        return SaveTeacher(teacher);
    }

    OperationResult UpdateTeacher(unsigned short teacher_id, const models::Teacher& teacher)
    {
        if (!GetTeacherById(teacher_id).has_value())
        {
            return OperationResult::Fail("Викладача з таким Id не знайдено.");
        }

        OperationResult validation_result = ValidateTeacher(teacher);
        if (!validation_result.success)
        {
            return validation_result;
        }

        return EditTeacherById(teacher_id, teacher);
    }

    OperationResult DeleteTeacher(unsigned short teacher_id)
    {
        if (!GetTeacherById(teacher_id).has_value())
        {
            return OperationResult::Fail("Викладача з таким Id не знайдено.");
        }

        if (HasWorkloadForTeacher(teacher_id))
        {
            return OperationResult::Fail("Викладач використовується в навантаженнi.");
        }

        return DeleteTeacherById(teacher_id);
    }
}
